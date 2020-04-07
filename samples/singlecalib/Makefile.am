

noinst_PROGRAMS=singlecalib augment3d cli

singlecalib_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
singlecalib_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a
singlecalib_SOURCES=singlecalib.cpp

augment3d_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
augment3d_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a
augment3d_SOURCES=augment3d.cpp

cli_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
cli_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc -lopencv_calib3d  -lopencv_imgcodecs ../../starter/libstarter.a
cli_SOURCES=gms_matcher.h cli.cpp
