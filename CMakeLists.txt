cmake_minimum_required(VERSION 3.0.0)
project(PBRayTracer VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(./header)
file(GLOB SRC_FILES ./src/*.cpp ./header/*.h)

add_executable(PBRayTracer ${SRC_FILES})