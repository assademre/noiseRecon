cmake_minimum_required(VERSION 3.16)
project(noiseReckon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(noiseReckon
    src/main.cpp
    src/field/field.cpp
    src/forward/projection.cpp
    src/noise/noiseModel.cpp
    src/reconstruction/reconstructor.cpp
)

target_include_directories(noiseReckon PRIVATE src)

