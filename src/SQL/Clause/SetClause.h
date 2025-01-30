#ifndef GODOTLIGHTER_SETCLAUSE_H
#define GODOTLIGHTER_SETCLAUSE_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_set()
	{
		ClassDB::bind_method(D_METHOD("set", "field", "value"),				&self::set);
		ClassDB::bind_method(D_METHOD("set_exp", "expression", "binds"),	&self::set_exp);
	}
}


#endif