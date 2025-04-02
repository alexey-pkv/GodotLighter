# From Clause

The From Clause is used in various SQL commands to specify the table(s) from which to retrieve, update, or delete data.

## Supported Commands

The From Clause is available in the following SQL command builders:

- [SQLSelect](../SQLSelect.md)
- [SQLDelete](../SQLDelete.md)

## Methods

### `from(table: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `table`   | String   | The table to operate on        |

**Description**: Specifies the table to operate on.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# SELECT query
sql_node.select().from("game_levels")

# DELETE query
sql_node.delete().from("enemy_spawns")
```

---

### `from_a(table: String, alias: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `table`   | String   | The table to operate on        |
| `alias`   | String   | Alias for the table            |

**Description**: Specifies the table to operate on with an alias.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# SELECT query with alias
sql_node.select().from_a("player_characters", "pc").where("pc.level > ?", [10])
```

---

### `from_scheme(scheme: String, table: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `scheme`  | String   | The schema name                |
| `table`   | String   | The table to operate on        |

**Description**: Specifies the schema and table to operate on.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# SELECT query with schema
sql_node.select().from_scheme("save_data", "character_stats")
```

---

### `from_scheme_a(scheme: String, table: String, alias: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `scheme`  | String   | The schema name                |
| `table`   | String   | The table to operate on        |
| `alias`   | String   | Alias for the table            |

**Description**: Specifies the schema and table to operate on with an alias.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# SELECT query with schema and alias
sql_node.select().from_scheme_a("save_data", "player_achievements", "ach").where("ach.unlocked = ?", [true])
```

