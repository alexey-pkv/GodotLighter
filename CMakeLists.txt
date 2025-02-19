cmake_minimum_required(VERSION 3.29)


############################
### Project Settings	####
############################

project(GodotLighter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


############################
### Includes ###############
############################

add_subdirectory("cmake")


#############################
### Variables ###############
#############################

file(GLOB_RECURSE GODOTLIGHTER_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE GODOTLIGHTER_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)


############################
### Targets		 ###########
############################

add_library(godotlighter EXCLUDE_FROM_ALL SHARED ${GODOTLIGHTER_SOURCE})

# This will copy the extension and library files after godotlighter is build.
define_example_target()

set_target_properties(godotlighter PROPERTIES 
	OUTPUT_NAME "godotlighter.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64"
	ARCHIVE_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	LIBRARY_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}"
	RUNTIME_OUTPUT_DIRECTORY "${GODOTLIGHTER_BIN}")

target_include_directories(godotlighter PRIVATE ${GODOTLIGHTER_OUT})
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gen/include/")
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/include/")
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gdextension/")
target_include_directories(godotlighter PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries(godotlighter PRIVATE sqlighter)
target_link_libraries(godotlighter PRIVATE ${GODOTLIGHTER_GODOT_LIB})
target_link_libraries(godotlighter PRIVATE sqlite3)

if (MSVC)
	target_compile_definitions(godotlighter PRIVATE TYPED_METHOD_BIND)
	target_compile_definitions(sqlighter PRIVATE "_ITERATOR_DEBUG_LEVEL=0")
	target_compile_definitions(godotlighter PRIVATE "_ITERATOR_DEBUG_LEVEL=0")
	
	set_property(TARGET godotlighter PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
	set_property(TARGET sqlite3 PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
	set_property(TARGET sqlighter PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
endif ()
