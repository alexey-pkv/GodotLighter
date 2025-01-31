#ifndef GODOTLIGHTER_SQLINSERT_H
#define GODOTLIGHTER_SQLINSERT_H


#include "SQLCommand.h"
#include "Utils/macros.h"

#include <connectors/CMDInsert.h>


namespace godot
{
	class SQLInsert : public SQLCommand
	{
		AS_GD_CLASS(SQLInsert, SQLCommand);
	private:
		uptr<sqlighter::CMDInsert> m_cmd { nullptr };
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		Ref<SQLInsert> as(const gstr& alias);
		Ref<SQLInsert> into(const gstr& table);
		Ref<SQLInsert> into_scheme(const gstr& scheme, const gstr& table);
		
		Ref<SQLInsert> default_values();
		Ref<SQLInsert> on_conflict_do_nothing();
		Ref<SQLInsert> on_conflict(const gstr& column);
		
		Ref<SQLInsert> column(const gstr& name);
		Ref<SQLInsert> columns(const Array& names);
		Ref<SQLInsert> record(const Array& values);
		Ref<SQLInsert> records(const Array& values_set);
		
		
	public:
		CLAUSE_OR_HEADER(SQLInsert);
		CLAUSE_SET_HEADER(SQLInsert);
		
		
	public:
		bool insert();
		
		
	public: // Internals
		void init(sqlighter::CMDInsert&& cmd, const Ref<SQLErrors>& errors);
	};
}


#endif
