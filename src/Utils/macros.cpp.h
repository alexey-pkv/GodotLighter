#ifndef GODOTLIGHTER_MACROS_CPP_H
#define GODOTLIGHTER_MACROS_CPP_H


#define CLAUSE_FROM_IMPL(class)														\
	Ref<class> class::as(const gstr& alias)											\
	{																				\
		m_cmd->as(str2str(alias));													\
		return { this };															\
	}																				\
																					\
	Ref<class> class::from(const gstr& table)										\
	{																				\
		m_cmd->from(str2str(table));												\
		return { this };															\
	}																				\
																					\
	Ref<class> class::from_scheme(const gstr& scheme, const gstr& table)			\
	{																				\
		m_cmd->from(str2str(scheme), str2str(table));								\
		return { this };															\
	}

#define CLAUSE_FROM_BIND(class)																	\
	ClassDB::bind_method(D_METHOD("as", "alias"),						&class::as);			\
	ClassDB::bind_method(D_METHOD("from", "table"),						&class::from);			\
	ClassDB::bind_method(D_METHOD("from_scheme", "scheme", "table"),	&class::from_scheme);

#define CLAUSE_OR_IMPL(class)													\
	Ref<class> class::or_rollback()	{ m_cmd->or_rollback(); return { this }; }	\
	Ref<class> class::or_fail()		{ m_cmd->or_fail(); return { this }; }		\
	Ref<class> class::or_replace()	{ m_cmd->or_replace(); return { this }; }	\
	Ref<class> class::or_ignore()	{ m_cmd->or_ignore(); return { this }; }	\
	Ref<class> class::or_abort()	{ m_cmd->or_abort(); return { this }; }		

#define CLAUSE_OR_BIND(class)																	\
	ClassDB::bind_method(D_METHOD("or_rollback"),	&class::or_rollback);	\
	ClassDB::bind_method(D_METHOD("or_fail"),		&class::or_fail);		\
	ClassDB::bind_method(D_METHOD("or_replace"),	&class::or_replace);	\
	ClassDB::bind_method(D_METHOD("or_ignore"),		&class::or_ignore);		\
	ClassDB::bind_method(D_METHOD("or_abort"),		&class::or_abort);			

#define CLAUSE_SET_IMP(class)														\
	Ref<class> class::set_exp(const gstr& expression, const Array& binds)	 		\
	{																				\
		TRY_SQLIGHTER_ACTION(m_cmd->set_exp(str2str(expression), var2val(binds)));	\
		return { this };															\
	}																				\
																					\
	Ref<class> class::set(const gstr& field, const Variant& value)					\
	{																				\
		TRY_SQLIGHTER_ACTION(m_cmd->set(str2str(field), var2val_unsafe(value)));	\
		return { this };															\
	}

#define CLAUSE_SET_BIND(class)																\
	ClassDB::bind_method(D_METHOD("set", "field", "value"),				&class::set);		\
	ClassDB::bind_method(D_METHOD("set_exp", "expression", "binds"),	&class::or_abort);

#define CLAUSE_TABLE_IMPL(class)										\
	Ref<class> class::as(const gstr& alias)								\
	{																	\
		m_cmd->as(str2str(alias));										\
		return { this };												\
	}																	\
																		\
	Ref<class> class::table(const gstr& table)							\
	{																	\
		m_cmd->table(str2str(table));									\
		return { this };												\
	}																	\
																		\
	Ref<class> class::table_in(const gstr& scheme, const gstr& table)	\
	{																	\
		m_cmd->table(str2str(scheme), str2str(table));					\
		return { this };												\
	}

#define CLAUSE_TABLE_BIND(class)														\
	ClassDB::bind_method(D_METHOD("as", "alias"),					&class::as);		\
	ClassDB::bind_method(D_METHOD("table", "table"),				&class::table);		\
	ClassDB::bind_method(D_METHOD("table_in", "scheme", "table"),	&class::table_in);

#define CLAUSE_WHERE_IMPL(class)														\
	Ref<class> class::where(const gstr& expression, const Array& binds)					\
	{																					\
		TRY_SQLIGHTER_ACTION(m_cmd->where(str2str(expression), var2val(binds)));		\
		return { this };																\
	}																					\
																						\
	Ref<class> class::where_null(const gstr& column)									\
	{																					\
		TRY_SQLIGHTER_ACTION(m_cmd->where_null(str2str(column)));						\
		return { this };																\
	}																					\
																						\
	Ref<class> class::where_not_null(const gstr& column)								\
	{																					\
		TRY_SQLIGHTER_ACTION(m_cmd->where_not_null(str2str(column)));					\
		return { this };																\
	}																					\
																						\
	Ref<class> class::by_field(const gstr& column, const Variant& value)				\
	{																					\
		TRY_SQLIGHTER_ACTION(m_cmd->by_field(str2str(column), var2val_unsafe(value)));	\
		return { this };																\
	}

#define CLAUSE_WHERE_BIND(class)																	\
	ClassDB::bind_method(D_METHOD("where", "expression", "binds"),		&class::where);				\
	ClassDB::bind_method(D_METHOD("where_null", "column"),				&class::where_null);		\
	ClassDB::bind_method(D_METHOD("where_not_null", "column"),			&class::where_not_null);	\
	ClassDB::bind_method(D_METHOD("by_field", "column", "value"),		&class::by_field);

#define CLAUSE_ORDER_BY_IMPL(class)													\
	Ref<class> class::order_by_exp(const gstr& exp, const Array& binds)				\
	{																				\
		TRY_SQLIGHTER_ACTION(m_cmd->order_by(str2str(exp), var2val(binds)));		\
		return { this };															\
	}																				\
																					\
	Ref<class> class::order_by_field(const gstr& field, bool asc)					\
	{																				\
		auto order = asc ? OrderBy::ASC : OrderBy::DESC;							\
																					\
		TRY_SQLIGHTER_ACTION(m_cmd->order_by_field(str2str(field), order));			\
																					\
		return { this };															\
	}																				\
																					\
	Ref<class> class::order_by_field_asc(const gstr& field)							\
	{																				\
		TRY_SQLIGHTER_ACTION(m_cmd->order_by_field(str2str(field), OrderBy::ASC));	\
		return { this };															\
	}																				\
																					\
	Ref<class> class::order_by_field_desc(const gstr& field)						\
	{																				\
		TRY_SQLIGHTER_ACTION(m_cmd->order_by_field(str2str(field), OrderBy::DESC));	\
		return { this };															\
	}

#define CLAUSE_ORDER_BY_BIND(class)																		\
	ClassDB::bind_method(D_METHOD("order_by_exp", "exp", "binds"),		&class::order_by_exp);			\
	ClassDB::bind_method(D_METHOD("order_by_field", "field", "asc"),	&class::order_by_field);		\
	ClassDB::bind_method(D_METHOD("order_by_field_asc", "field"),		&class::order_by_field_asc);	\
	ClassDB::bind_method(D_METHOD("order_by_field_desc", "field"),		&class::order_by_field_desc);

#define CLAUSE_LIMIT_IMPL(class)						\
	Ref<class> class::limit_by(int count)				\
	{													\
		m_cmd->limit_by(count);							\
		return { this };								\
	}													\
														\
	Ref<class> class::limit(int offset, int count)		\
	{													\
		m_cmd->limit(offset, count);					\
		return { this };								\
	}													\
														\
	Ref<class> class::page(int page, int page_size)		\
	{													\
		m_cmd->page(page, page_size);					\
		return { this };								\
	}

#define CLAUSE_LIMIT_BIND(class)															\
	ClassDB::bind_method(D_METHOD("limit_by", "count"),					&class::limit_by);	\
	ClassDB::bind_method(D_METHOD("limit", "offset", "count"),			&class::limit);		\
	ClassDB::bind_method(D_METHOD("page", "page", "page_size"),			&class::page);		


#endif