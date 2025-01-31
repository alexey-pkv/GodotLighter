#ifndef GODOTLIGHTER_SQLCOMMAND_H
#define GODOTLIGHTER_SQLCOMMAND_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/SQLStmt.h"

#include <connectors/CMDDirect.h>


namespace godot
{
	class SQLCommand : public RefCounted
	{
		AS_GD_CLASS(SQLCommand, RefCounted);
	private:
		virtual sqlighter::CMD* get_cmd() = 0;
		virtual const sqlighter::CMD* get_cmd() const = 0;
		
		
	public:
		gstr assemble() const;
		Array binds() const;
		Ref<SQLStmt> execute();
	};
}


#endif