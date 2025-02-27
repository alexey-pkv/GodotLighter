class_name ScoreTable extends Control


#region Scenes

const SCENE_TableRecord = preload("res://ui/table_record.tscn")

#endregion 


#region Nodes

@onready var m_records	: Node			= $records
@onready var m_title	: TableRecord	= $TableRecord

#endregion


#region Private Methods

func _map_actors(actors: Array) -> Dictionary:
	var dict = {}
	
	for actor in actors:
		if actor is Actor:
			dict[actor.id] = actor
	
	return dict

func _adjust_children_count(to_count: int) -> void:
	var current_count = m_records.get_child_count()
	
	while current_count > to_count:
		m_records.get_child(current_count - 1).queue_free()
		current_count -= 1
	
	while current_count < to_count:
		current_count += 1
		m_records.add_child(SCENE_TableRecord.instantiate())

#endregion


#region Built In

func _ready() -> void:
	m_title.as_title()

#endregion


#region Methods

func update(data: Array, actors: Array) -> void:
	var actor_map = _map_actors(actors)
	
	_adjust_children_count(len(data))
	
	var records = m_records.get_children()
	
	for i in len(records):
		var record: TableRecord = records[i]
		var item = data[i]
		
		record.actor_id = item["ID"]
		
		if record.actor_id in actor_map:
			record.spawned(actor_map[record.actor_id])
		
		record.update(item["Name"], item["Kills"], item["Death"])

func spawned(actor: Actor) -> void:
	for child: TableRecord in m_records.get_children():
		if child.actor_id == actor.id:
			child.spawned(actor)
			return

#endregion
