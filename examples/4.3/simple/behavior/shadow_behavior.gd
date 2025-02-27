class_name ShadowBehavior extends AbstractBehavior


#region Properties

@export var source: Actor = null:
	get: return source
	set(a):
		source = a
		
		if a != null:
			a.tree_exiting.connect(func() -> void: 
				if a == source:
					source = null)

#endregion


#region Private Methods

func _update_actor() -> void:
	if actor == null:
		return
		
	if source == null:
		actor.visible = false
		return
	
	actor.visible		= true
	actor.actor_color	= source.actor_color
	actor.tag_name		= source.tag_name
	actor.rotation		= source.rotation

#endregion


#region Methods

func init_actor() -> void:
	super.init_actor()
	
	actor.disable()
	
	_update_actor()

#endregion


#region Built In

func _ready() -> void:
	super._ready()
	
	process_mode = PROCESS_MODE_ALWAYS

func _process(_delta: float) -> void:
	_update_actor()

#endregion
