cmake_minimum_required(VERSION 3.25)
project(asl23_image_quilting C)

set(CMAKE_C_STANDARD 11)

add_executable(asl23_image_quilting main.c helpers.h helpers.c image_quilting.c image_quilting.h)
