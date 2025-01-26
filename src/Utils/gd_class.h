#ifndef GODOTLIGHTER_GD_CLASS_H
#define GODOTLIGHTER_GD_CLASS_H


#include <godot_cpp/core/class_db.hpp>


#define AS_GD_CLASS(class_name, godot_type) \
/*********************************************************************************************/	\
	GDCLASS(class_name, godot_type); /* NOLINT(*-use-auto, *-default-arguments) */				\
	protected:																					\
		static void _bind_methods();															\
/****** AS_GD_CLASS **************************************************************************/

#endif