#include "errors.h"


#include "types.h"
#include "GLighter.h"

#include <sstream>


using namespace godot;


excp godot::column_name_not_a_string_error(const Variant& value, int at)
{
	std::ostringstream ss {};
	auto type = value.get_type();
	auto name = Variant::get_type_name(type);
	
	ss
		<< "A column at index [" << at << "] is not a string. " 
		<< "Got `" << str2str(name) << "` instead";
	
	return { SQLIGHTER_ERR_VALUE, ss.str() };
}

excp godot::expecting_array_error(const Variant& value, int at)
{
	std::ostringstream ss {};
	auto type = value.get_type();
	auto name = Variant::get_type_name(type);
	
	ss
		<< "Expecting an array at index [" << at << "]. " 
		<< "Got `" << str2str(name) << "` instead";
	
	return { SQLIGHTER_ERR_VALUE, ss.str() };
}

