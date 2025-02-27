extends Control


@onready var actor: Actor = $Actor


func _ready() -> void:
	pass

func _process(delta: float) -> void:
	var target_v = 0.0
	var target_a = 0.0
	
	if Input.is_action_pressed("ui_down"):	target_v += 1.0
	if Input.is_action_pressed("ui_up"):	target_v -= 1.0
	if Input.is_action_pressed("ui_left"):	target_a -= 1.0
	if Input.is_action_pressed("ui_right"):	target_a += 1.0
	
	if Input.is_action_just_pressed("ui_accept"):
		actor.apply_force(Vector2(10000, 0))
		
	
	actor.target_speed			= target_v * 150.0
	actor.target_angel_speed	= 2.0 * PI * target_a
