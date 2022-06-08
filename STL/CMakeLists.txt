cmake_minimum_required (VERSION 3.8)

set (TARGET_NAME STL)

add_library(${TARGET_NAME} STATIC "Header/Vector.h"
								  "Header/VectorIterator.h"
								  "Source/lib.cpp")
