#include "SQLCreateTable.h"


using namespace godot;
using namespace sqlighter;


void SQLCreateTable::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("temp"),				&SQLCreateTable::temp);
	ClassDB::bind_method(D_METHOD("without_rowid"),		&SQLCreateTable::without_rowid);
	ClassDB::bind_method(D_METHOD("strict"),			&SQLCreateTable::strict);
	ClassDB::bind_method(D_METHOD("create"),			&SQLCreateTable::create);
	ClassDB::bind_method(D_METHOD("if_not_exists"),		&SQLCreateTable::if_not_exists);
	
	ClassDB::bind_method(D_METHOD("table", "name"),					&SQLCreateTable::table);
	ClassDB::bind_method(D_METHOD("table_in", "scheme", "name"),	&SQLCreateTable::table_in);
	ClassDB::bind_method(D_METHOD("column_exp", "expression"),		&SQLCreateTable::column_exp);
}


Ref<SQLCreateTable> SQLCreateTable::temp() { m_cmd->temp(); return { this }; }
Ref<SQLCreateTable> SQLCreateTable::if_not_exists() { m_cmd->if_not_exists(); return { this }; }

Ref<SQLCreateTable> SQLCreateTable::table(const gstr& name)
{
	m_cmd->table(str2str(name));
	return { this };
}

Ref<SQLCreateTable> SQLCreateTable::table_in(const gstr& scheme, const gstr& name)
{
	m_cmd->table(str2str(scheme), str2str(name));
	return { this };
}

Ref<SQLCreateTable> SQLCreateTable::column_exp(const gstr& exp)
{
	m_cmd->column_exp(str2str(exp));
	return { this };
}

Ref<SQLCreateTable> SQLCreateTable::without_rowid() { m_cmd->without_rowid(); return { this }; }
Ref<SQLCreateTable> SQLCreateTable::strict() { m_cmd->strict(); return { this }; }

bool SQLCreateTable::create()
{
	return !execute()->is_failed();
}


sqlighter::CMD* SQLCreateTable::get_cmd() { return m_cmd.get(); }
const sqlighter::CMD* SQLCreateTable::get_cmd() const { return m_cmd.get(); }

void SQLCreateTable::init(CMDCreateTable&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDCreateTable>(std::move(cmd));
}
