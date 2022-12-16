FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive # ignore user input required

ENV QT_DEBUG_PLUGINS=1
ENV QT_QPA_PLATFORM=xcb
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/home/coco/Qt/6.4.1/gcc_64/plugins
ENV QT_PLUGIN_PATH=/home/coco/Qt/6.4.1/gcc_64/plugins
ENV DISPLAY=:1

# Install required build dependencies
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git wget unzip

RUN wget https://github.com/Itseez/opencv/archive/3.3.1.zip -O opencv.zip \
	&& unzip opencv.zip \
	&& wget https://github.com/Itseez/opencv_contrib/archive/3.3.1.zip -O opencv_contrib.zip \
	&& unzip opencv_contrib \
	&& mkdir /opencv-3.3.1/cmake_binary \
	&& cd /opencv-3.3.1/cmake_binary \
	&& cmake -DOPENCV_EXTRA_MODULES_PATH=/opencv_contrib-3.3.1/modules \
	  -DBUILD_TIFF=ON \
	  -DBUILD_opencv_java=OFF \
	  -DWITH_CUDA=OFF \
	  -DENABLE_AVX=ON \
	  -DWITH_OPENGL=ON \
	  -DWITH_OPENCL=ON \
	  -DWITH_IPP=ON \
	  -DWITH_TBB=ON \
	  -DWITH_EIGEN=ON \
	  -DWITH_V4L=ON \
      -DWITH_QT=ON \
	  -DBUILD_TESTS=OFF \
	  -DBUILD_PERF_TESTS=OFF \
	  -DCMAKE_BUILD_TYPE=RELEASE \
	  -DBUILD_opencv_python3=ON \
	  -DCMAKE_INSTALL_PREFIX=$(python3.6 -c "import sys; print(sys.prefix)") \
	  -DPYTHON_EXECUTABLE=$(which python3.6) \
	  -DPYTHON_INCLUDE_DIR=$(python3.6 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
	  -DPYTHON_PACKAGES_PATH=$(python3.6 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())") .. \
	&& make install \
	&& rm /opencv.zip \
	&& rm /opencv_contrib.zip \
	&& rm -r /opencv-3.3.1 \
	&& rm -r /opencv_contrib-3.3.1



COPY . .
WORKDIR .

# Run cmake configure & build process
RUN mkdir ./release
RUN cmake -B/release -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /release

# Launch built application
CMD ["./release/Photos_Only_Face_Recognition"]