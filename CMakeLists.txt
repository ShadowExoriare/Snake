cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME Snake)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc")
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Snake.cpp Snake.h Map.cpp Map.h GameRules.cpp GameRules.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} Snake.cpp)


set(SFML_ROOT H:/Works/Programming/C++/Snake/libs/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules")

find_package(SFML REQUIRED COMPONENTS audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
        endif()

