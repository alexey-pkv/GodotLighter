#include "SQLDrop.h"


#include "Utils/types.h"


using namespace godot;
using namespace sqlighter;


#define CALL_DROP(func) \
	if (m_scheme.empty()) \
	{ \
		m_cmd->func(str2str(name)); \
	} \
	else \
	{ \
		m_cmd->func(m_scheme, str2str(name)); \
	}


void SQLDrop::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("if_exists"),			&SQLDrop::if_exists);
	ClassDB::bind_method(D_METHOD("scheme", "name"),	&SQLDrop::scheme);
	ClassDB::bind_method(D_METHOD("table", "name"),		&SQLDrop::table);
	ClassDB::bind_method(D_METHOD("view", "name"),		&SQLDrop::view);
	ClassDB::bind_method(D_METHOD("trigger", "name"),	&SQLDrop::trigger);
	ClassDB::bind_method(D_METHOD("index", "name"),		&SQLDrop::index);
	
	ClassDB::bind_method(D_METHOD("drop"), &SQLDrop::drop);
}


CMD* SQLDrop::get_cmd() { return m_cmd.get(); }
const CMD* SQLDrop::get_cmd() const { return m_cmd.get(); };


void SQLDrop::init(CMDDrop&& cmd)
{
	m_cmd = std::make_unique<sqlighter::CMDDrop>(std::move(cmd));
}


Ref<SQLDrop> SQLDrop::if_exists()
{
	m_cmd->if_exists();
	return { this };
}

Ref<SQLDrop> SQLDrop::scheme(const gstr& name)
{
	m_scheme = str2str(name);
	return { this };
}

Ref<SQLDrop> SQLDrop::table(const gstr& name)
{
	CALL_DROP(table);
	return { this };
}

Ref<SQLDrop> SQLDrop::view(const gstr& name)
{
	CALL_DROP(view);
	return { this };
}

Ref<SQLDrop> SQLDrop::trigger(const gstr& name)
{
	CALL_DROP(trigger);
	return { this };
}

Ref<SQLDrop> SQLDrop::index(const gstr& name)
{
	CALL_DROP(index);
	return { this };
}

bool SQLDrop::drop()
{
	return !execute()->is_failed();
}
