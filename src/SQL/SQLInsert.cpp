#include "SQLInsert.h"


#include "Utils/types.h"
#include "Utils/macros.cpp.h"
#include "Utils/errors.h"

#include "SQL/Clause/OrClause.h"
#include "SQL/Clause/SetClause.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLInsert::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("as", "alias"),						&SQLInsert::as);
	ClassDB::bind_method(D_METHOD("into", "table"),						&SQLInsert::into);
	ClassDB::bind_method(D_METHOD("into_scheme", "scheme", "table"),	&SQLInsert::into_scheme);
	
	ClassDB::bind_method(D_METHOD("default_values"),			&SQLInsert::default_values);
	ClassDB::bind_method(D_METHOD("on_conflict_do_nothing"),	&SQLInsert::on_conflict_do_nothing);
	ClassDB::bind_method(D_METHOD("on_conflict", "column"),		&SQLInsert::on_conflict);
	
	ClassDB::bind_method(D_METHOD("column", "name"),		&SQLInsert::column);
	ClassDB::bind_method(D_METHOD("columns", "names"),		&SQLInsert::columns);
	ClassDB::bind_method(D_METHOD("record", "values"),		&SQLInsert::record);
	ClassDB::bind_method(D_METHOD("records", "values_set"),	&SQLInsert::records);
	
	bind_or<SQLInsert>();
	bind_set<SQLInsert>();
	
	ClassDB::bind_method(D_METHOD("insert"), &SQLInsert::insert);
}


CMD* SQLInsert::get_cmd() { return m_cmd.get(); }
const CMD* SQLInsert::get_cmd() const { return m_cmd.get(); };

void SQLInsert::init(CMDInsert&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDInsert>(std::move(cmd));
}


Ref<SQLInsert> SQLInsert::as(const gstr& alias)
{
	m_cmd->as(str2str(alias));
	return { this };
}

Ref<SQLInsert> SQLInsert::into(const gstr& table)
{
	m_cmd->into(str2str(table));
	return { this };
}

Ref<SQLInsert> SQLInsert::into_scheme(const gstr& scheme, const gstr& table)
{
	m_cmd->into(str2str(scheme), str2str(table));
	return { this };
}

bool SQLInsert::insert()
{
	return !execute()->is_failed();
}

Ref<SQLInsert> SQLInsert::default_values()
{
	m_cmd->default_values();
	return { this };
}

Ref<SQLInsert> SQLInsert::on_conflict_do_nothing()
{
	m_cmd->on_conflict_do_nothing();
	return { this };
}

Ref<SQLInsert> SQLInsert::on_conflict(const gstr& column)
{
	m_cmd->on_conflict(str2str(column));
	return { this };
}

Ref<SQLInsert> SQLInsert::column(const gstr& name)
{
	m_cmd->column(str2str(name));
	return { this };
}

Ref<SQLInsert> SQLInsert::columns(const Array& names)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i].get_type() != Variant::STRING)
		{
			column_name_not_a_string_error(names[i], i);
			continue;
		}
		
		m_cmd->column(str2str(names[i]));
	}
	
	
	return { this };
}

Ref<SQLInsert> SQLInsert::record(const Array& values)
{
	godot::GLighter::try_action([&] { m_cmd->record(var2val(values)); });
	
	return { this };
}

Ref<SQLInsert> SQLInsert::records(const Array& values_set)
{
	for (int i = 0; i < values_set.size(); i++)
	{
		if (values_set[i].get_type() != Variant::ARRAY)
		{
			expecting_array_error(values_set[i], i);
			continue;
		}
		
		record(values_set[i]);
	}
	
	return { this };
}


CLAUSE_OR_IMPL(SQLInsert);
CLAUSE_SET_IMPL(SQLInsert);
