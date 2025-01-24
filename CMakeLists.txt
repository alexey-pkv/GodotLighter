cmake_minimum_required(VERSION 3.30)


############################
### Project Settings	####
############################

project(GodotLighter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


############################
### Includes ###############
############################

include(FetchContent)


#####################################
### Include SQLighter ###############
#####################################

FetchContent_Declare(
	sqlighter
	GIT_REPOSITORY	https://github.com/alexey-pkv/sqlighter.git
	GIT_TAG			v1.0.0
)

set(SQLIGHTER_BUILD_STATIC_LIBS ON)

FetchContent_MakeAvailable(sqlighter)
set_target_properties(sqlighter PROPERTIES POSITION_INDEPENDENT_CODE ON)


#############################
### Variables ###############
#############################

set(GODOTLIGHTER_BIN "${CMAKE_BINARY_DIR}/bin")

file(GLOB_RECURSE GODOTLIGHTER_SOURCE
	"./src/*.cpp"
)

file(GLOB_RECURSE GODOTLIGHTER_HEADERS
	"./src/*.h"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(GODOTLIGHTER_PLATFORM linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(GODOTLIGHTER_PLATFORM windows)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(GODOTLIGHTER_PLATFORM macos)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(GODOTLIGHTER_VERSION_MAJOR 1)
set(GODOTLIGHTER_VERSION_MINOR 0)
set(GODOTLIGHTER_VERSION_PATCH 0)

set(GODOTLIGHTER_VERSION "${GODOTLIGHTER_VERSION_MAJOR}.${GODOTLIGHTER_VERSION_MINOR}.${GODOTLIGHTER_VERSION_PATCH}")

set(GODOTLIGHTER_GODOT_VERSION "4.3")


############################
### Define Version #########
############################

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/godotlighter_version.h.in"
	"${GODOTLIGHTER_BIN}/godotlighter_version.h"
	@ONLY
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/godotlighter.gdextension"
	"${GODOTLIGHTER_BIN}/godotlighter.gdextension"
	@ONLY
)


############################
### Targets		 ###########
############################

add_custom_target(godotlighter_build_godot_cpp
    COMMAND scons platform=${GODOTLIGHTER_PLATFORM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp
    COMMENT "Building Godot C++ bindings for ${PLATFORM} using SCons"
)


add_library(godotlighter SHARED ${GODOTLIGHTER_SOURCE})

set_target_properties(godotlighter PROPERTIES 
	OUTPUT_NAME "godotlighter"
	ARCHIVE_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	LIBRARY_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	RUNTIME_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}")

target_include_directories(godotlighter PRIVATE ${GODOTLIGHTER_BIN})
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gen/include/")
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/include/")
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gdextension/")

target_link_libraries(godotlighter PRIVATE sqlighter)

# Optimize this part:
# add_dependencies(godotlighter godotlighter_build_godot_cpp)