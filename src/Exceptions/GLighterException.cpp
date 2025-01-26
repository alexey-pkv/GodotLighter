#include "GLighterException.h"


using namespace godot;
using namespace sqlighter;


void GLighterException::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("err_code"),				&GLighterException::err_code);
	ClassDB::bind_method(D_METHOD("err_sqlite_code"),		&GLighterException::err_sqlite_code);
	ClassDB::bind_method(D_METHOD("err_str"),				&GLighterException::err_str);
	ClassDB::bind_method(D_METHOD("err_slighter_message"),	&GLighterException::err_slighter_message);
	ClassDB::bind_method(D_METHOD("err_sqlite_message"),	&GLighterException::err_sqlite_message);
	ClassDB::bind_method(D_METHOD("err_query"),				&GLighterException::err_query);
}


int GLighterException::err_code() const
{
	return m_e.code();
}

int GLighterException::err_sqlite_code() const
{
	return m_e.sqlite_code();
}

gstr GLighterException::err_str() const
{
	return m_e.what();
}

gstr GLighterException::err_slighter_message() const
{
	return str2str(m_e.message());
}

gstr GLighterException::err_sqlite_message() const
{
	return { m_e.what_sqlite3() };
}

gstr GLighterException::err_query() const
{
	return str2str(m_e.query());
}
