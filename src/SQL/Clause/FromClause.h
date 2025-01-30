#ifndef GODOTLIGHTER_FROMCLAUSE_H
#define GODOTLIGHTER_FROMCLAUSE_H


#include "Utils/types.h"

#include <godot_cpp/core/class_db.hpp>


namespace godot
{
	template<class self, class cmd>
	class FromClause
	{
	private:
		inline Ref<self> get_self() { return Ref<self>(static_cast<self*>(this)); }
		
		
	protected:
		virtual cmd& get_from_command() = 0;
		
		
	public:
		Ref<self> as(const gstr& alias)
		{
			get_from_command().as(str2str(alias));
			return get_self();
		}
		
		Ref<self> from(const gstr& table)
		{
			get_from_command().from(str2str(table));
			return get_self();
		}
		
		Ref<self> from_scheme(const gstr& scheme, const gstr& table)
		{
			get_from_command().from(str2str(scheme), str2str(table));
			return get_self();
		}
		
		static const ::godot::StringName &get_class_static() {                                                                                                                             \
			static const ::godot::StringName string_name = ::godot::StringName("FromClause");                                                                                                  \
			return string_name;                                                                                                                                                            \
		}
	public:
		static void bind_from()
		{
			ClassDB::bind_method(D_METHOD("as", "alias"),						&self::as);
			ClassDB::bind_method(D_METHOD("from", "table"),						&self::from);
			ClassDB::bind_method(D_METHOD("from_scheme", "scheme", "table"),	&self::from_scheme);
		}
	};
		
		
	template<class self>
	void bind_from()
	{
		ClassDB::bind_method(D_METHOD("as", "alias"),						&self::as);
		ClassDB::bind_method(D_METHOD("from", "table"),						&self::from);
		ClassDB::bind_method(D_METHOD("from_scheme", "scheme", "table"),	&self::from_scheme);
	}
}


#endif