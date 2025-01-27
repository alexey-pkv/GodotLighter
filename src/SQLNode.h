#ifndef GODOTLIGHTER_H
#define GODOTLIGHTER_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/GLighterStmt.h"

#include "SQL/SQLDirect.h"
#include "SQL/SQLSelect.h"
#include "SQL/SQLDelete.h"
#include "SQL/SQLDrop.h"
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
		
		gstr m_path			{};
		bool m_autoCreate	{ false };
		
		
	private:
		bool open();
		
		
	public: // Basic and init.
		gstr get_db_path() const;
		void set_db_path(const gstr& path);
		
		bool get_auto_create() const;
		void set_auto_create(bool value);
		
		void close();
		
		gstr get_full_path() const;
		
		
	public:
		bool execute(const gstr& query, const Array& binds);
		Ref<GLighterStmt> execute_stmt(const gstr& query, const Array& binds);
		
		Dictionary query_row(const gstr& query, const Array& binds);
		Array query_row_numeric(const gstr& query, const Array& binds);
		Array query_all(const gstr& query, const Array& binds);
		Array query_column_all(const gstr& query, const Array& binds);
		Variant query_value(const gstr& query, const Array& binds);
		
		Array query_all_max(const gstr& query, const Array& binds, int failsafeLimit);
		Array query_column_all_max(const gstr& query, const Array& binds, int failsafeLimit);
		
		int count_rows(const gstr& table_name);
		
	public: // Transactions.
		bool begin() const;
		bool commit() const;
		bool rollback() const;
		
		bool reindex(const gstr& element) const;
		bool reindex_in(const gstr& scheme, const gstr& element) const;
		
		
	public: // SQLs
		Ref<SQLDirect>		direct() const;
		Ref<SQLDelete>		del() const;
		Ref<SQLSelect>		select() const;
		Ref<SQLCreateTable>	create_table() const;
		Ref<SQLDrop>		drop() const;
		
		/*
		 * 
		
		
	public:
		CMDInsert		insert() const;
		CMDUpdate		update() const;
		
	public:
		 */
	};
}


#endif