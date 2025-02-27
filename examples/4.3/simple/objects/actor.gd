class_name Actor extends RigidBody2D


#region Consts

const LIFE_OFFSET		: Vector2	= Vector2(-100, -50)
const TAG_NAME_OFFSET	: Vector2	= Vector2(-100, +20)

#endregion


#region Nodes

@onready var life_label		: Label				= $Life
@onready var tag_name_label	: Label				= $NameTag
@onready var body			: ColorRect			= $Body
@onready var dagger_body	: ColorRect			= $Dagger_Body
@onready var dagger			: CollisionShape2D	= $Dagger
@onready var hit_box		: CollisionShape2D	= $Shape

#endregion


#region Properties

@export var acceleration		: float	= 100
@export var ang_acceleration	: float	= PI
@export var target_speed		: float	= 0.0
@export var target_angel_speed	: float	= 0.0

@export var id			: int		= -1
@export var life		: int		= 10
@export var tag_name	: String
@export var actor_color	: Color: 
	get: return actor_color
	set(c):
		actor_color = c
		update_color()

#endregion


#region Methods

func update_color() -> void:
	if !is_inside_tree(): return
	
	body.color			= actor_color
	dagger_body.color	= actor_color.darkened(0.2)

func set_targets(speed_dir: int, ang_speed_dir: int) -> void:
	speed_dir		= clamp(speed_dir, -1, 1)
	ang_speed_dir	= clamp(ang_speed_dir, -1, 1)
	
	target_speed		= speed_dir * GameConfig.SPEED
	target_angel_speed	= ang_speed_dir * GameConfig.ANG_SPEED

func damaged(from: Actor, by: int) -> void:
	life -= by
	
	if life <= 0:
		on_killed.emit(self, from)
		queue_free()

func disable() -> void:
	tag_name_label.visible = false
	life_label.visible = false
	
	set_process(false)
	set_physics_process(false)

#endregion


#region Build In Methods

func _ready() -> void:
	update_color()

func _physics_process(delta: float) -> void:
	var target_velocity = Vector2(target_speed, 0).rotated(rotation)
	
	if target_velocity != linear_velocity:
		var frame_acceleration = acceleration * delta
		var velocity_delta = target_velocity - linear_velocity
		
		if velocity_delta.length() < frame_acceleration:
			linear_velocity = target_velocity
		else:
			linear_velocity += velocity_delta.normalized() * frame_acceleration
		
	if target_angel_speed != angular_velocity:
		var frame_ang_acceleration = ang_acceleration * delta
		var angular_diff = target_angel_speed - angular_velocity
		
		if absf(angular_diff) < frame_ang_acceleration:
			angular_velocity = target_angel_speed
		else:
			if angular_diff < 0:
				angular_velocity -= frame_ang_acceleration
			else:
				angular_velocity += frame_ang_acceleration

func _process(_delta: float) -> void:
	tag_name_label.text	= tag_name
	
	life_label.text = str(life)
	
	if life < 20:
		life_label.set("theme_override_colors/font_color", Color.RED)
	elif life < 50:
		life_label.set("theme_override_colors/font_color", Color.YELLOW)
	else:
		life_label.set("theme_override_colors/font_color", Color.GREEN)
	
	life_label.rotation = -rotation
	life_label.position = LIFE_OFFSET.rotated(-rotation)
	
	tag_name_label.rotation = -rotation
	tag_name_label.position = TAG_NAME_OFFSET.rotated(-rotation)

#endregion


#region Handlers

func handle_body_shape_entered(_body_rid: RID, 
		with: Node, body_shape_index: int, local_shape_index: int) -> void:
	
	if !(with is Actor):
		return
	if shape_owner_get_owner(local_shape_index) != dagger:
		return
	
	var other: Actor = with
	var other_part = other.shape_owner_get_owner(body_shape_index)
	
	if other_part != other.hit_box:
		return
	
	on_hit.emit(self, with)

#endregion


#region Signals

signal on_hit(me: Actor, other: Actor)
signal on_killed(me: Actor, by: Actor)

#endregion
