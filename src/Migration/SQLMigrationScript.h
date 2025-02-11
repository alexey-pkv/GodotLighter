#ifndef GODOTLIGHTER_SQLMIGRATIONSCRIPT_H
#define GODOTLIGHTER_SQLMIGRATIONSCRIPT_H


#include "Utils/gd_class.h"
#include "Utils/types.h"

#include <godot_cpp/classes/node.hpp>


namespace godot
{
	class SQLNode;
	
	
	class SQLMigrationScript : public Node
	{
		AS_GD_CLASS(SQLMigrationScript, Node);
	private:
		static const char* UPDATE_METHOD;
		
		
	private:
		bool trigger_complete_event(bool result);
		SQLNode* get_parent_sql_node() const;
		bool validate_can_update(PackedStringArray& notes) const;
		bool run_execute_for_node(SQLNode* node);
		
		inline bool validate_can_update() const { PackedStringArray notes; return validate_can_update(notes); }
		
		
	public:
		PackedStringArray _get_configuration_warnings() const override;
		
		
	public:
		bool execute_update();
		bool execute_update_for(SQLNode* node);
	};
}


#endif