extends SQLMigrationScript


func _update(node: SQLNode) -> void:
	var cmd = node.insert()
	
	cmd.into("Actor")
	cmd.columns(["ID", "Name", "Color", "Kills", "Death", "IsDead"])
	
	cmd.record([1, "Bobby Bobinsons",	Color.RED.to_html(),		 0, 0, 1]);
	cmd.record([2, "Ricky Rickman",		Color.GREEN.to_html(),		 0, 0, 1]);
	cmd.record([3, "Danny Danielsons",	Color.WHITE.to_html(),		 0, 0, 1]);
	cmd.record([4, "Timmy McTimmy",		Color.BLUE_VIOLET.to_html(), 0, 0, 1]);
	cmd.record([5, "Billy Billington",	Color.BLUE.to_html(),		 0, 0, 1]);
	cmd.record([6, "Girry Grimberg",	Color.DARK_ORANGE.to_html(), 0, 0, 1]);
	cmd.record([7, "Jhony McBerry",		Color.VIOLET.to_html(),		 0, 0, 1]);
	cmd.record([8, "Flonz Flodinger",	Color.CORNSILK.to_html(),	 0, 0, 1]);
	
	cmd.execute()
