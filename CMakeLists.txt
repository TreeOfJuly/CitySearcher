cmake_minimum_required(VERSION 3.26)
project(CitySearcher)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CitySearcher
        hashTable.h
        main.cpp
        parsingCSV.h)
