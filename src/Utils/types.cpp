#include "types.h"


#include <godot_cpp/variant/variant.hpp>


using namespace godot;
using namespace sqlighter;


void _throw_invalid_variant_type(const Variant& v, int index)
{
	std::ostringstream ss {};
	auto type = v.get_type();
	auto name = Variant::get_type_name(type);
	
	ss
		<< "The bind argument at index [" << index << "] is not of a valid type. Got `" 
		<< str2str(name) << "`. Only, `bool`, `int`, `float`, `string` and `null` are supported.";
	
	throw excp(SQLIGHTER_ERR_VALUE, ss.str());
}

void _throw_invalid_variant_type(const Variant& v)
{
	std::ostringstream ss {};
	auto type = v.get_type();
	auto name = Variant::get_type_name(type);
	
	ss
		<< "The bind argument is not of a valid type. Got `" 
		<< str2str(name) << "`. Only, `bool`, `int`, `float`, `string` and `null` are supported.";
	
	throw excp(SQLIGHTER_ERR_VALUE, ss.str());
}


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

Variant godot::val2var(const BindValue& val)
{
	switch (val.get_type())
	{
		case BindValue::type::INT_32:
			return { val.get_value().i32 };
			
		case BindValue::type::INT_64:
			return { val.get_value().i64 };
			
		case BindValue::type::DOUBLE:
			return { val.get_value().dbl };
			
		case BindValue::type::TEXT:
		case BindValue::type::TEXT_16:
		case BindValue::type::TEXT_64:
			return { str2str(val.get_str_value()) };
			
		case BindValue::type::NULL_VAL:
		default:
			return {nullptr };
	}
}

Array godot::val2var(const vec<BindValue>& val)
{
	Array a {};
	
	for (const auto& v : val)
	{
		a.push_back(val2var(v));
	}
	
	return a;
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

BindValue godot::var2val_unsafe(const godot::Variant& var)
{
	switch (var.get_type())
	{
		case godot::Variant::Type::BOOL:
			return ((int)var == 0 ? 0 : 1);
		
		case godot::Variant::Type::INT:
			return (int64_t)var;

		case godot::Variant::Type::FLOAT:
			return (double)var;

		case godot::Variant::Type::STRING:
			return { str2str((gstr)var) };

		case godot::Variant::Type::NIL:
			return BindValue::null;
		
		default:
			_throw_invalid_variant_type(var);
	}
	
	return BindValue::null;
}

godot::vec<BindValue> godot::var2val(const godot::Array& vars)
{
	if (vars.size() == 0)
		return {};
	
	vec<BindValue> into {};
	into.reserve(vars.size());
	
	for (int i = 0; i < vars.size(); i++)
	{
		BindValue bind;
		
		if (!var2val(vars[i], bind))
		{
			_throw_invalid_variant_type(vars[i], i);
		}
		
		into.emplace_back(std::move(bind));
	}
	
	return into;
}