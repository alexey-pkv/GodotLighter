#ifndef GODOTLIGHTER_FROMCLAUSE_H
#define GODOTLIGHTER_FROMCLAUSE_H


#include "Utils/types.h"

#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_from()
	{
		ClassDB::bind_method(D_METHOD("as", "alias"),						&self::as);
		ClassDB::bind_method(D_METHOD("from", "table"),						&self::from);
		ClassDB::bind_method(D_METHOD("from_scheme", "scheme", "table"),	&self::from_scheme);
	}
}


#endif