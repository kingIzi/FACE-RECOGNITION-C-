cmake_minimum_required(VERSION 3.16)

project(Photos_Only_Face_Recognition LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)


set(CMAKE_PREFIX_PATH "/home/coco/Qt/6.4.1/gcc_64")

set(FACE_DETECTION_CONFIGURATION "${PROJECT_SOURCE_DIR}/assets/deploy.prototxt")
set(FACE_DETECTION_WEIGHTS "${PROJECT_SOURCE_DIR}/assets/res10_300x300_ssd_iter_140000_fp16.caffemodel")  
set(HAAR_CASCADE_FRONTAL_FACE_DEFAULT "${PROJECT_SOURCE_DIR}/assets/haarcascade_frontalface_alt.xml")
set(RECOGNITION_MODEL "${PROJECT_SOURCE_DIR}/assets/recognitionModel.xml")
set(DATASET_CSV "${PROJECT_SOURCE_DIR}/assets/dataset.txt")


set(ALL_SOURCE_FILES 
    src/main.cpp
    src/facedetect.cpp
    src/requesthandler.cpp
)

set(ALL_HEADER_FILES 
    include/facedetect.hpp
    include/requesthandler.hpp
)


include_directories(include/)

add_executable(${PROJECT_NAME} ${ALL_HEADER_FILES} ${ALL_SOURCE_FILES}) 

target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")
target_compile_definitions(${PROJECT_NAME} PRIVATE HAAR_CASCADE_FRONTAL_FACE_DEFAULT="${HAAR_CASCADE_FRONTAL_FACE_DEFAULT}")
target_compile_definitions(${PROJECT_NAME} PRIVATE RECOGNITION_MODEL="${RECOGNITION_MODEL}")
target_compile_definitions(${PROJECT_NAME} PRIVATE DATASET_CSV="${DATASET_CSV}")




target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17) 

target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(OpenCV REQUIRED) 
find_package(Qt6 REQUIRED COMPONENTS HttpServer Network Core Gui)
# find_package(cpprestsdk CONFIG REQUIRED)
#     target_link_libraries(main PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal)


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Qt6::Gui Qt6::Core Qt6::HttpServer 
Qt6::Network) 