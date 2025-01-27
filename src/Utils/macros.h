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

#define TRY_SQLIGHTER_ACTION(what) \
	try	{ what; } \
	catch (const excp& e) { godot::GLighter::handle_error(e); }

#define RETURN_TRY_SQLIGHTER_VALUE(what, default_value) \
	try	{ \
		return what; \
	} \
	catch (const excp& e) { \
		godot::GLighter::handle_error(e); \
		return default_value; \
	}

#define RETURN_TRY_SQLIGHTER_STMT(what) \
	try	{ \
		return GLighterStmt::from_stmt(what); \
	} \
	catch (const excp& e) { \
		godot::GLighter::handle_error(e); \
		return GLighterStmt::from_error(e); \
	}

#define CLAUSE_WHERE_HEADER(class) \
	Ref<class> where(const gstr& expression, const Array& binds); \
	Ref<class> where_null(const gstr& column); \
	Ref<class> where_not_null(const gstr& column); \
	Ref<class> by_field(const gstr& column, const Variant& value);

#define CLAUSE_OR_HEADER(class) \
	Ref<class> or_abort();		\
	Ref<class> or_fail();		\
	Ref<class> or_ignore();		\
	Ref<class> or_replace();	\
	Ref<class> or_rollback();

#define CLAUSE_SET_HEADER(class)									\
	Ref<class> set(const gstr& field, const Variant& value);		\
	Ref<class> set_exp(const gstr& expression, const Array& binds);

#define CLAUSE_ORDER_BY_HEADER(class) \
	Ref<class> order_by_exp(const gstr& exp, const Array& binds); \
	Ref<class> order_by_field(const gstr& field, bool asc); \
	Ref<class> order_by_field_asc(const gstr& field); \
	Ref<class> order_by_field_desc(const gstr& field);

#define CLAUSE_LIMIT_HEADER(class)					\
	Ref<class> limit_by(int count);					\
	Ref<class> limit(int offset, int count);		\
	Ref<class> page(int page, int page_size);

#define CLAUSE_FROM_HEADER(class)									\
	Ref<class> as(const gstr& alias);								\
	Ref<class> from(const gstr& table);								\
	Ref<class> from_scheme(const gstr& scheme, const gstr& table);

#define CLAUSE_TABLE_HEADER(class)									\
	Ref<class> as(const gstr& alias);								\
	Ref<class> table(const gstr& table);							\
	Ref<class> table_in(const gstr& scheme, const gstr& table);
		
#endif