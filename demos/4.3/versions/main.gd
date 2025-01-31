extends Control


func _ready() -> void:
	print("SQLite       : " + GLighter.sqlite_version())
	print("SQLighter    : " + GLighter.sqlighter_version())
	print("GodotLighter : " + GLighter.library_version())
	
	$CenterContainer/HBoxContainer/Values/SQLite_value.text			= GLighter.sqlite_version()
	$CenterContainer/HBoxContainer/Values/SQLighter_value.text		= GLighter.sqlighter_version()
	$CenterContainer/HBoxContainer/Values/GodotLighter_value.text	= GLighter.library_version()
