#include "GLighter.h"


#include "godotlighter_version.h"

#include <sstream>
#include <sqlite3.h>
#include <sqlighter.h>

#include <godot_cpp/core/class_db.hpp>


using namespace godot;


Ref<SQLErrors>	GLighter::m_errors		{nullptr };
		

void GLighter::_bind_methods()
{
	ClassDB::bind_static_method("GLighter", D_METHOD("errors"), &errors);
	
	ClassDB::bind_static_method("GLighter", D_METHOD("sqlighter_version"),	&sqlighter_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("library_version"),	&godotlighter_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("sqlite_version"),		&sqlite_version);
	ClassDB::bind_static_method("GLighter", D_METHOD("versions_info"),		&versions_info);
}


Ref<SQLErrors> GLighter::errors()
{
	if (m_errors == nullptr)
	{
		m_errors.instantiate();
	}
	
	return m_errors;
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
