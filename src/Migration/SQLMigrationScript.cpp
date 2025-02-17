#include "SQLMigrationScript.h"


#include "SQLNode.h"
#include "GLighter.h"
#include "Utils/types.h"
#include "Utils/helpers.h"

#include <sstream>


using namespace godot;


const char* SQLMigrationScript::UPDATE_METHOD = "_update";


void SQLMigrationScript::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("execute_update"),				&SQLMigrationScript::execute_update);
	ClassDB::bind_method(D_METHOD("execute_update_for", "node"),	&SQLMigrationScript::execute_update_for);
	
	
	ADD_SIGNAL(MethodInfo("before_update",
		PropertyInfo(
			Variant::OBJECT, "script",
			PROPERTY_HINT_NODE_TYPE, "SQLMigrationScript")));
	
	ADD_SIGNAL(MethodInfo("on_updated",
		PropertyInfo(
			Variant::OBJECT, "script",
			PROPERTY_HINT_NODE_TYPE, "SQLMigrationScript")));
	
	ADD_SIGNAL(MethodInfo("on_failed",
		PropertyInfo(
			Variant::OBJECT, "script",
			PROPERTY_HINT_NODE_TYPE, "SQLMigrationScript")));
}


bool SQLMigrationScript::trigger_complete_event(bool result)
{
	if (result)
	{
		emit_signal("on_updated", this);
	}
	else
	{
		emit_signal("on_failed", this);
	}
	
	return result;
}

bool SQLMigrationScript::validate_can_update(PackedStringArray& notes) const
{
	if (!has_method(UPDATE_METHOD))
	{
		std::stringstream ss;
		
		ss
			<< "Missing method '" 
			<< UPDATE_METHOD << "(node: SQLNode) -> void'"
			<< " in the migration script";
		
		notes.append(str2str(ss.str()));
		GLighter::handle_error({ SQLIGHTER_ERR_GENERIC, ss.str() });
		
		return false;
	}
	
	auto methodsList = get_method_list();
	
	for (int i = 0; i < methodsList.size(); i++)
	{
		auto methodData = (Dictionary)(methodsList[i]);
		
		if (methodData["name"] != UPDATE_METHOD)
			continue;
		
		auto returnValue	= (Dictionary)(methodData["return"]);
		auto returnType		= (Dictionary)(returnValue["type"]);
		auto args			= (Array)(methodData["args"]);
		
		if ((int)(returnValue["type"]) != 0 || 
			args.size() != 1 ||
			str2str(((Dictionary)(args[0]))["class_name"]) != "SQLNode")
		{
			std::stringstream ss;
			
			ss
				<< "Invalid method definition. Expecting '" 
				<< UPDATE_METHOD << "(node: SQLNode) -> void'";
			
			notes.append(str2str(ss.str()));
			GLighter::handle_error({ SQLIGHTER_ERR_GENERIC, ss.str() });
			return false;
		}
		
		break;
	}
	
	return true;
}

bool SQLMigrationScript::run_execute_for_node(SQLNode* node)
{
	emit_signal("before_update", this);
	
	GLighter::errors()->reset_error();
	
	if (!validate_can_update())
	{
		return trigger_complete_event(false);
	}
	
	call(UPDATE_METHOD, node);
	
	return trigger_complete_event(!GLighter::errors()->has_err());
}


bool SQLMigrationScript::execute_update()
{
	auto node = get_first_parent_by_class(this, "SQLNode");
	
	if (node == nullptr)
	{
		GLighter::handle_error({ SQLIGHTER_ERR_GENERIC, "No parent SQLNode found in execute_update" });
		return trigger_complete_event(false);
	}
	
	return run_execute_for_node((SQLNode*)node);
}

bool SQLMigrationScript::execute_update_for(SQLNode* node)
{
	if (node == nullptr)
	{
		GLighter::handle_error({ SQLIGHTER_ERR_GENERIC, "SQLNode expected, by got null in execute_update_for" });
		return trigger_complete_event(false);
	}
	
	return run_execute_for_node(node);
}


PackedStringArray SQLMigrationScript::_get_configuration_warnings() const
{
	PackedStringArray a;
	
	validate_can_update(a);
	
	return a;
}
