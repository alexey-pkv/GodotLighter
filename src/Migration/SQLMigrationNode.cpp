#include "SQLMigrationNode.h"


#include <sstream>
#include <iostream>
#include <chrono>

#include "Utils/helpers.h"

#include "SQLNode.h"
#include "GLighter.h"
#include "SQLMigrationScript.h"


using namespace godot;


const char* SQL_NODE_CLASS_NAME	= "SQLNode";
const char* SCRIPT_CLASS_NAME	= "SQLMigrationScript";

gstr mysql_now()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm tm{};
	
	#ifdef _WIN32
		localtime_s(&tm, &now_c);
	#else
		localtime_r(&now_c, &tm);
	#endif
	
	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
	return gstr { buffer };
}

struct MigrationScriptData
{
public:
	int 				Index	= 0;
	gstr				Path	= "";
	SQLMigrationScript* Script	= nullptr;
	
	
public:
	void update_path(const gstr& original, const gstr& next)
	{
		Path = original + gstr { "/" } + next;
	}
	
	Dictionary to_dictionary() const
	{
		Dictionary d;
		
		d["Path"]	= Path;
		d["Script"]	= Script;
		
		return d;
	}
	
	static std::map<int, MigrationScriptData> to_map(vec<MigrationScriptData>&& all)
	{
		std::map<int, MigrationScriptData> map;
		
		for (auto& s : all)
		{
			map[s.Index] = std::move(s);
		}
		
		return map;
	}
};

struct MigrationLogData
{
public:
	int 	Created	= 0;
	int 	Index	= 0;
	gstr	Path	= "";
	bool	Result	= "";
	gstr	Error	= "";
	
	
public:
	void from_record(const Dictionary& record)
	{
		Created	= record["Created"];
		Index	= record["Index"];
		Path	= record["Path"];
		Result	= record["Result"];
		Error	= record["Error"];
	}
	
	Dictionary to_record() const
	{
		Dictionary record;
		
		record["Created"]	= Created;
		record["Index"]		= Index;
		record["Path"]		= Path;
		record["Result"]	= Result;
		record["Error"]		= Error;
		
		return record;
	}
	
	
public:
	inline static MigrationLogData create_from_record(const Dictionary& record)
	{
		MigrationLogData m;
		m.from_record(record);
		return m;
	}
	
	static vec<MigrationLogData> from_records(const Array& all)
	{
		vec<MigrationLogData> result;
		
		for (int i = 0; i < all.size(); i++)
		{
			result.push_back(MigrationLogData::create_from_record(all[i]));
		}
		
		return result;
	}
	
	static Array to_records(const vec<MigrationLogData>& all)
	{
		Array result;
		
		for (const auto& data : all)
		{
			result.push_back(data.to_record());
		}
		
		return result;
	}
};


int l_get_migration_scripts(Node* root, MigrationScriptData cursor, vec<MigrationScriptData>& into) // NOLINT(*-no-recursion)
{
	auto children = root->get_children();
	auto path = cursor.Path;
	
	for (int i = 0; i < children.size(); i++)
	{
		auto child = (Node*)((Object*)children[i]);
		
		cursor.update_path(path, child->get_name());
		
		if (child->get_class() != SCRIPT_CLASS_NAME)
		{
			cursor.Index = l_get_migration_scripts(child, cursor, into);
		}
		else
		{
			cursor.Script = (SQLMigrationScript*)child;
			into.push_back(cursor);
			cursor.Index++;
		}
	}
	
	return cursor.Index;
}

vec<MigrationScriptData> l_get_migration_scripts(Node* root)
{
	MigrationScriptData cursor;
	vec<MigrationScriptData> data = {};
	
	l_get_migration_scripts(root, cursor, data);
	
	return data;
}

vec<MigrationLogData> l_get_migration_log(SQLNode* sql, const gstr& table, bool withErrors)
{
	auto cmd = sql
		->select()
		->column_as("Created",	"Created")
		->column_as("ID",		"`Index`")
		->column_as("Path",		"Path")
		->column_as("Result",	"Result")
		->column_as("Error",	"Error")
		->from(table);
	
	if (!withErrors)
	{
		cmd->by_field("Result", true);
	}
	
	return MigrationLogData::from_records(cmd->query_all());
}

int l_get_migration_offset(SQLNode* sql, const gstr& table)
{
	Array value = sql
		->select()
		->column("MAX(ID)")
		->column("COUNT(*)")
		->from(table)
		->by_field("Result", true)
		->query_row_numeric();
	
	if ((int)(value[1]) == 0)
		return 0;
	
	return (int)(value[0]) + 1;
}


void SQLMigrationNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_auto_free"),				&SQLMigrationNode::get_auto_free);
	ClassDB::bind_method(D_METHOD("set_auto_free", "value"),	&SQLMigrationNode::set_auto_free);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_free"), "set_auto_free", "get_auto_free");
	
	ClassDB::bind_method(D_METHOD("get_auto_run"),				&SQLMigrationNode::get_auto_run);
	ClassDB::bind_method(D_METHOD("set_auto_run", "value"),		&SQLMigrationNode::set_auto_run);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_run"), "set_auto_run", "get_auto_run");
	
	ClassDB::bind_method(D_METHOD("get_is_one_time"),			&SQLMigrationNode::get_is_one_time);
	ClassDB::bind_method(D_METHOD("set_is_one_time", "value"),	&SQLMigrationNode::set_is_one_time);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_one_time"), "set_is_one_time", "get_is_one_time");
	
	ClassDB::bind_method(D_METHOD("get_migration_table"),			&SQLMigrationNode::get_migration_table);
	ClassDB::bind_method(D_METHOD("set_migration_table", "value"),	&SQLMigrationNode::set_migration_table);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "migration_table"), "set_migration_table", "get_migration_table");
	
	
	ClassDB::bind_method(D_METHOD("execute"),								&SQLMigrationNode::execute);
	
	ClassDB::bind_method(D_METHOD("create_migration_table"),				&SQLMigrationNode::create_migration_table);
	ClassDB::bind_method(D_METHOD("get_migration_scripts_metadata"),		&SQLMigrationNode::get_migration_scripts_metadata);
	ClassDB::bind_method(D_METHOD("is_migration_table_exists"),				&SQLMigrationNode::is_migration_table_exists);
	ClassDB::bind_method(D_METHOD("load_migration_log", "include_errors"),	&SQLMigrationNode::load_migration_log);
	ClassDB::bind_method(D_METHOD("get_desync_issues"),						&SQLMigrationNode::get_desync_issues);
	ClassDB::bind_method(D_METHOD("is_up_to_date"),							&SQLMigrationNode::is_up_to_date);
	
	
	ADD_SIGNAL(MethodInfo("begin_migration"));
	ADD_SIGNAL(MethodInfo("migration_failed"));
	ADD_SIGNAL(MethodInfo("migration_complete"));
	
	{
		auto pathProperty	= PropertyInfo(Variant::STRING, "path");
		auto scriptProperty	= PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_NODE_TYPE, "SQLMigrationScript");
		
		ADD_SIGNAL(MethodInfo("before_script",		pathProperty, scriptProperty));
		ADD_SIGNAL(MethodInfo("script_complete",	pathProperty, scriptProperty));
		ADD_SIGNAL(MethodInfo("script_failed",		pathProperty, scriptProperty));
	}
}


bool SQLMigrationNode::get_auto_free() const { return m_autoFree; }
void SQLMigrationNode::set_auto_free(bool val) { m_autoFree = val; }
bool SQLMigrationNode::get_auto_run() const { return m_autoRun; }
void SQLMigrationNode::set_auto_run(bool val) { m_autoRun = val; }
bool SQLMigrationNode::get_is_one_time() const { return m_isOneTime; }
void SQLMigrationNode::set_is_one_time(bool val) { m_isOneTime = val; }
const gstr& SQLMigrationNode::get_migration_table() const { return m_migrationTable; }
void SQLMigrationNode::set_migration_table(const gstr& to) { m_migrationTable = to; }


PackedStringArray SQLMigrationNode::_get_configuration_warnings() const
{
	PackedStringArray a;
	
	if (!m_isOneTime && m_migrationTable.is_empty())
	{
		a.append("Either 'Is One Time' must be true, or a 'Migration Table' name must be set");
	}
	
	return a;
}

void SQLMigrationNode::_enter_tree()
{
	Node::_enter_tree();
	
	if (!GLighter::is_editor() && m_autoRun)
	{
		execute();
	}
}


void SQLMigrationNode::insert_migration_log(SQLNode* node, int seq, const gstr& name, const gstr& error) const
{
	Array columns = {};
	
	columns.push_back("ID");
	columns.push_back("Created");
	columns.push_back("Path");
	columns.push_back("Result");
	columns.push_back("Error");
	
	Array values = {};
	
	values.push_back(seq);
	values.push_back(mysql_now());
	values.push_back(name);
	values.push_back(error.is_empty());
	values.push_back(error.is_empty() ? Variant { nullptr } : Variant { error });
	
	node
		->insert()
		->into(get_migration_table())
		->columns(columns)
		->record(values)
		->execute();
}

bool SQLMigrationNode::is_migration_table_exists_for(SQLNode* node) const
{
	int count = node->select()
		->column_exp("COUNT(*)", {})
		->from("sqlite_master")
		->by_field("type", "table")
		->by_field("name", get_migration_table())
		->query_value();
	
	return count > 0;
}

bool SQLMigrationNode::run_migration(SQLNode* node, int offset)
{
	auto scripts = l_get_migration_scripts(node);
	
	if (scripts.empty())
	{
		GLighter::generic_error("No migration scripts found");
		return false;
	}
	else if (scripts.size() <= offset)
	{
		return true;
	}
	
	for (int index = offset; index < scripts.size(); index++)
	{
		const auto& script = scripts[index];
		
		
		emit_signal("before_script", script.Path, script.Script);
		
		bool result = script.Script->execute_update_for(node);
		
		if (!m_isOneTime)
		{
			auto lastError = GLighter::errors()->last_err();
			gstr error = "";
			
			if (!result)
			{
				if (lastError != nullptr)
				{
					error = lastError->error();
				}
				else
				{
					error = "Unknown fail reason";
				}
			}
			
			insert_migration_log(node, index, script.Path, error);
		}
		
		if (!result)
		{
			emit_signal("script_failed", script.Path, script.Script);
			return false;
		}
		else
		{
			emit_signal("script_complete", script.Path, script.Script);
		}
	}
	
	return true;
}

SQLNode* SQLMigrationNode::try_get_parent_sql() const
{
	auto node = get_first_parent_by_class(this, SQL_NODE_CLASS_NAME);
	
	if (node == nullptr)
	{
		GLighter::generic_error("No parent SQLNode found in execute");
		return nullptr;
	}
	
	return (SQLNode*)node;
}

bool SQLMigrationNode::validate_db_empty(SQLNode* node) 
{
	int count = node->select()
		->column_exp("COUNT(*)", {})
		->from("sqlite_master")
		->by_field("type", "table")
		->where("name NOT LIKE ?", { { "sqlite_%" } })
		->query_value();
	
	return count == 0 && no_errors();
}

bool SQLMigrationNode::create_migration_table_for(SQLNode* node) const
{
	const auto& table = get_migration_table();
	
	if (table.is_empty())
	{
		GLighter::handle_error({
			SQLIGHTER_ERR_GENERIC,
			"Either 'Is One Time' must be true, or a 'Migration Table' name must be set" 
		});
		
		return false;
	}
	
	if (is_migration_table_exists_for(node))
		return true;
	
	if (!validate_db_empty(node))
		return false;
	
	return node
		->create_table()
		->table(table)
		->column_exp("ID INT NOT NULL")
		->column_exp("Created TEXT NOT NULL")
		->column_exp("Path TEXT NOT NULL")
		->column_exp("Result INTEGER NOT NULL")
		->column_exp("Error TEXT")
		->create();
}

bool SQLMigrationNode::no_errors() 
{
	return !GLighter::errors()->has_err();
}

bool SQLMigrationNode::run_execute_for_node(SQLNode* node)
{
	GLighter::errors()->reset_error();
	
	if (m_isOneTime)
	{
		if (!validate_db_empty(node))
		{
			return false;
		}
		
		return run_migration(node, 0);
	}
	else
	{
		if (!create_migration_table_for(node))
		{
			return false;
		}
		
		if (!get_desync_issues().is_empty())
		{
			GLighter::generic_error(
				"There seems to be desync issues with the migration scripts. "
				"Call 'get_desync_issues()' for more info.");
			
			return false;
		}
		
		return run_migration(node, l_get_migration_offset(node, m_migrationTable));
	}
}

bool SQLMigrationNode::execute()
{
	emit_signal("begin_migration");
	
	auto node = try_get_parent_sql();
	
	if (node == nullptr)
	{
		emit_signal("migration_failed");
		return false;
	}
	
	auto result = run_execute_for_node(node);
	
	if (result)
	{
		emit_signal("migration_complete");
		
		if (m_autoFree)
		{
			this->queue_free();
		}
	}
	else
	{
		emit_signal("migration_failed");
	}
	
	return result;
}

Array SQLMigrationNode::get_migration_scripts_metadata() const
{
	Array result = {};
	
	for (const auto& c : l_get_migration_scripts((Node*)this))
	{
		result.push_back(c.to_dictionary());
	}
	
	return result;
}

Array SQLMigrationNode::load_migration_log(bool includeErrors) const
{
	if (m_isOneTime)
		return {};
	
	auto sql = try_get_parent_sql();
	
	if (sql == nullptr || !is_migration_table_exists_for(sql))
		return {};
	
	return MigrationLogData::to_records(
		l_get_migration_log(
			sql, 
			get_migration_table(),
			includeErrors)
	);
}

bool SQLMigrationNode::is_migration_table_exists() const
{
	if (m_isOneTime)
		return false;
	
	auto sql = try_get_parent_sql();
	
	if (!sql)
		return false;
	
	return is_migration_table_exists_for(sql);
}

bool SQLMigrationNode::create_migration_table() const
{
	auto sql = try_get_parent_sql();
	
	if (!sql)
		return false;
	
	return create_migration_table_for(sql);
}

Array SQLMigrationNode::get_desync_issues() const
{
	Array issues = {};
	
	if (m_isOneTime)
		return {};
	
	auto sql = try_get_parent_sql();
	
	if (!sql)
		return {};
	
	auto logs = l_get_migration_log(sql, get_migration_table(), false);
	auto scripts	= MigrationScriptData::to_map(l_get_migration_scripts(sql));
	
	for (const auto& log : logs)
	{
		auto kvp = scripts.find(log.Index);
		
		if (kvp == scripts.end())
			continue;
		
		if (kvp->second.Path == log.Path)
			continue;
		
		std::stringstream ss;
		
		ss
			<< "At position " << log.Index 
			<< " expected script " << str2str(log.Path) 
			<< " but got " << str2str(kvp->second.Path);  
		
		issues.push_back(str2str(ss.str()));
	}
	
	return issues;
}

bool SQLMigrationNode::is_up_to_date() const
{
	auto sql = try_get_parent_sql();
	
	if (m_isOneTime)
	{
		GLighter::generic_error("Invalid call to is_up_to_date for a one time migration script");
		return false;
	}
	
	if (!sql)
		return false;
	
	GLighter::errors()->reset_error();
	
	auto scripts = l_get_migration_scripts(sql);
	auto index = l_get_migration_offset(sql, get_migration_table());
	
	return no_errors() && index >= scripts.size();
}
