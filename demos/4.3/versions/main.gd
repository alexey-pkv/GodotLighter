extends Control


@onready var sql: SQLNode = $SQLNode


func _ready() -> void:
	
	print("GodotLighter : " + GLighter.library_version())
	print("SQLighter    : " + GLighter.sqlighter_version())
	print("SQLite       : " + GLighter.sqlite_version())
	
	var n = SQLSelect.new()
	
	# OR :
	# print(GodotLighter.versions_info())
	
	sql.begin()
	
	print(sql.query_all("SELECT ? as a UNION ALL SELECT ?", [1, "A"]))
	
	
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
