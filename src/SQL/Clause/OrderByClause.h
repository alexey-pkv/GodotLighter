#ifndef GODOTLIGHTER_ORDERBYCLAUSE_H
#define GODOTLIGHTER_ORDERBYCLAUSE_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_order_by()
	{
		ClassDB::bind_method(D_METHOD("order_by_exp", "exp", "binds"),		&self::order_by_exp);
		ClassDB::bind_method(D_METHOD("order_by_field", "field", "asc"),	&self::order_by_field);
		ClassDB::bind_method(D_METHOD("order_by_field_asc", "field"),		&self::order_by_field_asc);
		ClassDB::bind_method(D_METHOD("order_by_field_desc", "field"),		&self::order_by_field_desc);
	}
}


#endif