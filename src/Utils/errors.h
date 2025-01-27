#ifndef GODOTLIGHTER_ERRORS_H
#define GODOTLIGHTER_ERRORS_H


#include <godot_cpp/variant/variant.hpp>


namespace godot
{
	void column_name_not_a_string_error(const Variant& value, int at);
	void expecting_array_error(const Variant& value, int at);
}


#endif