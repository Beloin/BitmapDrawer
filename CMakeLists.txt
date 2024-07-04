cmake_minimum_required(VERSION 3.1...3.29)

project(bitmap VERSION 1.0 LANGUAGES CXX)

add_executable(bitmap
        cmd/main.cpp
        examples/cpp_symbol.h
        )

add_library(src_lib src/bitmap.h src/bitmap.cpp src/BitmapWriter.h src/BitmapWriter.cpp)

add_subdirectory(./ui)

target_include_directories(bitmap PUBLIC ./src ./ui)

target_link_libraries(bitmap src_lib ui_lib)
