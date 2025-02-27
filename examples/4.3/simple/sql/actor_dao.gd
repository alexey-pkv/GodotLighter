class_name ActorDAO extends RefCounted


#region Data Members

var m_sql: SQLNode	= null;

#endregion


#region Built In

func _init(node: SQLNode) -> void:
	m_sql = node

#endregion


#region Methods

func load_all_ids() -> Array:
	return m_sql.query_column_all(
		"SELECT ID FROM Actor",
		[]
	)

func load_all(order_by: String, asc: bool) -> Array:
	var select = m_sql.select()
	
	select.from("Actor")
	select.order_by_field(order_by, asc)
	select.order_by_field_asc("ID")
	
	return select.query_all()

func load_by_id(id: int) -> Dictionary:
	var select = m_sql.select()
	
	select.from("Actor")
	select.by_field("ID", id)
	
	return select.query_row()

func save_is_dead(id: int, is_dead: bool) -> void:
	var update = m_sql.update()
	
	update.table("Actor")
	update.by_field("ID", id)
	update.set("IsDead", is_dead)
	
	update.execute()

func update_score(killed_actor_id: int, killer_actor_id: int) -> void:
	m_sql.execute(
		"UPDATE Actor SET Death = Death + 1 WHERE ID = ?", 
		[killed_actor_id])
		
	m_sql.update() \
		.table("Actor") \
		.set_exp("Kills = Kills + 1", []) \
		.by_field("ID", killer_actor_id) \
		.execute()

#endregion
