cmake_minimum_required(VERSION 3.5.1)
project( groud_truth )


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O0 -g")

include_directories (${PROJECT_SOURCE_DIR}/include)  #增加Hello为include目录
link_directories (${PROJECT_SOURCE_DIR}/lib) 


find_package(Threads REQUIRED)

add_executable(apriltag-detection-demo 
    src/main.cpp 
 )

target_link_libraries(apriltag-detection-demo 
    pthread
libapriltag.a
    opencv_imgproc.so
    opencv_xfeatures2d.so
    opencv_features2d.so
    opencv_calib3d.so
    opencv_core.so
    opencv_imgcodecs.so
    opencv_highgui.so
    opencv_aruco.so
    libopencv_videoio.so
 )
