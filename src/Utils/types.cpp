#include "types.h"


#include <godot_cpp/variant/variant.hpp>


godot::Variant godot::val2var(const sqlighter::ScalarValue& val)
{
	switch (val.get_type())
	{
		case sqlighter::ScalarValue::type::INT:
			return { val.get_int64() };
			
		case sqlighter::ScalarValue::type::DOUBLE:
			return { val.get_double() };
			
		case sqlighter::ScalarValue::type::TEXT:
			return { str2str(val.get_str()) };
			
		case sqlighter::ScalarValue::type::BLOB:
		case sqlighter::ScalarValue::type::NULL_VAL:
		default:
			return { nullptr };
	}
}