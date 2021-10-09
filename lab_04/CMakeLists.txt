cmake_minimum_required(VERSION 3.21)
project(lab_04)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} src/geometric_mean.h src/geometric_mean.cpp src/thread_structs.h src/threads.h
        src/threads.cpp src/timer.h src/timer.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)


add_executable(${PROJECT_NAME}_debug src/main.cpp)

target_link_libraries(${PROJECT_NAME}_debug PUBLIC ${PROJECT_NAME})