cmake_minimum_required(VERSION 3.10)
project(json)

set(CMAKE_CXX_STANDARD 11)

add_executable(json main.cpp json/json_object.cpp json/json_boolean.cpp json/json.h json/json_array.cpp json/json_string.cpp json/json_number.cpp json/json_type.cpp json/json.cpp)