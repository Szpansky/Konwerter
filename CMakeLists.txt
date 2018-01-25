cmake_minimum_required(VERSION 3.9)
project(Konwerter)

set(CMAKE_CXX_STANDARD 11)

add_executable(Konwerter main.cpp Koder/Koder.cpp Koder/Koder.h Dekoder/Dekoder.cpp Dekoder/Dekoder.h Tools/Structs.cpp Tools/Structs.h Tools/Functions.cpp Tools/Functions.h)