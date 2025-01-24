#include "SQLNode.h"


#include "godotlighter_version.h"

#include <sqlite3.h>
#include <sqlighter.h>


using namespace godot;


void SQLNode::_bind_methods()
{
	ClassDB::bind_static_method("SQLNode", D_METHOD("sqlighter_version"), &sqlighter_version);
}


godot::String SQLNode::sqlighter_version()
{
	return SQLIGHTER_VERSION;
}

godot::String SQLNode::library_version()
{
	return GODOTLIGHTER_VERSION;
}

godot::String SQLNode::sqlite_version()
{
	return sqlite3_libversion();
}
