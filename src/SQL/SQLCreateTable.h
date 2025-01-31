#ifndef GODOTLIGHTER_SQLCREATETABLE_H
#define GODOTLIGHTER_SQLCREATETABLE_H


#include "SQLCommand.h"


namespace godot
{
	class SQLCreateTable : public SQLCommand
	{
		AS_GD_CLASS(SQLCreateTable, SQLCommand);
	private:
		uptr<sqlighter::CMDCreateTable> m_cmd { nullptr };
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		Ref<SQLCreateTable> temp();
		Ref<SQLCreateTable> if_not_exists();
		Ref<SQLCreateTable> table(const gstr& name);
		Ref<SQLCreateTable> table_in(const gstr& scheme, const gstr& name);
		Ref<SQLCreateTable> column_exp(const gstr& exp);
		Ref<SQLCreateTable> without_rowid();
		Ref<SQLCreateTable> strict();
		
		bool create();
		
		
	public: // Internals
		void init(sqlighter::CMDCreateTable&& cmd, const Ref<SQLErrors>& errors);
	};
}


#endif