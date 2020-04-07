/*! \file singlecalib.cpp
 * \brief A single camera\video geometric calibration noninteractive example.
 * \author Oleg Jakushkin
 * \author Julien Pilet
 * In this example, the user gives a file or cam stream
 * We autodetect features objects and homographys using GMS matcher (BSD3)
 * and we build cam calib matrix from it
 */
#include <iostream>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/flann/miniflann.hpp>
#include "gms_matcher.h"

#include <garfeild.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

void usage(const char *s) {
    cerr << "Builds and outputs camera_c.txt camera_r_t.txt view_r_t.txt\n"
         << " usage:\n" << s
         << "[<video file>] \n";
    exit(1);
}

int main( int argc, char** argv )
{
    const char *captureSrc = "./video.avi";

    // parse command line
    for (int i=1; i<argc; i++) {
        if (argv[i][0]=='-') {
            usage(argv[0]);
        } else {
            captureSrc = argv[i];
        }
    }

    VideoCapture capture(captureSrc);

    if( !capture.isOpened() )
    {
        cerr <<"Could not initialize capturing from " << captureSrc << " ...\n";
        return -1;
    }

    CamCalibration calib;

    Mat frame;
    capture >> frame;

    auto size = frame.size();
    calib.AddCamera(size.width, size.height);

    int nbHomography =0;
    for(;;)
    {
        // acquire image
        Mat img1, img2;

        capture >> img1;
        if (img1.empty()) {
            break;
        }

        capture >> img2;
        if (img2.empty()) {
            break;
        }

        //Detect all features
        vector<KeyPoint> kp1, kp2;
        Mat d1, d2;
        vector<DMatch> matches_all, matches_gms;

        Ptr<ORB> orb = ORB::create(10000);
        orb->setFastThreshold(0);

        orb->detectAndCompute(img1, Mat(), kp1, d1);
        orb->detectAndCompute(img2, Mat(), kp2, d2);

#ifdef USE_GPU
        GpuMat gd1(d1), gd2(d2);
	Ptr<cuda::DescriptorMatcher> matcher = cv::cuda::DescriptorMatcher::createBFMatcher(NORM_HAMMING);
	matcher->match(gd1, gd2, matches_all);
#else
        BFMatcher matcher(NORM_HAMMING);
        matcher.match(d1, d2, matches_all);
#endif

        // GMS filter
        std::vector<bool> vbInliers;
        gms_matcher gms(kp1, img1.size(), kp2, img2.size(), matches_all);
        int num_inliers = gms.GetInlierMask(vbInliers, false, false);
        cout << "Get total " << num_inliers << " matches." << endl;

        // collect matches
        for (size_t i = 0; i < vbInliers.size(); ++i)
        {
            if (vbInliers[i] == true)
            {
                matches_gms.push_back(matches_all[i]);
            }
        }

        //-- Localize the object
        std::vector<Point2f> obj;
        std::vector<Point2f> scene;
        for( size_t i = 0; i < matches_gms.size(); i++ )
        {
            //-- Get the keypoints from the good matches
            obj.push_back( kp1[ matches_gms[i].queryIdx ].pt );
            scene.push_back( kp2[ matches_gms[i].trainIdx ].pt );
        }

        // Get matches that are near to point
        flann::KDTreeIndexParams indexParams;
        flann::Index kdtree(Mat(obj).reshape(1), indexParams);
        vector<float> query;
        query.push_back( size.width/4 + rand() % (size.width / 2) );
        query.push_back( size.height/4 + rand() % (size.height / 2 ));
        vector<int> indices;
        vector<float> dists;
        int pts = 9;

        kdtree.knnSearch(query, indices, dists, pts);

        std::vector<Point2f> obj2;
        std::vector<Point2f> scene2;
        for( size_t i = 0; i < pts; i++ )
        {
            //-- Get the keypoints from the good matches
            obj2.push_back( obj[i] );
            scene2.push_back( scene[i] );
        }

        Mat H = findHomography( obj2, scene2, RANSAC );

        // run the detector
        static std::vector<CamCalibration::s_struct_points> bpts;
        bpts.clear();

        for (int i=0; i<pts; ++i) {
            bpts.push_back(CamCalibration::s_struct_points(obj2[i].x, obj2[i].y, scene2[i].x, scene2[i].y));
        }
        CvMat cH = H;
        calib.AddHomography(0, bpts, &cH );

        nbHomography++;
        cout << nbHomography << " homographies.\n";
        if (nbHomography >=140) {
            if (calib.Calibrate(
                    50, // max hom
                    2,   // random
                    3,
                    3,   // padding ratio 1/2
                    0,
                    0,
                    0.0078125,	//alpha
                    0.9,		//beta
                    0.001953125,//gamma
                    12,	  // iter
                    0.05, //eps
                    3   //postfilter eps
            )) {
                calib.PrintOptimizedResultsToFile1();
                break;
            }
        }
    }
    return 0;
}