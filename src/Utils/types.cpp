#include "types.h"


#include <godot_cpp/variant/variant.hpp>


using namespace sqlighter;


godot::Variant godot::val2var(const ScalarValue& val)
{
	switch (val.get_type())
	{
		case ScalarValue::type::INT:
			return { val.get_int64() };
			
		case ScalarValue::type::DOUBLE:
			return { val.get_double() };
			
		case ScalarValue::type::TEXT:
			return { str2str(val.get_str()) };
			
		case ScalarValue::type::BLOB:
		case ScalarValue::type::NULL_VAL:
		default:
			return { nullptr };
	}
}

bool godot::var2val(const godot::Variant& var, BindValue& into)
{
	switch (var.get_type())
	{
		case godot::Variant::Type::BOOL:
			into = ((int)var == 0 ? 0 : 1);
			return true;
		
		case godot::Variant::Type::INT:
			into = (int64_t)var;
			return true;

		case godot::Variant::Type::FLOAT:
			into = (double)var;
			return true;

		case godot::Variant::Type::STRING:
			into = { str2str((gstr)var) };
			return true;

		case godot::Variant::Type::NIL:
			into = BindValue::null;
			return true;
		
		default:
			return false;
	}
}

godot::vec<BindValue> godot::var2val(const godot::Array& vars)
{
	if (vars.size() == 0)
		return {};
	
	vec<BindValue> into {};
	into.reserve(vars.size());
	
	for (int i = 0; i < vars.size(); i++)
	{
		BindValue v;
		
		if (!var2val(vars[i], v))
		{
			std::ostringstream ss {};
			auto type = vars[i].get_type();
			auto name = Variant::get_type_name(type);
			
			ss
				<< "The bind argument at index [" << i << "] is not of a valid type. Got `" 
				<< str2str(name) << "`. Only, `bool`, `int`, `float`, `string` and `null` are supported.";
			
			throw excp(SQLIGHTER_ERR_VALUE, ss.str());
		}
		
		into.emplace_back(std::move(v));
	}
	
	return into;
}