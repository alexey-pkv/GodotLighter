#ifndef GODOTLIGHTER_SQLDELETE_H
#define GODOTLIGHTER_SQLDELETE_H


#include "SQLCommand.h"
#include "Utils/macros.h"

#include <connectors/CMDDelete.h>


namespace godot
{
	class SQLDelete : public SQLCommand
	{
		AS_GD_CLASS(SQLDelete, SQLCommand);
	private:
		uptr<sqlighter::CMDDelete> m_cmd { nullptr };
		str m_scheme {};
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		bool del();
		
		CLAUSE_FROM_HEADER(SQLDelete);
		CLAUSE_WHERE_HEADER(SQLDelete);
		CLAUSE_ORDER_BY_HEADER(SQLDelete);
		CLAUSE_LIMIT_HEADER(SQLDelete);
		
		
	public: // Internals
		void init(sqlighter::CMDDelete&& cmd);
	};
}


#endif