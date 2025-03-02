# Generic Example

A generic example of using the library is available under `examples/4.3/simple`. Also available as a separate archive under releases: https://github.com/alexey-pkv/GodotLighter/releases.

In this example, multiple bots are spawned in a small arena. The bots attempt to hit each other with their triangular front shape to eliminate opponents. Eliminating a bot grants 1 kill, while the eliminated bot receives 1 death.

SQLite is used to manage the score table for the bots. You can sort the table by name, kills, or deaths in either ascending or descending order.

It should be noted that SQLite is not necessarily the best approach for solving this problem. However, this serves merely as an example of how to use the library.

## Key Files and Classes

| File                                             | Notes                                                                                                                                                                                                                                   |
|--------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `sql/actor_dao.gd`                               | A class responsible for managing access to the `Actor` table. This demonstrates a pattern where each table has a corresponding class, and any queries related to this table should be placed within this class.                         |
| `sql/init` directory and `sql/init/db_init.tscn` | This directory contains an example of using migration scripts to initialize the database on startup. The `db_init.tscn` scene is used as a configuration for this migration and is attached to the `SQLNode` in the main scene.         |

## Extra

In the `main.md` file, you can modify the `_ready` method to enable user control of the first and second bots:

```gdscript
func _ready() -> void:
	# Uncomment and modify to enable player control:
	m_players = 0
	# m_players = 1	# Arrows
	# m_players = 2	# WASD
```
