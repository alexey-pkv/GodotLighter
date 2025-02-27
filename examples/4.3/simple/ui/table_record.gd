class_name TableRecord extends HBoxContainer


#region Nodes

@onready var m_actor	: Actor				= $container_shadow/Actor
@onready var m_shadow	: ShadowBehavior	= $container_shadow/Actor/ShadowBehavior
@onready var m_death	: Label				= $container_death/lbl_death
@onready var m_kills	: Label				= $container_kills/lbl_kills
@onready var m_name		: Label				= $container_name/_mrg/lbl_name

#endregion


#region Properties

var actor_id: int = -1:
	get: return actor_id
	set(id): actor_id = id

#endregion


#region Methods

func update(actor_name: String, kills: int, death: int) -> void:
	m_name.text		= actor_name
	m_kills.text	= str(kills)
	m_death.text	= str(death)

func spawned(actor: Actor) -> void:
	m_shadow.source = actor
	actor_id = actor.id

func as_title() -> void:
	m_actor.queue_free()
	
	m_name.text		= "Name"
	m_kills.text	= "Kills"
	m_death.text	= "Death"

#endregion
