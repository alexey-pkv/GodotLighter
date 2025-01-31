#ifndef GODOTLIGHTER_SQLDIRECT_H
#define GODOTLIGHTER_SQLDIRECT_H


#include "SQLCommand.h"

#include <connectors/CMDDirect.h>


namespace godot
{
	class SQLDirect : public SQLCommand
	{
		AS_GD_CLASS(SQLDirect, SQLCommand);
	private:
		uptr<sqlighter::CMDDirect> m_cmd { nullptr };
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		Ref<SQLDirect> append(const gstr& query, const Array& binds);
		
		
	public: // Internals
		void init(sqlighter::CMDDirect&& cmd, const Ref<SQLErrors>& errors);
	};
}


#endif