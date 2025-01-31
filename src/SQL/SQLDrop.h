#ifndef GODOTLIGHTER_SQLDROP_H
#define GODOTLIGHTER_SQLDROP_H


#include "SQLCommand.h"

#include <connectors/CMDDrop.h>


namespace godot
{
	class SQLDrop : public SQLCommand
	{
		AS_GD_CLASS(SQLDrop, SQLCommand);
	private:
		uptr<sqlighter::CMDDrop> m_cmd { nullptr };
		str m_scheme {};
		
		
	private:
		sqlighter::CMD* get_cmd() override;
		const sqlighter::CMD* get_cmd() const override;
		
		
	public:
		Ref<SQLDrop> if_exists();
		Ref<SQLDrop> scheme(const gstr& name);
		Ref<SQLDrop> table(const gstr& name);
		Ref<SQLDrop> view(const gstr& name);
		Ref<SQLDrop> trigger(const gstr& name);
		Ref<SQLDrop> index(const gstr& name);
		
		bool drop();
		
		
	public: // Internals
		inline void init() {};
		void init(sqlighter::CMDDrop&& cmd);
	};
}


#endif