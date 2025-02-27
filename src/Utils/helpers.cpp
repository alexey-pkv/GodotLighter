#include "helpers.h"


#include <godot_cpp/classes/node.hpp>


using namespace godot;


Node* godot::get_first_parent_by_class(const Node* from, const char* name)
{
	auto n = from->get_parent();
	
	while (n)
	{
		auto class_name = n->get_class();
		
		if (class_name == name)
			// Need to support parent classes:
			// || ClassDB::is_parent_class(class_name, name))
		{
			return n;
		}
		
		n = n->get_parent();
	}
	
	return nullptr;
}