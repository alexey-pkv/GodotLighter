extends Control


@onready var sql: SQLNode = $SQLNode


func handle(e: SQLErrorInfo) -> void:
	print(e.err_code())


func _ready() -> void:
	
	print("GodotLighter : " + GLighter.library_version())
	print("SQLighter    : " + GLighter.sqlighter_version())
	print("SQLite       : " + GLighter.sqlite_version())
	
	print(sql.begin())
	
	print(sql.query_all("SELECT ? as a UNION ALL SELECT ?", [1, "A"]))
	
	print(sql.query_all("INVALID QUERY", [1, "A"]))
	
	
	var cmd = sql.direct(); 
	
	var stmt = cmd \
		.append("SELECT ", []) \
		.append("? as a, ? as b", [1, 2]) \
		.execute()
		
	
	print(stmt.all())
	
	var create = sql.create_table()
	
	create.table("MyTable")
	create.if_not_exists()
	create.column_exp("`ID` INTEGER PRIMARY KEY")
	create.column_exp("`name` TEXT NOT NULL")
	
	print(create.create())
	print(sql.select().from("a").assemble());


func _on_sql_node_on_error(error: SQLErrorInfo) -> void:
	print(error.err_code())
