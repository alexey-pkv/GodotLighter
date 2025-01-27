#include "SQLUpdate.h"


#include "Utils/types.h"
#include "Utils/macros.h"
#include "Utils/macros.cpp.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLUpdate::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("as", "alias"),					&SQLUpdate::as);
	ClassDB::bind_method(D_METHOD("table", "table"),				&SQLUpdate::table);
	ClassDB::bind_method(D_METHOD("table_in", "scheme", "table"),	&SQLUpdate::table_in);
	
	CLAUSE_OR_BIND(SQLUpdate);
	CLAUSE_SET_BIND(SQLUpdate)
	CLAUSE_WHERE_BIND(SQLUpdate);
	
	ClassDB::bind_method(D_METHOD("update"), &SQLUpdate::update);
}


CMD* SQLUpdate::get_cmd() { return m_cmd.get(); }
const CMD* SQLUpdate::get_cmd() const { return m_cmd.get(); };

void SQLUpdate::init(CMDUpdate&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDUpdate>(std::move(cmd));
}


Ref<SQLUpdate> SQLUpdate::as(const gstr& alias)
{
	m_cmd->as(str2str(alias));
	return { this };
}

Ref<SQLUpdate> SQLUpdate::table(const gstr& table)
{
	m_cmd->table(str2str(table));
	return { this };
}

Ref<SQLUpdate> SQLUpdate::table_in(const gstr& scheme, const gstr& table)
{
	m_cmd->table(str2str(scheme), str2str(table));
	return { this };
}
		

CLAUSE_OR_IMPL(SQLUpdate)
CLAUSE_SET_IMPL(SQLUpdate)
CLAUSE_WHERE_IMPL(SQLUpdate)


bool SQLUpdate::update()
{
	return !execute()->is_failed();
}
