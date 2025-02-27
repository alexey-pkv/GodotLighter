class_name PlayerBehavior extends AbstractBehavior


#region Built In

func _process(_delta: float) -> void:
	if actor == null:
		return
	
	var target_v = 0
	var target_a = 0
	
	if Input.is_action_pressed("ui_down"):	target_v += 1
	if Input.is_action_pressed("ui_up"):	target_v -= 1
	if Input.is_action_pressed("ui_left"):	target_a -= 1
	if Input.is_action_pressed("ui_right"):	target_a += 1
	
	actor.set_targets(target_v, target_a)

#endregion
