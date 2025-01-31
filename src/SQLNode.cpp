#include "SQLNode.h"


#include "Utils/gd_path.h"


using namespace godot;
using namespace sqlighter;



template<class CMD, class LCMD>
static Ref<CMD> create_cmd(LCMD&& cmd, const Ref<SQLErrors>& errors)
{
	Ref<CMD> r;
	
	r.instantiate();
	r->init(std::forward<LCMD>(cmd), errors);
	
	return r;
}


void SQLNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_db_path"),			&SQLNode::get_db_path);
	ClassDB::bind_method(D_METHOD("set_db_path", "path"),	&SQLNode::set_db_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "db_path"), "set_db_path", "get_db_path");
	
	ClassDB::bind_method(D_METHOD("get_auto_create"),					&SQLNode::get_auto_create);
	ClassDB::bind_method(D_METHOD("set_auto_create", "auto_create"),	&SQLNode::set_auto_create);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_create"), "set_auto_create", "get_auto_create");
	
	ClassDB::bind_method(D_METHOD("get_is_memory"),					&SQLNode::get_is_memory);
	ClassDB::bind_method(D_METHOD("set_is_memory", "is_memory"),	&SQLNode::set_is_memory);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "in_memory"), "set_is_memory", "get_is_memory");
	
	ClassDB::bind_method(D_METHOD("get_full_path"),	&SQLNode::get_full_path);
	ClassDB::bind_method(D_METHOD("open"),			&SQLNode::open);
	ClassDB::bind_method(D_METHOD("close"),			&SQLNode::close);
	
	ClassDB::bind_method(D_METHOD("execute", "query_string", "binds"),		&SQLNode::execute);
	ClassDB::bind_method(D_METHOD("execute_stmt", "query_string", "binds"),	&SQLNode::execute_stmt);
	
	ClassDB::bind_method(D_METHOD("errors"), &SQLNode::errors);
	
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
	ClassDB::bind_method(D_METHOD("insert"),		&SQLNode::insert);
	ClassDB::bind_method(D_METHOD("update"),		&SQLNode::update);
	ClassDB::bind_method(D_METHOD("delete"),		&SQLNode::del);
	ClassDB::bind_method(D_METHOD("create_table"),	&SQLNode::create_table);
	ClassDB::bind_method(D_METHOD("drop"),			&SQLNode::drop);
	
	ADD_SIGNAL(MethodInfo("on_error",
		PropertyInfo(
			Variant::OBJECT, "error",
			PROPERTY_HINT_NODE_TYPE, "SQLErrorInfo")));
	
	ClassDB::bind_method(D_METHOD("handle_error"), &SQLNode::handle_error);
}


const Ref<SQLErrors>& SQLNode::errors_ref()
{
	if (m_errors == nullptr)
	{
		m_errors.instantiate();
		m_errors->propagate_to_global();
		m_errors->set_print_errors(false);
		m_errors->connect("on_error", Callable(this, "handle_error"));
	}
	
	return m_errors;
}


bool SQLNode::open()
{
	if (m_sql != nullptr) return true;
	
	try
	{
		if (!get_is_memory())
		{
			m_sql = std::make_unique<SQLighter>(to_path(m_path));
		}
		else
		{
			m_sql = std::make_unique<SQLighter>(str2str(m_path));
		}
	}
	catch (const excp& e)
	{
		m_sql = nullptr;
		errors_ref()->handle_error(e);
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

bool SQLNode::get_is_memory() const
{
	return m_path == ":memory:";
}

void SQLNode::set_is_memory(bool value)
{
	if (value == (m_path == ":memory:"))
		return;
	
	m_path = value ? ":memory:" : "";
	
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

Ref<SQLErrors> SQLNode::errors()
{
	return errors_ref();
}

void SQLNode::handle_error(const Ref<SQLErrorInfo>& e)
{
	emit_signal("on_error", e);
}


bool SQLNode::execute(const gstr& query, const Array& binds)
{
	return execute_stmt(query, binds)->is_failed();
}

Ref<SQLStmt> SQLNode::execute_stmt(const gstr& query, const Array& binds)
{
	if (!open())
	{
		return SQLStmt::from_error(errors_ref(), errors_ref()->last_err());
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
		
		errors_ref()->handle_error(ee);
		
		return SQLStmt::from_error(errors_ref(), ee);
	}
	
	try
	{
		auto cmd = m_sql->direct().append(query_str, binds_v);
		auto res = cmd.execute();
		
		return SQLStmt::from_stmt(errors_ref(), std::move(res));
	}
	catch (const excp& e)
	{
		errors_ref()->handle_error(e);
		return SQLStmt::from_error(errors_ref(), e);
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
	if (!open())
		return 0;
	
	return errors_ref()->try_action(
		[&] { return m_sql->count_rows(str2str(table_name)); }, 
		0);
}

bool SQLNode::begin()
{
	if (!open())
		return false;
	
	return errors_ref()->try_action_bool([&] { m_sql->begin(); });
}

bool SQLNode::commit()
{
	if (!open())
		return false;
	
	return errors_ref()->try_action_bool([&] { m_sql->commit(); });
}

bool SQLNode::rollback()
{
	if (!open())
		return false;
	
	return errors_ref()->try_action_bool([&] { m_sql->rollback(); });
}

bool SQLNode::reindex(const gstr& element)
{
	if (!open())
		return false;
	
	return errors_ref()->try_action_bool(
		[&] { m_sql->reindex(str2str(element)); });
}

bool SQLNode::reindex_in(const gstr& scheme, const gstr& element)
{
	if (!open())
		return false;
	
	return errors_ref()->try_action_bool(
		[&] { m_sql->reindex(str2str(scheme), str2str(element)); });
}


Ref<SQLDirect> SQLNode::direct()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLDirect>(std::move(m_sql->direct()), errors_ref());
}

Ref<SQLDelete> SQLNode::del()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLDelete>(std::move(m_sql->del()), errors_ref());
}

Ref<SQLSelect> SQLNode::select()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLSelect>(std::move(m_sql->select()), errors_ref());
}

Ref<SQLInsert> SQLNode::insert()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLInsert>(std::move(m_sql->insert()), errors_ref());
}

Ref<SQLUpdate> SQLNode::update()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLUpdate>(std::move(m_sql->update()), errors_ref());
}

Ref<SQLCreateTable> SQLNode::create_table()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLCreateTable>(std::move(m_sql->create()), errors_ref());
}

Ref<SQLDrop> SQLNode::drop()
{
	if (!open())
		return nullptr;
	
	return create_cmd<SQLDrop>(std::move(m_sql->drop()), errors_ref());
}