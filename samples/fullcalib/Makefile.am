

noinst_PROGRAMS=fullcalib

fullcalib_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
fullcalib_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc -lopencv_calib3d  -lopencv_imgcodecs ../../starter/libstarter.a \
		 @GLEW_LIBS@
fullcalib_SOURCES=fullcalib.cpp calibmodel.cpp calibmodel.h

