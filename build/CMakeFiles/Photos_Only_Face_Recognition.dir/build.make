# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build

# Include any dependencies generated for this target.
include CMakeFiles/Photos_Only_Face_Recognition.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Photos_Only_Face_Recognition.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Photos_Only_Face_Recognition.dir/flags.make

CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o: CMakeFiles/Photos_Only_Face_Recognition.dir/flags.make
CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o -c /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/main.cpp

CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/main.cpp > CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.i

CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/main.cpp -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.s

CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o: CMakeFiles/Photos_Only_Face_Recognition.dir/flags.make
CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o: ../src/facedetect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o -c /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/facedetect.cpp

CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/facedetect.cpp > CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.i

CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/facedetect.cpp -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.s

CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o: CMakeFiles/Photos_Only_Face_Recognition.dir/flags.make
CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o: ../src/requesthandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o -c /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/requesthandler.cpp

CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/requesthandler.cpp > CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.i

CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/src/requesthandler.cpp -o CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.s

# Object files for target Photos_Only_Face_Recognition
Photos_Only_Face_Recognition_OBJECTS = \
"CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o" \
"CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o" \
"CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o"

# External object files for target Photos_Only_Face_Recognition
Photos_Only_Face_Recognition_EXTERNAL_OBJECTS =

Photos_Only_Face_Recognition: CMakeFiles/Photos_Only_Face_Recognition.dir/src/main.cpp.o
Photos_Only_Face_Recognition: CMakeFiles/Photos_Only_Face_Recognition.dir/src/facedetect.cpp.o
Photos_Only_Face_Recognition: CMakeFiles/Photos_Only_Face_Recognition.dir/src/requesthandler.cpp.o
Photos_Only_Face_Recognition: CMakeFiles/Photos_Only_Face_Recognition.dir/build.make
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_stitching.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_superres.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_videostab.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_aruco.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_bgsegm.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_bioinspired.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_ccalib.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_dpm.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_face.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_freetype.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_fuzzy.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_hdf.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_hfs.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_img_hash.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_line_descriptor.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_optflow.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_reg.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_rgbd.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_saliency.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_stereo.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_structured_light.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_surface_matching.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_tracking.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_xfeatures2d.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_ximgproc.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_xobjdetect.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_xphoto.so.3.4.18
Photos_Only_Face_Recognition: /home/coco/Qt/6.4.1/gcc_64/lib/libQt6Gui.so.6.4.1
Photos_Only_Face_Recognition: /home/coco/Qt/6.4.1/gcc_64/lib/libQt6HttpServer.so.6.4.1
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_shape.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_highgui.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_videoio.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_video.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_datasets.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_plot.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_text.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_dnn.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_ml.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_imgcodecs.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_objdetect.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_calib3d.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_features2d.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_flann.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_photo.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_imgproc.so.3.4.18
Photos_Only_Face_Recognition: /usr/local/lib/libopencv_core.so.3.4.18
Photos_Only_Face_Recognition: /usr/lib/x86_64-linux-gnu/libGLX.so
Photos_Only_Face_Recognition: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Photos_Only_Face_Recognition: /home/coco/Qt/6.4.1/gcc_64/lib/libQt6WebSockets.so.6.4.1
Photos_Only_Face_Recognition: /home/coco/Qt/6.4.1/gcc_64/lib/libQt6Network.so.6.4.1
Photos_Only_Face_Recognition: /home/coco/Qt/6.4.1/gcc_64/lib/libQt6Core.so.6.4.1
Photos_Only_Face_Recognition: CMakeFiles/Photos_Only_Face_Recognition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Photos_Only_Face_Recognition"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Photos_Only_Face_Recognition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Photos_Only_Face_Recognition.dir/build: Photos_Only_Face_Recognition

.PHONY : CMakeFiles/Photos_Only_Face_Recognition.dir/build

CMakeFiles/Photos_Only_Face_Recognition.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Photos_Only_Face_Recognition.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Photos_Only_Face_Recognition.dir/clean

CMakeFiles/Photos_Only_Face_Recognition.dir/depend:
	cd /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build /home/coco/Documents/c++/projects/vs-code-c++/photos_only_face_recognition/build/CMakeFiles/Photos_Only_Face_Recognition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Photos_Only_Face_Recognition.dir/depend
