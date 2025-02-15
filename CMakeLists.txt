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

file(GLOB_RECURSE GODOTLIGHTER_DEMOS_BIN 
	"${CMAKE_CURRENT_SOURCE_DIR}/demos/*/*/bin/"
)





############################
### Targets		 ###########
############################

add_library(godotlighter EXCLUDE_FROM_ALL SHARED ${GODOTLIGHTER_SOURCE})

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

# TODO: Optimize this part:
# add_dependencies(godotlighter godotlighter_build_godot_cpp)

# TODO: Change, as currently this works only for linux and only for debug.
if (UNIX)
	add_custom_command(
		TARGET godotlighter POST_BUILD
		COMMAND cp "${GODOTLIGHTER_OUT}/libgodotlighter.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64.so" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/versions/bin"
		COMMAND cp "${GODOTLIGHTER_OUT}/libgodotlighter.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64.so" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/error_handling/bin"
		
		COMMAND cp "${GODOTLIGHTER_OUT}/godotlighter.gdextension" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/versions/bin"
		COMMAND cp "${GODOTLIGHTER_OUT}/godotlighter.gdextension" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/error_handling/bin"
		
		COMMENT "Copying file to each bin directory after build"
	)
elseif(WIN32)
	add_custom_command(
		TARGET godotlighter POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${GODOTLIGHTER_OUT}/godotlighter.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64.dll" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/versions/bin"
		COMMAND ${CMAKE_COMMAND} -E copy "${GODOTLIGHTER_OUT}/godotlighter.${GODOTLIGHTER_PLATFORM}.template_debug.x86_64.dll" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/error_handling/bin"
		
		COMMAND ${CMAKE_COMMAND} -E copy "${GODOTLIGHTER_OUT}/godotlighter.gdextension" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/versions/bin"
		COMMAND ${CMAKE_COMMAND} -E copy "${GODOTLIGHTER_OUT}/godotlighter.gdextension" "${CMAKE_CURRENT_SOURCE_DIR}/demos/4.3/error_handling/bin"
		
		COMMENT "Copying file to each bin directory after build"
	)
endif ()