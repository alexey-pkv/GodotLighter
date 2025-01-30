#include "SQLCommand.h"


#include "GLighter.h"
#include "Utils/macros.h"


using namespace godot;


void SQLCommand::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("assemble"),	&SQLCommand::assemble);
	ClassDB::bind_method(D_METHOD("binds"),		&SQLCommand::binds);
	
	ClassDB::bind_method(D_METHOD("execute"),	&SQLCommand::execute);
}


gstr SQLCommand::assemble() const
{
	return str2str(get_cmd()->assemble());
}

Array SQLCommand::binds() const
{
	return val2var(get_cmd()->bind());
}

Ref<GLighterStmt> SQLCommand::execute()
{
	return GLighter::try_stmt_action([&] { return get_cmd()->execute(); });
}
