#ifndef GODOTLIGHTER_SQLSELECT_H
#define GODOTLIGHTER_SQLSELECT_H


#include "SQLCommand.h"
#include "Utils/macros.h"
#include "SQL/Clause/FromClause.h"

#include <connectors/CMDSelect.h>


namespace godot
{
	class SQLSelect : 
		public SQLCommand 
	{
		AS_GD_CLASS(SQLSelect, SQLCommand);
	private:
		uptr<sqlighter::CMDSelect> m_cmd { nullptr };
		str m_scheme {};
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		Ref<SQLSelect> distinct();
		
		Ref<SQLSelect> column_exp(const gstr& expression, const Array& binds);
		Ref<SQLSelect> column(const gstr& column);
		Ref<SQLSelect> column_as(const gstr& column, const gstr& as);
		Ref<SQLSelect> columns(const Array& columns);
		
	public:
		CLAUSE_FROM_HEADER(SQLSelect);
		CLAUSE_WHERE_HEADER(SQLSelect);
		CLAUSE_ORDER_BY_HEADER(SQLSelect);
		CLAUSE_LIMIT_HEADER(SQLSelect);
		
		
	public:
		Ref<SQLSelect> join_exp(const gstr&exp, const Array& binds);
		
		Ref<SQLSelect> join(
			const gstr&what,
			const gstr&as,
			const gstr&condition,
			const Array& binds);
		
		Ref<SQLSelect> left_join(
			const gstr&what,
			const gstr&as,
			const gstr&condition,
			const Array& binds);
		
		Ref<SQLSelect> right_join(
			const gstr&what,
			const gstr&as,
			const gstr&condition,
			const Array& binds);
		
		
	public:
		Dictionary query_row();
		Array query_row_numeric();
		Array query_all();
		Array query_column_all();
		Variant query_value();
		
		Array query_all_max(int failsafeLimit);
		Array query_column_all_max(int failsafeLimit);
		
		
	public: // Internals
		void init(sqlighter::CMDSelect&& cmd, const Ref<SQLErrors>& errors);
	};
}


#endif