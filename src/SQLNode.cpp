#include "SQLNode.h"


#include "Utils/macros.h"
#include "Utils/gd_path.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_db_path"),			&SQLNode::get_db_path);
	ClassDB::bind_method(D_METHOD("set_db_path", "path"),	&SQLNode::set_db_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "db_path"), "set_db_path", "get_db_path");
	
	ClassDB::bind_method(D_METHOD("get_auto_create"),					&SQLNode::get_auto_create);
	ClassDB::bind_method(D_METHOD("set_auto_create", "auto_create"),	&SQLNode::set_auto_create);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_create"), "set_auto_create", "get_auto_create");
	
	ClassDB::bind_method(D_METHOD("get_full_path"),	&SQLNode::get_full_path);
	ClassDB::bind_method(D_METHOD("close"),			&SQLNode::close);
	
	ClassDB::bind_method(D_METHOD("execute", "query_string", "binds"),		&SQLNode::execute);
	ClassDB::bind_method(D_METHOD("execute_stmt", "query_string", "binds"),	&SQLNode::execute_stmt);
	
	// Transaction
	ClassDB::bind_method(D_METHOD("begin"),		&SQLNode::begin);
	ClassDB::bind_method(D_METHOD("commit"),	&SQLNode::commit);
	ClassDB::bind_method(D_METHOD("rollback"),	&SQLNode::rollback);
	
	// Reindex
	ClassDB::bind_method(D_METHOD("reindex", "what"),				&SQLNode::reindex);
	ClassDB::bind_method(D_METHOD("reindex_in", "scheme", "what"),	&SQLNode::reindex_in);
	
	// Shortcuts
	ClassDB::bind_method(D_METHOD("query_row", "query", "binds"),			&SQLNode::query_row);
	ClassDB::bind_method(D_METHOD("query_row_numeric", "query", "binds"),	&SQLNode::query_row_numeric);
	ClassDB::bind_method(D_METHOD("query_all", "query", "binds"),			&SQLNode::query_all);
	ClassDB::bind_method(D_METHOD("query_column_all", "query", "binds"),	&SQLNode::query_column_all);
	ClassDB::bind_method(D_METHOD("query_value", "query", "binds"),			&SQLNode::query_value);
	
	ClassDB::bind_method(D_METHOD("query_all_max", "query", "binds", "failsafe"),			&SQLNode::query_all_max);
	ClassDB::bind_method(D_METHOD("query_column_all_max", "query", "binds", "failsafe"),	&SQLNode::query_column_all_max);
	
	ClassDB::bind_method(D_METHOD("count_rows", "table_name"),	&SQLNode::count_rows);
	
	ClassDB::bind_method(D_METHOD("direct"),		&SQLNode::direct);
	ClassDB::bind_method(D_METHOD("select"),		&SQLNode::select);
	ClassDB::bind_method(D_METHOD("update"),		&SQLNode::update);
	ClassDB::bind_method(D_METHOD("delete"),		&SQLNode::del);
	ClassDB::bind_method(D_METHOD("create_table"),	&SQLNode::create_table);
	ClassDB::bind_method(D_METHOD("drop"),			&SQLNode::drop);
}


bool SQLNode::open()
{
	if (m_sql != nullptr) return true;
	
	try
	{
		m_sql = std::make_unique<SQLighter>(to_path(m_path));
	}
	catch (const excp& e)
	{
		m_sql = nullptr;
		GLighter::handle_error(e);
		return false;
	}
	
	return true;
}


bool SQLNode::get_auto_create() const
{
	return m_autoCreate;
}

void SQLNode::set_auto_create(bool value)
{
	m_autoCreate = value;
}

gstr SQLNode::get_db_path() const
{
	return m_path;
}

void SQLNode::set_db_path(const gstr& path)
{
	m_path = path;
	
	if (m_sql)
	{
		m_sql = nullptr;
	}
}

gstr SQLNode::get_full_path() const
{
	return str2str(to_path(m_path));
}

void SQLNode::close()
{
	m_sql = nullptr;
}


bool SQLNode::execute(const gstr& query, const Array& binds)
{
	return execute_stmt(query, binds)->is_failed();
}

Ref<GLighterStmt> SQLNode::execute_stmt(const gstr& query, const Array& binds)
{
	if (!open())
	{
		return GLighterStmt::from_error(GLighter::last_err());
	}
	
	auto query_str = str2str(query);
	godot::vec<BindValue> binds_v = {};
	
	try
	{
		binds_v = var2val(binds);
	}
	catch (const excp& e)
	{
		SQLighterException ee(e);
		
		ee.query(query_str);
		
		GLighter::handle_error(ee);
		return GLighterStmt::from_error(ee);
	}
	
	try
	{
		auto cmd = m_sql->direct().append(query_str, binds_v);
		auto res = cmd.execute();
		
		return GLighterStmt::from_stmt(std::move(res));
	}
	catch (const excp& e)
	{
		GLighter::handle_error(e);
		return GLighterStmt::from_error(e);
	}
}


Dictionary SQLNode::query_row(const gstr& query, const Array& binds)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Dictionary {} : res->row();
}

Array SQLNode::query_row_numeric(const gstr& query, const Array& binds)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Array {} : res->row_numeric();
}

Array SQLNode::query_all(const gstr& query, const Array& binds)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Array {} : res->all_max(DEFAULT_FAILSAFE);
}

Array SQLNode::query_column_all(const gstr& query, const Array& binds)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Array {} : res->column_all_max(DEFAULT_FAILSAFE);
}

Variant SQLNode::query_value(const gstr& query, const Array& binds)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Variant { nullptr } : res->value();
}

Array SQLNode::query_all_max(const gstr& query, const Array& binds, int failsafeLimit)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Array { } : res->all_max(failsafeLimit);
}

Array SQLNode::query_column_all_max(const gstr& query, const Array& binds, int failsafeLimit)
{
	auto res = execute_stmt(query, binds);
	return res->is_failed() ? Array { } : res->column_all_max(failsafeLimit);
}

int SQLNode::count_rows(const gstr& table_name)
{
	RETURN_TRY_SQLIGHTER_VALUE(m_sql->count_rows(str2str(table_name)), 0);
}

bool SQLNode::begin() const
{
	RETURN_TRY_SQLIGHTER_ACTION(m_sql->begin());
}

bool SQLNode::commit() const
{
	RETURN_TRY_SQLIGHTER_ACTION(m_sql->commit());
}

bool SQLNode::rollback() const
{
	RETURN_TRY_SQLIGHTER_ACTION(m_sql->rollback());
}

bool SQLNode::reindex(const gstr& element) const
{
	RETURN_TRY_SQLIGHTER_ACTION(m_sql->reindex(str2str(element)));
}

bool SQLNode::reindex_in(const gstr& scheme, const gstr& element) const
{
	RETURN_TRY_SQLIGHTER_ACTION(m_sql->reindex(str2str(scheme), str2str(element)));
}

Ref<SQLDirect> SQLNode::direct() const
{
	return make_ref<SQLDirect>(std::move(m_sql->direct()));
}

Ref<SQLDelete> SQLNode::del() const
{
	return make_ref<SQLDelete>(std::move(m_sql->del()));
}

Ref<SQLSelect> SQLNode::select() const
{
	return make_ref<SQLSelect>(std::move(m_sql->select()));
}

Ref<SQLUpdate> SQLNode::update() const
{
	return make_ref<SQLUpdate>(std::move(m_sql->update()));
}

Ref<SQLCreateTable> SQLNode::create_table() const
{
	return make_ref<SQLCreateTable>(std::move(m_sql->create()));
}

Ref<SQLDrop> SQLNode::drop() const
{
	return make_ref<SQLDrop>(std::move(m_sql->drop()));
}