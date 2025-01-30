#ifndef GODOTLIGHTER_ORCLAUSE_H
#define GODOTLIGHTER_ORCLAUSE_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_or()
	{
		ClassDB::bind_method(D_METHOD("or_rollback"),	&self::or_rollback);
		ClassDB::bind_method(D_METHOD("or_fail"),		&self::or_fail);
		ClassDB::bind_method(D_METHOD("or_replace"),	&self::or_replace);
		ClassDB::bind_method(D_METHOD("or_ignore"),		&self::or_ignore);
		ClassDB::bind_method(D_METHOD("or_abort"),		&self::or_abort);	
	}
};


#endif