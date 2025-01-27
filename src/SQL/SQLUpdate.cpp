#include "SQLUpdate.h"


#include "Utils/types.h"
#include "Utils/macros.h"
#include "Utils/macros.cpp.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLUpdate::_bind_methods()
{
	CLAUSE_TABLE_BIND(SQLUpdate);
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


CLAUSE_TABLE_IMPL(SQLUpdate)
CLAUSE_OR_IMPL(SQLUpdate)
CLAUSE_SET_IMP(SQLUpdate)
CLAUSE_WHERE_IMPL(SQLUpdate)


bool SQLUpdate::update()
{
	return !execute()->is_failed();
}
