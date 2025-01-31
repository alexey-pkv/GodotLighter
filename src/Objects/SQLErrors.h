#ifndef GODOTLIGHTER_SQLERRORS_H
#define GODOTLIGHTER_SQLERRORS_H


#include "Utils/gd_class.h"
#include "Objects/SQLErrorInfo.h"

#include <godot_cpp/classes/ref_counted.hpp>


namespace godot
{
	class SQLErrors : public RefCounted
	{
		AS_GD_CLASS(SQLErrors, RefCounted);
	private:
		Ref<SQLErrorInfo> m_e { nullptr };
		
		bool m_printErrors			{ true };
		bool m_propagateToGlobal	{ false };
		
		
	public:
		bool has_err() const;
		Ref<SQLErrorInfo> last_err() const;
		void reset_error();
		bool get_print_errors() const;
		void set_print_errors(bool to);
		
		
	public: // Internals
		inline void propagate_to_global() { m_propagateToGlobal = true; }
		
		void handle_error_only(const excp& e);
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
	};
}


#endif