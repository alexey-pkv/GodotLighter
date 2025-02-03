#ifndef GODOTLIGHTER_H
#define GODOTLIGHTER_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/SQLStmt.h"
#include "Objects/SQLErrors.h"

#include "SQL/SQLDrop.h"
#include "SQL/SQLDirect.h"
#include "SQL/SQLSelect.h"
#include "SQL/SQLDelete.h"
#include "SQL/SQLUpdate.h"
#include "SQL/SQLInsert.h"
#include "SQL/SQLCreateTable.h"

#include <sqlighter.h>
#include <godot_cpp/classes/node.hpp>


namespace godot
{
	class SQLNode : public Node
	{
		AS_GD_CLASS(SQLNode, Node);
	private:
		uptr<sqlighter::SQLighter>	m_sql { nullptr };
		Ref<SQLErrors>				m_errors { nullptr };
		
		gstr m_path			{ ":memory:" };
		bool m_autoCreate	{ false };
		
		
	private:
		const Ref<SQLErrors>& errors_ref();
		
		
	public:
		~SQLNode() override;
		
		
	public: // Basic and init.
		gstr get_db_path() const;
		void set_db_path(const gstr& path);
		
		bool get_is_memory() const;
		void set_is_memory(bool value);
		
		bool get_auto_create() const;
		void set_auto_create(bool value);
		
		void close();
		bool open();
		
		gstr get_full_path() const;
		
		Ref<SQLErrors> errors();
		void handle_error(const Ref<SQLErrorInfo>& e);
		
		
	public:
		bool execute(const gstr& query, const Array& binds);
		Ref<SQLStmt> execute_stmt(const gstr& query, const Array& binds);
		
		Dictionary query_row(const gstr& query, const Array& binds);
		Array query_row_numeric(const gstr& query, const Array& binds);
		Array query_all(const gstr& query, const Array& binds);
		Array query_column_all(const gstr& query, const Array& binds);
		Variant query_value(const gstr& query, const Array& binds);
		
		Array query_all_max(const gstr& query, const Array& binds, int failsafeLimit);
		Array query_column_all_max(const gstr& query, const Array& binds, int failsafeLimit);
		
		int count_rows(const gstr& table_name);
		
		
	public: // Transactions.
		bool begin();
		bool commit();
		bool rollback();
		
		bool reindex(const gstr& element);
		bool reindex_in(const gstr& scheme, const gstr& element);
		
		
	public: // SQLs
		Ref<SQLDirect>		direct();
		Ref<SQLSelect>		select();
		Ref<SQLInsert>		insert();
		Ref<SQLUpdate>		update();
		Ref<SQLDelete>		del();
		Ref<SQLCreateTable>	create_table();
		Ref<SQLDrop>		drop();
	};
}


#endif