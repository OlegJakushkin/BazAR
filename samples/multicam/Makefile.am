
if FULLGL
openglprogs=multigl
else
openglprogs=
endif

noinst_PROGRAMS=multicam $(openglprogs)

multicam_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
multicam_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a  -lopencv_imgproc -lopencv_calib3d  -lopencv_imgcodecs ../../starter/libstarter.a \
		 @GLEW_LIBS@
multicam_SOURCES=multicam.cpp calibmodel.cpp calibmodel.h \
		 multigrab.h multigrab.cpp

multigl_CXXFLAGS=@OPENCV_CFLAGS@ -I@top_srcdir@/garfeild -I@top_srcdir@/starter
multigl_LDADD=@OPENCV_LIBS@ ../../garfeild/libgarfeild.a  -lopencv_imgproc -lopencv_calib3d  -lopencv_imgcodecs  ../../starter/libstarter.a \
		 @GLEW_LIBS@ @GLUT_LIBS@
multigl_SOURCES=multigl.cpp calibmodel.cpp calibmodel.h \
		 multigrab.h multigrab.cpp
