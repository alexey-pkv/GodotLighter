#include "GLighterStmt.h"


#include "GLighter.h"


#define TRY_OR_RETURN_VALUE(action, return_value) \
	try { action; } \
	catch (const excp& e) \
	{ handle_error(e); return return_value; }

#define TRY_RETURN(action, default_value) \
	try { return action; } \
	catch (const excp& e) \
	{ handle_error(e); return default_value; }

#define TRY_OR_NOTHING(action) \
	try { action; } \
	catch (const excp& e) \
	{ handle_error(e); }


using namespace godot;
using namespace sqlighter;


void GLighterStmt::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("value"), &GLighterStmt::value);
	
	ClassDB::bind_method(D_METHOD("column_value",	"column_name"),		&GLighterStmt::column_value);
	ClassDB::bind_method(D_METHOD("column_value_i",	"column_index"),	&GLighterStmt::column_value_i);
	
	ClassDB::bind_method(D_METHOD("column_int_i",		"column_index"),	&GLighterStmt::column_int_i);
	ClassDB::bind_method(D_METHOD("column_bool_i",		"column_index"),	&GLighterStmt::column_bool_i);
	ClassDB::bind_method(D_METHOD("column_double_i",	"column_index"),	&GLighterStmt::column_double_i);
	ClassDB::bind_method(D_METHOD("column_string_i",	"column_index"),	&GLighterStmt::column_string_i);
	ClassDB::bind_method(D_METHOD("column_is_null_i",	"column_index"),	&GLighterStmt::column_is_null_i);
	
	ClassDB::bind_method(D_METHOD("column_int",		"column_name"),	&GLighterStmt::column_int);
	ClassDB::bind_method(D_METHOD("column_bool",	"column_name"),	&GLighterStmt::column_bool);
	ClassDB::bind_method(D_METHOD("column_double",	"column_name"),	&GLighterStmt::column_double);
	ClassDB::bind_method(D_METHOD("column_string",	"column_name"),	&GLighterStmt::column_string);
	ClassDB::bind_method(D_METHOD("column_is_null",	"column_name"),	&GLighterStmt::column_is_null);
	
	ClassDB::bind_method(D_METHOD("row_numeric"),	&GLighterStmt::row_numeric);
	ClassDB::bind_method(D_METHOD("row"),			&GLighterStmt::row);
	
	ClassDB::bind_method(D_METHOD("all_numeric_max",	"failsafe_limit"), &GLighterStmt::all_numeric_max);
	ClassDB::bind_method(D_METHOD("column_all_max",		"failsafe_limit"), &GLighterStmt::column_all_max);
	ClassDB::bind_method(D_METHOD("all_max",			"failsafe_limit"), &GLighterStmt::all_max);
	
	ClassDB::bind_method(D_METHOD("all_numeric"),	&GLighterStmt::all_numeric);
	ClassDB::bind_method(D_METHOD("column_all"),	&GLighterStmt::column_all);
	ClassDB::bind_method(D_METHOD("all"),			&GLighterStmt::all);
	
	ClassDB::bind_method(D_METHOD("column_names"),	&GLighterStmt::column_names);
	
	ClassDB::bind_method(D_METHOD("code"),			&GLighterStmt::code);
	ClassDB::bind_method(D_METHOD("is_done"),		&GLighterStmt::is_done);
	ClassDB::bind_method(D_METHOD("is_ok"),			&GLighterStmt::is_ok);
	ClassDB::bind_method(D_METHOD("is_error"),		&GLighterStmt::is_error);
	ClassDB::bind_method(D_METHOD("has_row"),		&GLighterStmt::has_row);
	ClassDB::bind_method(D_METHOD("query_string"),	&GLighterStmt::query_string);
	ClassDB::bind_method(D_METHOD("step"),			&GLighterStmt::step);
	ClassDB::bind_method(D_METHOD("close"),			&GLighterStmt::close);
}


int GLighterStmt::require_column(const gstr& name)
{
	auto str = str2str(name);
	auto index = m_stmt.column_index(str);
	
	if (index < 0)
	{
		std::ostringstream ss;
		
		ss 
			<< "Column `" << str
			<< "` does not exists in the query result set or the query_string failed to execute" 
			<< std::endl;
		
		handle_error(std::move(excp(SQLIGHTER_ERR_INVALID_COLUMN)
			.query(m_stmt.query())
			.msg(ss.str())));
	}
	
	return index;
}

void GLighterStmt::rows_limit_reached_error(int limit)
{
	handle_error(excp(SQLIGHTER_ERR_ROWS_OVERFLOW)
		.msg(str{"The failsafe limit is "} + std::to_string(limit))
		.query(m_stmt.query()));
}

void GLighterStmt::number_of_columns_and_rows_error()
{
	handle_error(excp(
		SQLIGHTER_ERR_UNEXPECTED, 
		"Number of column values and column names did not match"));
}

void GLighterStmt::handle_error(const excp& e)
{
	GLighter::handle_error(e);
	init_with(e);
}

void GLighterStmt::handle_error(excp&& e)
{
	GLighter::handle_error(e);
	init_with(std::move(e));
}

void GLighterStmt::store_column_names()
{
	if (!m_column_names.empty())
		return;
	
	const auto& names = m_stmt.column_names();
	
	m_column_names.reserve(names.size());
	
	for (const auto& name : names)
	{
		m_column_names.push_back(str2str(name));
	}
}


bool GLighterStmt::is_failed() { return m_error != nullptr; }
Ref<GLighterException> GLighterStmt::get_err() { return m_error; }

int GLighterStmt::code() const			{ return m_stmt.code(); }
bool GLighterStmt::is_done() const		{ return m_stmt.is_done(); }
bool GLighterStmt::is_ok() const		{ return m_stmt.is_ok(); }
bool GLighterStmt::is_error() const 	{ return m_stmt.is_error(); }
bool GLighterStmt::has_row() const		{ return m_stmt.has_row(); }
gstr GLighterStmt::query_string() const	{ return str2str(m_stmt.query()); }


int GLighterStmt::step()
{
	TRY_OR_NOTHING(m_stmt.step());
	return m_stmt.code();
}

int GLighterStmt::close()
{
	return m_stmt.close();
}


Variant GLighterStmt::value()
{
	return column_value_i(0);
}

Variant GLighterStmt::column_value(const gstr& name)
{
	int index = require_column(name);
	
	if (index < 0)
		return nullptr;
		
	return column_value_i(index);
}

Variant GLighterStmt::column_value_i(int at)
{
	int type = SQLITE_NULL;
	
	TRY_OR_RETURN_VALUE(type = m_stmt.column_type(at), false);
	
	switch (type)
	{
		case SQLITE_INTEGER:
			return m_stmt.column_int64(at);
			
		case SQLITE_FLOAT:
			return m_stmt.column_double(at);
			
		case SQLITE_TEXT:
			return str2str(m_stmt.column_string(at));
			
		case SQLITE_NULL:
		case SQLITE_BLOB:
		default:
			return { nullptr };	
	}
}

int64_t GLighterStmt::column_int_i(int at)
{
	TRY_RETURN(m_stmt.column_int64(at), 0);
}

bool GLighterStmt::column_bool_i(int at)
{
	TRY_RETURN(m_stmt.column_bool(at), false);
}

double GLighterStmt::column_double_i(int at)
{
	TRY_RETURN(m_stmt.column_double(at), 0.0);
}

gstr GLighterStmt::column_string_i(int at)
{
	TRY_RETURN(str2str(m_stmt.column_string(at)), "");
}

bool GLighterStmt::column_is_null_i(int at)
{
	TRY_RETURN(m_stmt.column_is_null(at), false);
}

int64_t GLighterStmt::column_int(const gstr& name)
{
	int index = require_column(name);
	return index >= 0 ? m_stmt.column_int64(index) : 0;
}

bool GLighterStmt::column_bool(const gstr& name)
{
	int index = require_column(name);
	return index >= 0 ? m_stmt.column_bool(index) : false;
}

double GLighterStmt::column_double(const gstr& name)
{
	int index = require_column(name);
	return index >= 0 ? m_stmt.column_bool(index) : 0.0;
}

gstr GLighterStmt::column_string(const gstr& name)
{
	int index = require_column(name);
	return index >= 0 ? column_string_i(index) : "";
}

bool GLighterStmt::column_is_null(const gstr& name)
{
	int index = require_column(name);
	return index >= 0 ? m_stmt.column_is_null(index) : false;
}


Array GLighterStmt::row_numeric()
{
	Array a;
	vec<ScalarValue> row;
	
	TRY_OR_RETURN_VALUE(row = m_stmt.row(), {});
	
	for (const auto& sv : row)
	{
		a.push_back(val2var(sv));
	}
	
	return a;
}

Dictionary GLighterStmt::row()
{
	Dictionary			result	{};
	vec<ScalarValue>	row		{};
	
	TRY_OR_RETURN_VALUE(row = m_stmt.row(), {});
	
	store_column_names();
	
	if (m_column_names.size() != row.size())
	{
		number_of_columns_and_rows_error();
		return result;
	}
	
	for (int i = 0; i < row.size(); i++)
	{
		result[m_column_names[i]] = val2var(row[i]);
	}
	
	return result;
}

Array GLighterStmt::all_numeric()
{
	return all_numeric_max(DEFAULT_FAILSAFE);
}

Array GLighterStmt::all_numeric_max(int failsafeLimit)
{
	Array result;
	
	while (has_row() && !is_failed())
	{
		result.push_back(row_numeric());
		
		if (result.size() > failsafeLimit)
		{
			rows_limit_reached_error(failsafeLimit);
			return {};
		}
		else if (is_failed())
		{
			return {};
		}
		
		step();
	}
	
	return result;
}

Array GLighterStmt::all()
{
	return all_max(DEFAULT_FAILSAFE);
}

Array GLighterStmt::all_max(int failsafeLimit)
{
	Array result;
	Array names;
	
	names = column_names();
	
	while (has_row())
	{
		Dictionary curr_row;
		
		if (result.size() > failsafeLimit)
		{
			rows_limit_reached_error(failsafeLimit);
			return {};
		}
		
		auto row = m_stmt.row_and_step();
		
		if (m_column_names.size() != row.size())
		{
			number_of_columns_and_rows_error();
			return result;
		}
		
		for (int i = 0; i < row.size(); i++)
		{
			curr_row[names[i]] = val2var(row[i]);
		}
		
		result.push_back(curr_row);
	}
	
	return result;
}

Array GLighterStmt::column_all()
{
	return column_all_max(DEFAULT_FAILSAFE);
}

Array GLighterStmt::column_all_max(int failsafeLimit)
{
	Array result;
	
	TRY_OR_RETURN_VALUE(m_stmt.require_one_column(), {});
	
	while (has_row())
	{
		if (result.size() > failsafeLimit)
		{
			rows_limit_reached_error(failsafeLimit);
			return {};
		}
		
		result.push_back(column_value_i(0));
		step();
		
		if (is_failed())
		{
			return Array {};
		}
	}
	
	return result;
}

Array GLighterStmt::column_names()
{
	Array result;
	
	store_column_names();
	
	for (const auto& v : m_column_names)
	{
		result.push_back(v);
	}
	
	return result;
}

Ref<GLighterStmt> GLighterStmt::from_error(const excp& err)
{
	auto res = make_ref<GLighterStmt>();
	
	res->init_with(err);
	
	return res;
}

Ref<GLighterStmt> GLighterStmt::from_error(const Ref<GLighterException>& err)
{
	auto res = make_ref<GLighterStmt>();
	
	res->init_with(err);
	
	return res;
}

Ref<GLighterStmt> GLighterStmt::from_stmt(stmt&& s)
{
	auto res = make_ref<GLighterStmt>();
	
	res->init_with(std::move(s));
	
	return res;
}
