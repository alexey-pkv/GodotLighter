class_name AIBehavior extends AbstractBehavior


#region Consts

const TARGETING_ANGLE_TOLERANCE		= 0.05

#endregion


#region Data Members

var m_target: Actor = null

#endregion


#region Private Methods

func _find_target() -> bool:
	var field = actor.get_parent()
	
	if field == null:
		return false
	
	var targets = field.get_children()
	
	targets.shuffle()
	
	for child in targets:
		if !(child is Actor) or child == actor:
			continue
		
		m_target = child
		break
	
	return m_target != null

func _get_or_aquire_target() -> Actor:
	if m_target == null:
		if !_find_target():
			return null
		
		m_target.tree_exiting.connect(func() -> void: m_target = null)
	
	return m_target

#endregion


#region Built In

func _process(_delta: float) -> void:
	var target = _get_or_aquire_target()
	
	if target == null:
		actor.set_targets(1, 1)
		return
	
	var target_a = 0
	var target_v = 0
	
	var v_to_target		= actor.position.direction_to(target.position)
	var v_my_direction	= Vector2(1, 0).rotated(actor.rotation)
	var v_my_normal		= v_my_direction.rotated(-PI / 2.0)
	
	if v_my_direction.dot(v_to_target) > 0.0:
		target_v = +1
	else:
		target_v = -1
	
	if v_my_normal.dot(v_to_target) < 0.0:
		target_a = -1
	else:
		target_a = +1
	
	actor.set_targets(target_v, target_a)

#endregion
