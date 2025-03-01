extends Control


#region Scenes

const ActorScene = preload("res://objects/actor.tscn")

#endregion


#region Consts

const ARROW_DOWN	= "↓"
const ARROW_UP		= "↑"

#endregion


#region Data Members

var m_rnd						= RandomNumberGenerator.new()
var m_respawn_queue	: Array		= []
var m_actor_dao		: ActorDAO	= null
var m_order_asc		: bool		= true
var m_order_by		: String	= "Kills"
var m_players		: int		= 1

#endregion


#region Nodes

@onready var m_field	: BattleField	= $cont/BattleField
@onready var m_table	: ScoreTable	= $cont/mar/sec/ScoreTable

#endregion


#region Private Methods

func _place(behavior: AbstractBehavior = null) -> Actor:
	var actor = ActorScene.instantiate()
	
	actor.on_hit.connect(handle_actor_hit)
	actor.on_killed.connect(handle_killed)
	
	actor.position = Vector2(m_rnd.randf_range(20, 480), m_rnd.randf_range(20, 480))
	actor.rotation = m_rnd.randf_range(0, 2.0 * PI)
	
	if behavior != null:
		actor.add_child(behavior)
		
	m_field.add_child(actor)
	
	return actor

func _place_bot(id: int, tag_name: String, color: Color) -> void:
	var actor = _place(AIBehavior.new())
	
	actor.id			= id
	actor.actor_color	= color
	actor.tag_name		= tag_name
	
func _place_player(id: int, tag_name: String, color: Color) -> PlayerBehavior:
	var behavior	= PlayerBehavior.new()
	var actor		= _place(behavior)
	
	actor.id			= id
	actor.actor_color	= color
	actor.tag_name		= tag_name
	
	return behavior

func _spawn_actor(id: int) -> void:
	m_actor_dao.save_is_dead(id, false)
	
	var data = m_actor_dao.load_by_id(id)
	
	if id <= m_players:
		var behaviour = _place_player(data["ID"], data["Name"], Color.html(data["Color"]))
	
		# 1 player uses arrows, second WASD
		behaviour.is_arrows = (id == 1)
	else:
		_place_bot(data["ID"], data["Name"], Color.html(data["Color"]))
	
	_update_table()

func _wait_for_db() -> void:
	var startTime = Time.get_ticks_msec()
	var after = 0
	
	print("Using SQLite lib Versions: ")
	print(GLighter.versions_info())
	
	var migration: SQLMigrationNode = $SQLNode/DBInit
	
	if !(await migration.migration_complete):
		push_error("Failed to initialize the database. Exiting...")
		get_tree().quit()
	
	m_actor_dao = ActorDAO.new($SQLNode)
	
	after = Time.get_ticks_msec() - startTime
	print("SQL setup complete after " + str(after) + " ms")

func _update_table() -> void:
	var startTime = Time.get_ticks_usec()
	var all = m_actor_dao.load_all(m_order_by, m_order_asc)
	var loadTime = Time.get_ticks_usec() - startTime
	
	m_table.update(all, m_field.get_children())
	
	# Uncomment to get time readings
	# print(
	#	"Table update took " + str(Time.get_ticks_usec() - startTime) +
	#	" usec (" + str(loadTime) + " usec load time)")

#endregion


#region Build In Methods

func _ready() -> void:
	# Uncomment and modify to enable player control:
	m_players = 0
	# m_players = 1	# Arrows
	# m_players = 2	# AWSD
	
	var startTime : int = Time.get_ticks_msec()
	
	randomize()
	GLighter.errors().on_error.connect(handle_sql_error)
	
	await _wait_for_db()
	
	for id in m_actor_dao.load_all_ids():
		m_respawn_queue.push_back([id, Time.get_ticks_msec()])
	
	_update_table()
	
	print("Ready after " + str(Time.get_ticks_msec() - startTime) + " ms")

func _process(_delta: float) -> void:
	if m_respawn_queue.is_empty():
		return
	
	var now = Time.get_ticks_msec()
	
	if m_respawn_queue[0][1] > now:
		return
	
	_spawn_actor(m_respawn_queue.pop_front()[0])

#endregion


#region Handlers

func handle_actor_hit(offender: Actor, victim: Actor) -> void:
	var at = offender.dagger.global_position - victim.global_position
	var force_normal = offender.linear_velocity.normalized()
	
	victim.apply_force(force_normal * GameConfig.DAGGER_FORCE, at.normalized())
	offender.apply_force(force_normal * GameConfig.DAGGER_BACK_FORCE, Vector2.ZERO)
	
	victim.damaged(
		offender, 
		m_rnd.randi_range(
			GameConfig.DAMAGE_MIN, 
			GameConfig.DAMAGE_MAX
		))

func handle_killed(who: Actor, by: Actor) -> void:
	print(by.tag_name + " killed " + who.tag_name)
	
	m_actor_dao.save_is_dead(who.id, true)
	m_actor_dao.update_score(who.id, by.id)
	
	m_respawn_queue.push_back([
		who.id, 
		Time.get_ticks_msec() + GameConfig.RESPAWN_AFTER
	])
	
	_update_table()

func handle_sql_error(error: SQLErrorInfo) -> void:
	push_error("Failed in SQLite: ")
	push_error(error.error())

func handle_opt_order_item_selected(index: int) -> void:
	m_order_by = $cont/mar/sec/mar/sec/opt_order.get_item_text(index)
	_update_table()

func handle_btn_order_pressed() -> void:
	m_order_asc = !m_order_asc
	
	var arrow = ARROW_DOWN if m_order_asc else ARROW_UP
	
	$cont/mar/sec/mar/sec/btn_order.text = arrow
	
	_update_table()

#endregion
