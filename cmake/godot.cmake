message(STATUS "Godot directory: ${CMAKE_SOURCE_DIR}/godot-cpp")
message(STATUS "scons command: scons platform=${GODOTLIGHTER_PLATFORM}")

add_custom_target(build_godot_api
	COMMAND scons platform=${GODOTLIGHTER_PLATFORM}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/godot-cpp
)


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(GODOTLIGHTER_GODOT_LIB "${CMAKE_SOURCE_DIR}/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a" CACHE INTERNAL "")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(GODOTLIGHTER_GODOT_LIB "${CMAKE_SOURCE_DIR}/godot-cpp/bin/libgodot-cpp.windows.template_debug.x86_64.lib" CACHE INTERNAL "")
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()


message(STATUS "Godot API file: ${GODOTLIGHTER_GODOT_LIB}")
