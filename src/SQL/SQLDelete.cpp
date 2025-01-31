#include "SQLDelete.h"


#include "Utils/types.h"
#include "Utils/macros.cpp.h"
#include "SQL/Clause/FromClause.h"
#include "SQL/Clause/LimitClause.h"
#include "SQL/Clause/OrderByClause.h"
#include "SQL/Clause/WhereClause.h"

#include "GLighter.h"


using namespace godot;
using namespace sqlighter;


void SQLDelete::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("del"), &SQLDelete::del);
	
	bind_from<SQLDelete>();
	bind_limit<SQLDelete>();
	bind_order_by<SQLDelete>();
	bind_where<SQLDelete>();
}


CMD* SQLDelete::get_cmd() { return m_cmd.get(); }
const CMD* SQLDelete::get_cmd() const { return m_cmd.get(); };

void SQLDelete::init(CMDDelete&& cmd, const Ref<SQLErrors>& errors)
{
	m_cmd = std::make_unique<sqlighter::CMDDelete>(std::move(cmd));
	init_errors(errors);
}


CLAUSE_FROM_IMPL(SQLDelete)
CLAUSE_WHERE_IMPL(SQLDelete)
CLAUSE_ORDER_BY_IMPL(SQLDelete)
CLAUSE_LIMIT_IMPL(SQLDelete)


bool SQLDelete::del()
{
	return !execute()->is_failed();
}
