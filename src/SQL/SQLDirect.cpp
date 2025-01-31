#include "SQLDirect.h"


#include "GLighter.h"
#include "Utils/types.h"


using namespace godot;
using namespace sqlighter;


void SQLDirect::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("append", "query_string", "binds"),	&SQLDirect::append);
}


sqlighter::CMD* SQLDirect::get_cmd() { return m_cmd.get(); }
const sqlighter::CMD* SQLDirect::get_cmd() const { return m_cmd.get(); };

void SQLDirect::init(sqlighter::CMDDirect&& cmd, const Ref<SQLErrors>& errors)
{
	m_cmd = std::make_unique<sqlighter::CMDDirect>(std::move(cmd));
	init_errors(errors);
}

Ref<SQLDirect> SQLDirect::append(const gstr& query, const Array& binds)
{
	try
	{
		m_cmd->append(
			str2str(query),
			var2val(binds)
		);
	}
	catch (const excp& e)
	{
		handle_error(e);
	}
	
	return { this };
}
