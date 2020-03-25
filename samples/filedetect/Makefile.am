

EXTRA_DIST=a.jpg b.jpg c.jpg d.jpg e.jpg f.jpg model.jpg printme.jpg

noinst_PROGRAMS=filedetect

filedetect_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
filedetect_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a -lopencv_imgproc ../../starter/libstarter.a

filedetect_SOURCES=filedetect.cpp
