cmake_minimum_required(VERSION 3.16)

project(HttpServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(server
  main.cpp
  server.cpp

  include/
  server.h
)
