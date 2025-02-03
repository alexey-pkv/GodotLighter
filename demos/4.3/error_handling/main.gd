extends Control


@onready var sql: SQLNode  = $SQLNode


func handle_sql_error(error: SQLErrorInfo) -> void:
	print("Error in SQLNode: ")
	print(error.error())

func handle_run_commands_pressed() -> void:
	print("Running an incorrect SQL query")
	
	var stmt: SQLStmt = sql \
		.select() \
		.from("NotATable") \
		.execute()
	
	print("The list of all NPC's: ")
	print(stmt.all())
	
	print("Let's check if sqlite3 error code indicates that the query field")
	print("Is Failed: " + str(stmt.is_error()))
	
	print("Let's check if the statment contains an error information:")
	
	if stmt.has_error_info():
		print("Error info: " + stmt.error_info().error())
	
	print("We can reset the error by calling reset_error on the SQLErrors object")
	sql.errors().reset_error()
	print("Now, sql.errors().has_err() = " + str(sql.errors().has_err()))
