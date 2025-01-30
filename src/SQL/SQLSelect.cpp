#include "SQLSelect.h"


#include "Utils/types.h"
#include "Utils/macros.cpp.h"
#include "Utils/errors.h"

#include "SQL/Clause/LimitClause.h"
#include "SQL/Clause/OrderByClause.h"
#include "SQL/Clause/WhereClause.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLSelect::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("distinct"), &SQLSelect::distinct);
	
	ClassDB::bind_method(D_METHOD("column_exp", "expression", "binds"),	&SQLSelect::column_exp);
	ClassDB::bind_method(D_METHOD("column", "column"),					&SQLSelect::column);
	ClassDB::bind_method(D_METHOD("column_as", "column", "as"),			&SQLSelect::column_as);
	ClassDB::bind_method(D_METHOD("columns", "columns"),				&SQLSelect::columns);
	
	
	bind_from<SQLSelect>();
	bind_limit<SQLSelect>();
	bind_order_by<SQLSelect>();
	bind_where<SQLSelect>();
	
	ClassDB::bind_method(D_METHOD("query_row"),			&SQLSelect::query_row);
	ClassDB::bind_method(D_METHOD("query_row_numeric"),	&SQLSelect::query_row_numeric);
	ClassDB::bind_method(D_METHOD("query_all"),			&SQLSelect::query_all);
	ClassDB::bind_method(D_METHOD("query_column_all"),	&SQLSelect::query_column_all);
	ClassDB::bind_method(D_METHOD("query_value"),		&SQLSelect::query_value);
	
	ClassDB::bind_method(D_METHOD("query_all_max", "failsafeLimit"),		&SQLSelect::query_all_max);
	ClassDB::bind_method(D_METHOD("query_column_all_max", "failsafeLimit"),	&SQLSelect::query_column_all_max);
}


CMD* SQLSelect::get_cmd() { return m_cmd.get(); }
const CMD* SQLSelect::get_cmd() const { return m_cmd.get(); };

void SQLSelect::init(CMDSelect&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDSelect>(std::move(cmd));
}


Ref<SQLSelect> SQLSelect::distinct()
{
	m_cmd->distinct();
	return { this };
}

Ref<SQLSelect> SQLSelect::column_exp(const gstr& expression, const Array& binds)
{
	godot::GLighter::try_action([&] 
	{
		m_cmd->column_exp(str2str(expression), var2val(binds));
	});
	
	return { this };
}

Ref<SQLSelect> SQLSelect::column(const gstr& column)
{
	m_cmd->column(str2str(column));
	return { this };
}

Ref<SQLSelect> SQLSelect::column_as(const gstr& column, const gstr& as)
{
	m_cmd->column_as(str2str(column), str2str(as));
	return { this };
}

Ref<SQLSelect> SQLSelect::columns(const Array& columns)
{
	for (int i = 0; i < columns.size(); i++)
	{
		if (columns[i].get_type() != Variant::STRING)
		{
			column_name_not_a_string_error(columns[i], i);
			return { this }; 
		}
		
		m_cmd->column(str2str(columns[i]));
	}
	
	return { this };
}

CLAUSE_FROM_IMPL(SQLSelect)
CLAUSE_WHERE_IMPL(SQLSelect)
CLAUSE_ORDER_BY_IMPL(SQLSelect)
CLAUSE_LIMIT_IMPL(SQLSelect)


Dictionary SQLSelect::query_row()
{
	auto stmt = execute();
	return stmt->is_failed() ? Dictionary() : stmt->row();
}

Array SQLSelect::query_row_numeric()
{
	auto stmt = execute();
	return stmt->is_failed() ? Array() : stmt->row_numeric();
}

Array SQLSelect::query_all()
{
	auto stmt = execute();
	return stmt->is_failed() ? Array() : stmt->all();
}

Array SQLSelect::query_column_all()
{
	auto stmt = execute();
	return stmt->is_failed() ? Array() : stmt->column_all();
}

Variant SQLSelect::query_value()
{
	auto stmt = execute();
	return stmt->is_failed() ? Variant { nullptr } : stmt->value();
}

Array SQLSelect::query_all_max(int failsafeLimit)
{
	auto stmt = execute();
	return stmt->is_failed() ? Array() : stmt->all_max(failsafeLimit);
}

Array SQLSelect::query_column_all_max(int failsafeLimit)
{
	auto stmt = execute();
	return stmt->is_failed() ? Array() : stmt->column_all_max(failsafeLimit);
}
