#include "SQL.h"


#include "godotlighter_version.h"

#include <sqlite3.h>
#include <sqlighter.h>


using namespace godotlighter;


const char* SQL::sqlighter_version()
{
	return SQLIGHTER_VERSION;
}

const char* SQL::library_version()
{
	return GODOTLIGHTER_VERSION;
}

const char* SQL::sqlite_version()
{
	return sqlite3_libversion();
}
