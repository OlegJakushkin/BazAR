

noinst_PROGRAMS=interactive

interactive_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
interactive_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a

interactive_SOURCES=interactive.cpp
