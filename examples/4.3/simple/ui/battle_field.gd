class_name BattleField extends Control


#region Nodes

@onready var m_arena: Arena		= $Arena

#endregion


#region Built In

func _ready() -> void:
	m_arena.area = Rect2(Vector2.ZERO, size)

#endregion
