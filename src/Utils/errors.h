#ifndef GODOTLIGHTER_ERRORS_H
#define GODOTLIGHTER_ERRORS_H


#include "types.h"

#include <godot_cpp/variant/variant.hpp>


namespace godot
{
	excp column_name_not_a_string_error(const Variant& value, int at);
	excp expecting_array_error(const Variant& value, int at);
}


#endif