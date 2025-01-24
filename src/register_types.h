#ifndef GODOTLIGHTER_REGISTER_TYPES_H
#define GODOTLIGHTER_REGISTER_TYPES_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	void initialize_godotlighter_module(ModuleInitializationLevel p_level);
	void uninitialize_godotlighter_module(ModuleInitializationLevel p_level);
}


#endif
