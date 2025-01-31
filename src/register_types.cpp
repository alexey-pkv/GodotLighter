#include "register_types.h"


#include "SQLNode.h"
#include "GLighter.h"


#include <gdextension_interface.h>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/defs.hpp>


using namespace godot;


void godot::initialize_godotlighter_module(ModuleInitializationLevel p_level) 
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	
	
	ClassDB::register_class<SQLErrorInfo>();
	ClassDB::register_class<SQLStmt>();
	
	ClassDB::register_abstract_class<SQLCommand>();
	ClassDB::register_class<SQLDirect>();
	ClassDB::register_class<SQLSelect>();
	ClassDB::register_class<SQLInsert>();
	ClassDB::register_class<SQLUpdate>();
	ClassDB::register_class<SQLDelete>();
	ClassDB::register_class<SQLCreateTable>();
	ClassDB::register_class<SQLDrop>();
	
	ClassDB::register_class<SQLNode>();
	ClassDB::register_abstract_class<GLighter>();
}

void godot::uninitialize_godotlighter_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) 
	{
		return;
	}
}


extern "C" 
{
	GDExtensionBool GDE_EXPORT godotlighter_library_init(
		GDExtensionInterfaceGetProcAddress	p_get_proc_address, 
		const GDExtensionClassLibraryPtr	p_library, 
		GDExtensionInitialization			*r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		
		init_obj.register_initializer(initialize_godotlighter_module);
		init_obj.register_terminator(uninitialize_godotlighter_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
		
		return init_obj.init();
	}
}