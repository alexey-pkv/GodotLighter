#ifndef GODOTLIGHTER_H
#define GODOTLIGHTER_H


#include <godot_cpp/classes/node.hpp>


namespace godot
{
	class SQLNode : public Node
	{
		GDCLASS(SQLNode, Node);
		
		
	protected:
		static void _bind_methods();
		
		
	public:
		SQLNode() = default;
		~SQLNode() override = default;
		
		
	public:
		static godot::String sqlite_version();
		static godot::String sqlighter_version();
		static godot::String library_version();
	};
}


#endif