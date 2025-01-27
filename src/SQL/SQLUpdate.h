#ifndef GODOTLIGHTER_SQLUPDATE_H
#define GODOTLIGHTER_SQLUPDATE_H


#include "SQLCommand.h"
#include "Utils/macros.h"

#include <connectors/CMDUpdate.h>


namespace godot
{
	class SQLUpdate : public SQLCommand
	{
		AS_GD_CLASS(SQLUpdate, SQLCommand);
	private:
		uptr<sqlighter::CMDUpdate> m_cmd { nullptr };
		str m_scheme {};
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		CLAUSE_TABLE_HEADER(SQLUpdate);
		CLAUSE_OR_HEADER(SQLUpdate);
		CLAUSE_SET_HEADER(SQLUpdate);
		CLAUSE_WHERE_HEADER(SQLUpdate);
		
		
	public:
		bool update();
		
		
	public: // Internals
		void init(sqlighter::CMDUpdate&& cmd);
	};
}


#endif