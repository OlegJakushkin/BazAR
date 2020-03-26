from osrf/ros:kinetic-desktop-full

#install SSH
run apt-get -y update && apt-get update --fix-missing && apt-get upgrade -y
run apt-get install -y gdb rsync git nano htop mc wget curl youtube-dl automake
run youtube-dl -U

run \
    wget https://github.com/Itseez/opencv/archive/3.2.0.zip && \
    unzip 3.2.0.zip && \
    mv opencv-3.2.0/ opencv/ && \
    rm -rf 3.2.0.zip && \
    cd / && \
    wget https://github.com/opencv/opencv_contrib/archive/3.2.0.zip -O 3.2.0-contrib.zip && \
    unzip 3.2.0-contrib.zip && \
    mv opencv_contrib-3.2.0 opencv_contrib && \
    rm -rf 3.2.0-contrib.zip && \
    cd opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/ \
        -D INSTALL_C_EXAMPLES=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
        -D BUILD_EXAMPLES=OFF .. && \
    make -j $(nproc) && \
    make install && \
    ldconfig 
#end install opencv

#build BazAR
run git clone --recursive https://github.com/OlegJakushkin/BazAR
WORKDIR ./BazAR
run ls && chmod a+x ./configure && ./configure --prefix=/usr
run make -j $(nproc)
run make install
