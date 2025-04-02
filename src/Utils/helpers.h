#ifndef GODOTLIGHTER_HELPERS_H
#define GODOTLIGHTER_HELPERS_H


namespace godot
{
	class Node;
	
	
	Node* get_first_parent_by_class(const Node* from, const char* name);
}


#endif
