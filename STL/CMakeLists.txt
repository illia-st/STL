cmake_minimum_required (VERSION 3.8)

set (TARGET_NAME STL)


add_library(${TARGET_NAME} STATIC 	"Header/Vector.h"
									"Header/VectorIterator.h"
									"Header/List.h"
									"Header/Abstract_List.h"
									"Source/lib.cpp"
									"Header/ListIterator.h"
									"Header/ListNode.h")

add_executable(Testing main.cpp)

set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${TARGET_NAME}-debug )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${TARGET_NAME}-relwidthdebinfo )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${TARGET_NAME}-release )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_MINSIZEREL ${TARGET_NAME}-minsizerel )
