#ifndef GODOTLIGHTER_GLIGHTER_H
#define GODOTLIGHTER_GLIGHTER_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Exceptions/GLighterException.h"

#include <godot_cpp/classes/object.hpp>


namespace godot
{
	class GLighter : public Object
	{
		AS_GD_CLASS(GLighter, Object);	
	private:
		static Ref<GLighterException>	m_e;
		static bool						m_printErrors;
		
		
	public:
		static bool has_err();
		static Ref<GLighterException> last_err();
		static void reset_error();
		static void set_print_errors(bool to);
		
		
	public:
		static gstr sqlite_version();
		static gstr sqlighter_version();
		static gstr godotlighter_version();
		static gstr versions_info();
		
		
	public: // Internals
		static void handle_error(const excp& e);
	};
}


#endif