#ifndef GODOTLIGHTER_MACROS_H
#define GODOTLIGHTER_MACROS_H


#define RETURN_TRY_SQLIGHTER_ACTION(what) \
	try	{ \
		what; \
    	return true; \
	} \
	catch (const excp& e) { \
		godot::GLighter::handle_error(e); \
		return false; \
	}

#define RETURN_TRY_SQLIGHTER_VALUE(what, default_value) \
	try	{ \
    	return what; \
	} \
	catch (const excp& e) { \
		godot::GLighter::handle_error(e); \
		return default_value; \
	}


#endif