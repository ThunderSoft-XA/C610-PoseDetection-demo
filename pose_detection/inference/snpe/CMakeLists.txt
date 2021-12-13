#Cmake lowest  version 
CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
 
#project name
PROJECT(snpe_test CXX)
 
#allow gdb debug
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
 
#add C++11 support and other options
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})
 
# OpenCV Version: 3.4.3
find_package(PkgConfig REQUIRED)
set(OpenCV_DIR /usr/local/opencv/share/OpenCV)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "OpenCV Version: ${OpenCV_VERSION}")
message(STATUS "OpenCV Libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV Include path: ${OpenCV_INCLUDE_DIRS}")
 
# include file dir
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)
 
#add sub dir
#add_subdirectory(dict) 
 
#set all sources files in current dir to DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS) 
 
#get a executabl file
add_executable(snpe_test 
    ${DIR_SRCS}
) 
 
#add link libs
target_link_libraries(snpe_test
    ${OpenCV_LIBS}
    pthread
    m
    z

    /home/thundersoft/software/snpe-1.51/lib/x86_64-linux-clang/libSNPE.so
    #/home/thundersoft/Downloads/snpe-1.37.0/snpe-1.37.0.788/lib/x86_64-linux-clang/libSNPE.so
)