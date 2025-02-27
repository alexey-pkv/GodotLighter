class_name GameConfig


#region Consts

const SPEED				: float	= 150.0
const ANG_SPEED			: float	= PI * 2.0
const DAGGER_FORCE		: float	= 5000.0
const DAGGER_BACK_FORCE	: float	= -5000.0
const DAMAGE_MIN		: int	= 2
const DAMAGE_MAX		: int	= 20
const RESPAWN_AFTER		: int	= 3000

#endregion

#region Built In

func _ready() -> void:
	push_error("Static class. Do not initialize")

#endregion
