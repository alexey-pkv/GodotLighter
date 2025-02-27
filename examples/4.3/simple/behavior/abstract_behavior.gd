class_name AbstractBehavior extends Node


#region Properties

@export var actor: Actor = null:
	get: return actor
	set(a): 
		actor = a
		
		if is_inside_tree():
			init_actor.call_deferred()

#endregion


#region Private Methods

func init_actor() -> void:
	actor.target_speed			= 0.0
	actor.target_angel_speed	= 0

#endregion


#region Built In

func _ready() -> void:
	if actor == null and get_parent() is Actor:
		actor = get_parent()
		
	if actor != null:
		init_actor.call_deferred()

#endregion
