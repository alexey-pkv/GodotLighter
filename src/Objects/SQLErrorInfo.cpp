#include "SQLErrorInfo.h"


using namespace godot;
using namespace sqlighter;


void SQLErrorInfo::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("err_code"),				&SQLErrorInfo::err_code);
	ClassDB::bind_method(D_METHOD("err_sqlite_code"),		&SQLErrorInfo::err_sqlite_code);
	ClassDB::bind_method(D_METHOD("err_str"),				&SQLErrorInfo::err_str);
	ClassDB::bind_method(D_METHOD("err_lighter_message"),	&SQLErrorInfo::err_lighter_message);
	ClassDB::bind_method(D_METHOD("err_sqlite_message"),	&SQLErrorInfo::err_sqlite_message);
	ClassDB::bind_method(D_METHOD("err_query"),				&SQLErrorInfo::err_query);
}


int SQLErrorInfo::err_code() const
{
	return m_e.code();
}

int SQLErrorInfo::err_sqlite_code() const
{
	return m_e.sqlite_code();
}

gstr SQLErrorInfo::err_str() const
{
	return m_e.what();
}

gstr SQLErrorInfo::err_lighter_message() const
{
	return str2str(m_e.message());
}

gstr SQLErrorInfo::err_sqlite_message() const
{
	return { m_e.what_sqlite3() };
}

gstr SQLErrorInfo::err_query() const
{
	return str2str(m_e.query());
}
