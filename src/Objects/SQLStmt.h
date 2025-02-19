#ifndef GODOTLIGHTER_SQLSTMT_H
#define GODOTLIGHTER_SQLSTMT_H


#include <sqlighter.h>
#include <godot_cpp/classes/ref_counted.hpp>

#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/SQLErrors.h"
#include "Objects/SQLErrorInfo.h"


namespace godot
{
	class SQLStmt : public RefCounted
	{
		AS_GD_CLASS(SQLStmt, RefCounted)
	private:
		stmt 				m_stmt;
		Ref<SQLErrorInfo>	m_error { nullptr };
		Ref<SQLErrors>		m_errors { nullptr };
		vec<gstr>			m_column_names {};
		
		
	private:
		int require_column(const gstr& name);
		void rows_limit_reached_error(int limit);
		void number_of_columns_and_rows_error();
		void handle_error(const sqlighter::SQLighterException& e);
		void handle_error(sqlighter::SQLighterException&& e);
		void store_column_names();
		
		
	public: // Error
		bool is_failed();
		Ref<SQLErrorInfo> get_err();
		
		
	public:
		int code() const;
		bool is_done() const;
		bool is_ok() const;
		bool is_error() const;
		bool has_row() const;
		gstr query_string() const;
		
		int step();
		int close();
		
		
	public:
		Variant value();
		
		Variant column_value(const gstr& name);
		Variant column_value_i(int at);
		
		int64_t column_int_i(int at);
		bool column_bool_i(int at);
		double column_double_i(int at);
		gstr column_string_i(int at);
		bool column_is_null_i(int at);
		
		int64_t column_int(const gstr& name);
		bool column_bool(const gstr& name);
		double column_double(const gstr& name);
		gstr column_string(const gstr& name);
		bool column_is_null(const gstr& name);
		
		Array row_numeric();
		Dictionary row();
		Array all_numeric();
		Array all();
		Array column_all();
		Array all_numeric_max(int failsafeLimit);
		Array all_max(int failsafeLimit);
		Array column_all_max(int failsafeLimit);
		
		Array column_names();
		
		
	public: // Internal
		static Ref<SQLStmt> from_error(const Ref<SQLErrors>& errors, const excp& err);
		static Ref<SQLStmt> from_error(const Ref<SQLErrors>& errors, const Ref<SQLErrorInfo>& err);
		static Ref<SQLStmt> from_stmt(const Ref<SQLErrors>& errors, stmt&& s);
	};
}


#endif