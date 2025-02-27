class_name Arena extends Node2D


#region Nodes

@onready var m_left		: StaticBody2D = $Left
@onready var m_right	: StaticBody2D = $Right
@onready var m_top		: StaticBody2D = $Top
@onready var m_bottom	: StaticBody2D = $Bottom

#endregion


#region Properties

@export var area: Rect2i = Rect2i(0, 0, 100, 100):
	get: return area
	set(r):
		area = r
		set_process(true)

#endregion


#region Methods

func _update() -> void:
	set_process(false)
	
	m_left.position	= Vector2(area.position) + Vector2(0, area.size.y) / 2
	m_top.position	= Vector2(area.position) + Vector2(area.size.x, 0) / 2
	
	m_right.position	= Vector2(area.position + area.size) - Vector2(0, area.size.y) / 2
	m_bottom.position	= Vector2(area.position + area.size) - Vector2(area.size.x, 0) / 2

#endregion


#region Built In

func _ready() -> void:
	_update()

func _process(_delta: float) -> void:
	_update()

#endregion
