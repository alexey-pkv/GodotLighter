#include "SQLErrors.h"


#include "GLighter.h"
#include <godot_cpp/classes/engine.hpp>


using namespace godot;


void SQLErrors::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("has_err"),							&SQLErrors::has_err);
	ClassDB::bind_method(D_METHOD("last_err"),							&SQLErrors::last_err);
	ClassDB::bind_method(D_METHOD("reset_error"),						&SQLErrors::reset_error);
	
	ClassDB::bind_method(D_METHOD("set_print_errors", "is_to_print"),	&SQLErrors::set_print_errors);
	ClassDB::bind_method(D_METHOD("get_print_errors"),					&SQLErrors::get_print_errors);
	
	
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "print_errors"), "set_print_errors", "get_print_errors");
	
	
	ADD_SIGNAL(MethodInfo("on_error", PropertyInfo(Variant::OBJECT, "error", PROPERTY_HINT_NODE_TYPE, "SQLErrorInfo")));
}


bool SQLErrors::has_err() const
{
	return m_e != nullptr;
}

Ref<SQLErrorInfo> SQLErrors::last_err() const
{
	return m_e;
}

void SQLErrors::reset_error()
{
	m_e.unref(); 
}

bool SQLErrors::get_print_errors() const
{
	return m_printErrors;
}

void SQLErrors::set_print_errors(bool to)
{
	m_printErrors = to;
}

void SQLErrors::handle_error_only(const sqlighter::SQLighterException& e)
{
	m_e.instantiate();
	m_e->set_err(e);
	
	// Print error only after it was set.
	if (m_printErrors && !Engine::get_singleton()->is_editor_hint())
	{
		_err_print_error(__FUNCTION__, __FILE__, __LINE__, e.what(), true);
	}
	
	emit_signal("on_error", m_e);
}

void SQLErrors::handle_error(const excp& e)
{
	handle_error_only(e);
	
	if (m_propagateToGlobal)
	{
		GLighter::handle_error(e);
	}
}