#include "SQLErrorInfo.h"


#include <exceptions/error_message.h>


using namespace godot;
using namespace sqlighter;


void SQLErrorInfo::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("code"), &SQLErrorInfo::code);
	ClassDB::bind_method(D_METHOD("error"), &SQLErrorInfo::error);
	
	ClassDB::bind_method(D_METHOD("err_additional_message"),	&SQLErrorInfo::err_additional_message);
	ClassDB::bind_method(D_METHOD("err_sqlite_code"),			&SQLErrorInfo::err_sqlite_code);
	ClassDB::bind_method(D_METHOD("err_sqlite_str"),			&SQLErrorInfo::err_sqlite_str);
	ClassDB::bind_method(D_METHOD("err_lighter_str"),			&SQLErrorInfo::err_lighter_str);
	ClassDB::bind_method(D_METHOD("err_query"),					&SQLErrorInfo::err_query);
}


int SQLErrorInfo::code() const
{
	return m_e.code();
}

gstr SQLErrorInfo::err_additional_message() const
{
	return str2str(m_e.message());
}

int SQLErrorInfo::err_sqlite_code() const
{
	return m_e.sqlite_code();
}

gstr SQLErrorInfo::error() const
{
	return m_e.what();
}

gstr SQLErrorInfo::err_lighter_str() const
{
	return str2str(sqlighter::error_message(m_e.code()));
}

gstr SQLErrorInfo::err_sqlite_str() const
{
	return { m_e.what_sqlite3() };
}

gstr SQLErrorInfo::err_query() const
{
	return str2str(m_e.query());
}
