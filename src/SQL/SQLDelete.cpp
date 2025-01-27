#include "SQLDelete.h"


#include "Utils/types.h"
#include "Utils/macros.h"
#include "Utils/macros.cpp.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLDelete::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("del"), &SQLDelete::del);
	
	CLAUSE_FROM_BIND(SQLDelete);
	CLAUSE_WHERE_BIND(SQLDelete);
	CLAUSE_ORDER_BY_BIND(SQLDelete);
	CLAUSE_LIMIT_BIND(SQLDelete);
}


CMD* SQLDelete::get_cmd() { return m_cmd.get(); }
const CMD* SQLDelete::get_cmd() const { return m_cmd.get(); };

void SQLDelete::init(CMDDelete&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDDelete>(std::move(cmd));
}


CLAUSE_FROM_IMPL(SQLDelete)
CLAUSE_WHERE_IMPL(SQLDelete)
CLAUSE_ORDER_BY_IMPL(SQLDelete)
CLAUSE_LIMIT_IMPL(SQLDelete)


bool SQLDelete::del()
{
	return !execute()->is_failed();
}
