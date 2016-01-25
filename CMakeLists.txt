cmake_minimum_required(VERSION 3.0)

project(dhus-fuse-incoming VERSION 0.1.0 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Fuse REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD On)
find_package(Threads REQUIRED)

set(SOURCES "src/incoming.c")

add_executable(dhus-fuse-incoming ${SOURCES})

target_link_libraries(dhus-fuse-incoming Fuse::LibFuse Threads::Threads)

