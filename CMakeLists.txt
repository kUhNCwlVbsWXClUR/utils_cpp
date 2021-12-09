project(utils)

#set (CMAKE_CXX_STANDARD c99)

cmake_minimum_required(VERSION 3.10.2)

option(BUILD_SHARED_AND_STATIC_LIBS "Build both shared and static libraries" on)

set(UTILS_LIB utils)

set(CMAKE_C_FLAGS  "-fPIC")

set(CMAKE_BUILD_TYPE Release ON)

FILE(GLOB SRC_FILES "src/*.c")
include_directories("${PROJECT_SOURCE_DIR}/include/")

if(NOT BUILD_SHARED_AND_STATIC_LIBS)
	add_library("${UTILS_LIB}" SHARED ${SRC_FILES})
else()
	add_library("${UTILS_LIB}" SHARED ${SRC_FILES})
	add_library("${UTILS_LIB}-static" STATIC ${SRC_FILES})
	set_target_properties(${UTILS_LIB}-static PROPERTIES OUTPUT_NAME "${UTILS_LIB}")
endif()

	
set_target_properties(${UTILS_LIB} 
	PROPERTIES 
		VERSION 1.0.1
		SOVERSION 1)


FILE(GLOB HDR_FILES "${PROJECT_SOURCE_DIR}/include/utils_cpp/*.h")

set(LINK_LIB_LIST)

list(APPEND LINK_LIB_LIST ${UTILS_LIB})

install(FILES ${HDR_FILES} DESTINATION include/)
install(TARGETS "${UTILS_LIB}" "${UTILS_LIB}-static"  DESTINATION lib)
#install(TARGETS lib_shared DESTINATION lib)
#install(TARGETS lib_static DESTINATION lib)

add_subdirectory(tests)
