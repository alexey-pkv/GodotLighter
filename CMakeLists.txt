cmake_minimum_required(VERSION 3.30)


############################
### Project Settings	####
############################

project(GodotLighter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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


############################
### Define Version #########
############################

set(GODOTLIGHTER_VERSION_MAJOR 1)
set(GODOTLIGHTER_VERSION_MINOR 0)
set(GODOTLIGHTER_VERSION_PATCH 0)

set(GODOTLIGHTER_VERSION "${GODOTLIGHTER_VERSION_MAJOR}.${GODOTLIGHTER_VERSION_MINOR}.${GODOTLIGHTER_VERSION_PATCH}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/godotlighter_version.h.in"
    "${GODOTLIGHTER_BIN}/godotlighter_version.h"
    @ONLY
)


############################
### Clean 	 ###############
############################

add_custom_target(purge
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning the build directory"
)


############################
### Targets		 ###########
############################

add_library(godotlighter SHARED ${GODOTLIGHTER_SOURCE})

set_target_properties(godotlighter PROPERTIES 
	OUTPUT_NAME "godotlighter"
	ARCHIVE_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	LIBRARY_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	RUNTIME_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}")

target_include_directories(godotlighter PRIVATE ${GODOTLIGHTER_BIN})