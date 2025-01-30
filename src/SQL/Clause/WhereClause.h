#ifndef GODOTLIGHTER_WHERECLAUSE_H
#define GODOTLIGHTER_WHERECLAUSE_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_where()
	{
		ClassDB::bind_method(D_METHOD("where", "expression", "binds"),		&self::where);
		ClassDB::bind_method(D_METHOD("where_null", "column"),				&self::where_null);
		ClassDB::bind_method(D_METHOD("where_not_null", "column"),			&self::where_not_null);
		ClassDB::bind_method(D_METHOD("by_field", "column", "value"),		&self::by_field);
	}
}


#endif