#ifndef GODOTLIGHTER_MIGRATIONNODE_H
#define GODOTLIGHTER_MIGRATIONNODE_H


#include "Utils/gd_class.h"

#include <godot_cpp/classes/node.hpp>


namespace godot
{
	class MigrationNode : public Node
	{
		AS_GD_CLASS(MigrationNode, Node);
	private:
	};
}


#endif
