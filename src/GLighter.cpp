#include "GLighter.h"


#include "godotlighter_version.h"

#include <sstream>
#include <sqlite3.h>
#include <sqlighter.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>


using namespace godot;


Ref<SQLErrorInfo>	GLighter::m_e			{nullptr };
bool					GLighter::m_printErrors	{ true };
		

void GLighter::_bind_methods()
{
	ClassDB::bind_static_method("GLighter", D_METHOD("has_err"),							&has_err);
	ClassDB::bind_static_method("GLighter", D_METHOD("last_err"),							&last_err);
	ClassDB::bind_static_method("GLighter", D_METHOD("reset_error"),						&reset_error);
	ClassDB::bind_static_method("GLighter", D_METHOD("set_print_errors", "is_to_print"),	&set_print_errors);
		
	ClassDB::bind_static_method("GLighter", D_METHOD("sqlighter_version"),	&sqlighter_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("library_version"),	&godotlighter_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("sqlite_version"),		&sqlite_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("versions_info"),		&versions_info);
}


bool GLighter::has_err()
{
	return m_e == nullptr;
}

Ref<SQLErrorInfo> GLighter::last_err()
{
	return m_e;
}

void GLighter::reset_error()
{
	m_e.unref(); 
}

void GLighter::set_print_errors(bool to)
{
	m_printErrors = to;
}

void GLighter::handle_error(const sqlighter::SQLighterException& e)
{
	m_e.unref();
	
	m_e.instantiate();
	m_e->set_err(e);
	
	// Print error after it was set.
	if (m_printErrors)
	{
		_err_print_error(__FUNCTION__, __FILE__, __LINE__, e.what(), true);
	}
}


gstr GLighter::sqlighter_version()
{
	return SQLIGHTER_VERSION;
}

gstr GLighter::godotlighter_version()
{
	return GODOTLIGHTER_VERSION;
}

gstr GLighter::sqlite_version()
{
	return sqlite3_libversion();
}

gstr GLighter::versions_info()
{
	std::ostringstream ss;
	
	ss
		<< "GodotLighter : " << GODOTLIGHTER_VERSION	<< std::endl 
		<< "SQLighter    : " << SQLIGHTER_VERSION		<< std::endl
		<< "SQLite       : " << sqlite3_libversion();
	
	return str2str(ss);
}
