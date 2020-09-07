from osrf/ros:kinetic-desktop-full

#install SSH
run apt-get -y update
RUN apt-get install -y openssh-server
RUN mkdir /var/run/sshd

RUN echo 'root:root' |chpasswd

RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -ri 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config

RUN mkdir /root/.ssh

RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
run apt-get update --fix-missing && apt-get upgrade -y
run apt-get install -y gdb rsync
#end install SSH

#install opencv 3.4
run apt-get update && apt-get install -y libboost-all-dev git libgflags-dev libgoogle-glog-dev libatlas-base-dev libsuitesparse-dev software-properties-common

run wget http://bitbucket.org/eigen/eigen/get/3.3.7.zip && \
    unzip 3.3.7.zip && \
    mv eigen* eigen && ls && \
    cd eigen && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr/ .. && \
    make -j $(nproc) && \
    make install && \
    ldconfig


run git clone --recursive https://ceres-solver.googlesource.com/ceres-solver && \
    cd ceres-solver && \
    git fetch && git fetch --tags && \
    git checkout 1.13.0 && \
    mkdir build && cd build && \
    cmake  -DCMAKE_INSTALL_PREFIX=/usr/ .. && \
    make -j $(nproc) && \
    make install

run \
    wget https://github.com/Itseez/opencv/archive/3.4.10.zip && \
    unzip 3.4.10.zip && \
    mv opencv-3.4.10/ opencv/ && \
    rm -rf 3.4.10.zip && \
    cd / && \
    wget https://github.com/opencv/opencv_contrib/archive/3.4.10.zip -O 3.4.10-contrib.zip && \
    unzip 3.4.10-contrib.zip && \
    mv opencv_contrib-3.4.10 opencv_contrib && \
    rm -rf 3.4.10-contrib.zip && \
    cd opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/ \
        -D INSTALL_C_EXAMPLES=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D CPU_DISPATCH=SSE4_2,AVX \
        -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
        -D BUILD_EXAMPLES=OFF .. && \
    make -j $(nproc) && \
    make install && \
    ldconfig
#end install opencv

#build flame
run git clone --recursive https://github.com/robustrobotics/flame
WORKDIR ./flame
run mkdir -p ./dependencies/src
#run ./scripts/eigen.sh ./dependencies/src ./dependencies
run ./scripts/sophus.sh ./dependencies/src ./dependencies
run cp ./scripts/env.sh ./dependencies
run mkdir ./build && mkdir ./install
run /bin/bash -c "source /opt/ros/kinetic/setup.sh && \
    source ./dependencies/env.sh && \
    cd ./build \
    && cmake -D CMAKE_INSTALL_PREFIX=/usr/ .. \
    && cd ../ && make -C build  -j48 && make -C build install"
run ./build/bin/flame_test
#end build flame

EXPOSE 22

CMD    ["/usr/sbin/sshd", "-D"]
