#ifndef GODOTLIGHTER_SQLERRORINFO_H
#define GODOTLIGHTER_SQLERRORINFO_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "exceptions/sqlighter_exceptions.h"

#include <godot_cpp/classes/ref_counted.hpp>


namespace godot
{
	class SQLErrorInfo : public RefCounted
	{
		AS_GD_CLASS(SQLErrorInfo, RefCounted);
	private:
		sqlighter::SQLighterException m_e { SQLIGHTER_OK };
		
		
	public:
		gstr error() const;
		int code() const;
		
		gstr err_additional_message() const;
		gstr err_lighter_str() const;
		int err_sqlite_code() const;
		gstr err_sqlite_str() const;
		gstr err_query() const;
		
		
	public: // Internals
		inline void set_err(const sqlighter::SQLighterException& e) { m_e = e; }
		inline void set_err(sqlighter::SQLighterException&& e) { m_e = std::move(e); }
	};
}


#endif