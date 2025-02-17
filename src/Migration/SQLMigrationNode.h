#ifndef GODOTLIGHTER_SQLMIGRATIONNODE_H
#define GODOTLIGHTER_SQLMIGRATIONNODE_H


#include "Utils/gd_class.h"
#include "Utils/types.h"
#include "SQL/SQLCreateTable.h"

#include <godot_cpp/classes/node.hpp>


namespace godot
{
	class SQLNode;
	class SQLMigrationScript;
	
	
	class SQLMigrationNode : public Node
	{
		AS_GD_CLASS(SQLMigrationNode, Node);
	private:
		bool	m_autoFree			{ false };
		bool	m_autoRun			{ false };
		bool	m_isOneTime			{ false };
		gstr	m_migrationTable	{ "_glighter_migration_" };
		
		
	private:
		static bool validate_db_empty(SQLNode* node);
		
		void insert_migration_log(SQLNode* node, int seq, const gstr& name, const gstr& error) const;
		bool run_migration(SQLNode* node, int offset);
		
		SQLNode* try_get_parent_sql() const;
		bool create_migration_table_for(SQLNode* node) const;
		bool run_execute_for_node(SQLNode* node);
		
		
	private:
		static bool no_errors();
		
		
	public:
		PackedStringArray _get_configuration_warnings() const override;
		void _enter_tree() override;
	
	
	public:
		bool get_auto_free() const;
		void set_auto_free(bool val);
		bool get_auto_run() const;
		void set_auto_run(bool val);
		bool get_is_one_time() const;
		void set_is_one_time(bool val);
		bool is_migration_table_exists_for(SQLNode* node) const;
		
		const gstr& get_migration_table() const;
		void set_migration_table(const gstr& to);
		
		
	public:
		bool execute();
		
		bool create_migration_table() const;
		bool is_migration_table_exists() const;
		
		Array get_migration_scripts_metadata() const;
		Array get_migration_log(bool includeErrors) const;
		Array get_desync_issues() const;
		bool is_up_to_date() const;
	};
}


#endif
