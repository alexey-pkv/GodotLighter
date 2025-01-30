#ifndef GODOTLIGHTER_LIMITCLAUSE_H
#define GODOTLIGHTER_LIMITCLAUSE_H


#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self>
	void bind_limit()
	{
		ClassDB::bind_method(D_METHOD("limit_by", "count"),			&self::limit_by);
		ClassDB::bind_method(D_METHOD("limit", "offset", "count"),	&self::limit);
		ClassDB::bind_method(D_METHOD("page", "page", "page_size"),	&self::page);
	}
}


#endif