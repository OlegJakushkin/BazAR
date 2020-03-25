

noinst_PROGRAMS=singlecalib augment3d

singlecalib_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
singlecalib_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a
singlecalib_SOURCES=singlecalib.cpp

augment3d_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
augment3d_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a
augment3d_SOURCES=augment3d.cpp

