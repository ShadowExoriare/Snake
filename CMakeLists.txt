cmake_minimum_required(VERSION 3.9)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc")

add_executable(Snake main.cpp)

link_libraries(Snake
        -lopengl32
        -lglu32
        -lglew32
        -lglut32)
