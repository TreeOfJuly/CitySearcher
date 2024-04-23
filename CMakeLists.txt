cmake_minimum_required(VERSION 3.26)
project(CitySearcherNew)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CitySearcherNew
        gui.h
        hashTable.h
        main.cpp
        parsingCSV.h
        toolbox.h)
