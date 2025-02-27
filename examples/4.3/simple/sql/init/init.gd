extends SQLMigrationScript


func _update(node: SQLNode) -> void:
	node.execute(
		"CREATE TABLE Actor
		(
			ID INTEGER PRIMARY KEY,
			Name TEXT NOT NULL,
			Color TEXT,
			Kills INTEGER,
			Death INTEGER,
			IsDead BOOLEAN
		)",
		[])
		
	node.execute("CREATE INDEX idx_actor_kills ON Actor(Kills)", [])
	node.execute("CREATE INDEX idx_actor_death ON Actor(Death)", [])
	node.execute("CREATE INDEX idx_actor_name ON Actor(Name)", [])
