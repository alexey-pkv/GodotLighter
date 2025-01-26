#ifndef GODOTLIGHTER_GLIGHTEREXCEPTION_H
#define GODOTLIGHTER_GLIGHTEREXCEPTION_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "exceptions/sqlighter_exceptions.h"

#include <godot_cpp/classes/ref_counted.hpp>


namespace godot
{
	class GLighterException : public RefCounted
	{
		AS_GD_CLASS(GLighterException, RefCounted);
	private:
		sqlighter::SQLighterException m_e { SQLIGHTER_OK };
		
		
	public:
		int err_code() const;
		int err_sqlite_code() const;
		gstr err_str() const;
		gstr err_slighter_message() const;
		gstr err_sqlite_message() const;
		gstr err_query() const;
		
		
	public: // Internals
		inline void set_err(const sqlighter::SQLighterException& e) { m_e = e; }
		inline void set_err(sqlighter::SQLighterException&& e) { m_e = std::move(e); }
	};
}


#endif