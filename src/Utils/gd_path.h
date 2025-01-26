#ifndef GODOTLIGHTER_GD_PATH_H
#define GODOTLIGHTER_GD_PATH_H


#include "types.h"

#include <filesystem>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


namespace godot
{
	namespace fs = std::filesystem;
	
	
	inline fs::path to_path(const gstr& str)
	{
		return ProjectSettings::get_singleton()->globalize_path(str).utf8().get_data();
	}
}


#endif