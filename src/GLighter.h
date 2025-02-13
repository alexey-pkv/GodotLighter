#ifndef GODOTLIGHTER_GLIGHTER_H
#define GODOTLIGHTER_GLIGHTER_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/SQLStmt.h"
#include "Objects/SQLErrors.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>


namespace godot
{
	class GLighter : public Object
	{
		AS_GD_CLASS(GLighter, Object);
	private:
		static Ref<SQLErrors> m_errors;
	
		
	public:
		static Ref<SQLErrors> errors();
		
		
	public:
		static gstr sqlite_version();
		static gstr sqlighter_version();
		static gstr godotlighter_version();
		static gstr versions_info();
		
		
	public: // Internals
		inline static void handle_error(const excp& e)
		{
			errors()->handle_error_only(e);
		}
		
		inline static void generic_error(const char* message)
		{
			handle_error({ SQLIGHTER_ERR_GENERIC, message });
		}
		
		inline static bool is_editor()
		{
			return Engine::get_singleton()->is_editor_hint();
		}
	};
}


#endif