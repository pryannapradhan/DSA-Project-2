cmake_minimum_required(VERSION 3.30)
project(DSAProject2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DSAProject2 main.cpp
        sort_merge.cpp
        sort_heap.cpp
        Restaurant.h
        sort_merge.h
        sort_heap.h
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/150K_Restaurants_Cleaned.csv"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
