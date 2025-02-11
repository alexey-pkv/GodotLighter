#ifndef GODOTLIGHTER_TYPES_H
#define GODOTLIGHTER_TYPES_H


#include <core/Stmt.h>
#include <core/ScalarValue.h>
#include <exceptions/sqlighter_exceptions.h>

#include <memory>
#include <string>
#include <sstream>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>


namespace godot
{
	const int DEFAULT_FAILSAFE	= 10000; 
	
	
	typedef godot::String gstr;
	typedef std::string str;
	
	template<typename T>
	using vec = std::vector<T>;
	
	template<typename T>
	using uptr = std::unique_ptr<T>;
	
	template<typename T>
	using sptr = std::shared_ptr<T>;
	
	inline gstr str2str(const std::ostringstream& ss) { return { ss.str().c_str() }; }
	inline gstr str2str(std::string_view sv) { return { sv.data() }; }
	inline gstr str2str(const char* c) { return { c }; }
	inline gstr str2str(const str& s) { return { s.c_str() }; }
	inline str str2str(const gstr& s) { return { s.utf8().get_data() }; }
	
	template <typename T>
	inline Ref<T> make_ref()
	{
		Ref<T> r;
		r.instantiate();
		return r;
	}
	
	template<class T, class ... ARGS>
	Ref<T> make_ref(const ARGS& ... args)
	{
		Ref<T> r;
		r.instantiate();
		r->init(args...);
		return r;
	}
	
	template<class T, class MARG>
	Ref<T> make_ref(MARG&& marg)
	{
		Ref<T> r;
		r.instantiate();
		r->init(std::forward<MARG>(marg));
		return r;
	}
	
	Variant val2var(const sqlighter::ScalarValue& val);
	Variant val2var(const sqlighter::BindValue& val);
	Array val2var(const vec<sqlighter::BindValue>& val);
	bool var2val(const Variant& var, sqlighter::BindValue& val);
	sqlighter::BindValue var2val_unsafe(const godot::Variant& var);
	vec<sqlighter::BindValue> var2val(const godot::Array& vars);
	
	typedef sqlighter::Stmt					stmt;
	typedef sqlighter::SQLighterException	excp;
}


#endif