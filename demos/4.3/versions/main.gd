extends Control


@onready var sql: SQLNode = $SQLNode


func _ready() -> void:
	print("GodotLighter : " + GLighter.library_version())
	print("SQLighter    : " + GLighter.sqlighter_version())
	print("SQLite       : " + GLighter.sqlite_version())
	
	# OR :
	# print(GodotLighter.versions_info())
	
	print(sql.query_all("SELECT 1 UNION SELECT 2", []))
	
	
