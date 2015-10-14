project(TSiD)

cmake_minimum_required(VERSION 2.8.9)

set(SERVER server0)
set(CLIENT client0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

include(cmake/config.cmake)

find_package(SFML 2.3 REQUIRED system network)

if(CMAKE_COMPILER_IS_GNUCXX)
	include(cmake/macros/gcc-settings.cmake)
elseif(CMAKE_COMPILER MATCHES "clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	include(cmake/macros/clang-settings.cmake)
endif()

add_subdirectory(src)
