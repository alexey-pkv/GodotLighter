#include "helpers.h"


#include <godot_cpp/classes/node.hpp>


using namespace godot;


Node* godot::get_first_parent_by_class(const Node* from, const char* name)
{
	auto n = from->get_parent();
	
	while (n)
	{
		if (n->get_class() == name)
			return n;
		
		n = n->get_parent();
	}
	
	return nullptr;
}