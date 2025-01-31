#ifndef GODOTLIGHTER_SQLCOMMAND_H
#define GODOTLIGHTER_SQLCOMMAND_H


#include "Utils/types.h"
#include "Utils/gd_class.h"
#include "Objects/SQLStmt.h"
#include "Objects/SQLErrors.h"

#include <connectors/CMDDirect.h>


namespace godot
{
	class SQLCommand : public RefCounted
	{
		AS_GD_CLASS(SQLCommand, RefCounted);
	private:
		Ref<SQLErrors>	m_errors { nullptr };
		
		
	private:
		virtual sqlighter::CMD* get_cmd() = 0;
		virtual const sqlighter::CMD* get_cmd() const = 0;
		
		
	protected:
		inline void init_errors(const Ref<SQLErrors>& errors) { m_errors = errors; }
		
		
	public:
		gstr assemble() const;
		Array binds() const;
		Ref<SQLStmt> execute();
		
		
	public: // Internal
		void handle_error(const excp& e);
		
		template <typename F>
		void try_action(F&& action) noexcept
		{
			try
			{
				action();
			}
			catch (const excp& e)
			{
				handle_error(e);
			}
		}
		
		template <typename F>
		bool try_action_bool(F&& action) noexcept
		{
			try
			{
				action();
				return true;
			}
			catch (const excp& e)
			{
				handle_error(e);
				return false;
			}
		}
		
		template <typename F, typename DT>
		DT try_action(F&& action, DT default_value) noexcept
		{
			try
			{
				return action();
			}
			catch (const excp& e)
			{
				handle_error(e);
				return default_value;
			}
		}
		
		template <typename F>
		auto try_stmt_action(F&& action) noexcept
		{
			try
			{
				return SQLStmt::from_stmt(m_errors, action());
			}
			catch (const excp& e)
			{
				handle_error(e);
				return SQLStmt::from_error(m_errors, e);
			}
		}
	};
}


#endif