# SQLUpdate

**Extends:** [SQLCommand](SQLCommand.md)

`SQLUpdate` is a class representing a SQL UPDATE statement builder. It provides a fluent interface for constructing UPDATE queries in a type-safe manner.

## Methods

### `update(): bool`
**Description**: Executes the constructed UPDATE statement against the database.

**Return**: `false` if the query failed to execute; otherwise `true`. To get more information about the error, see the [SQLErrors](Objects/SQLErrors.md) object available through the parent [SQLNode](SQLNode.md)'s `errors()` method.

**Example**:
```gdscript
# Update player's health
if sql_node.update().table("player_stats").set("health", 100).by_field("player_id", current_player_id).update():
    print("Player health updated successfully")
else:
    var error_info = sql_node.errors().last_err()
    print("Failed to update player health: " + error_info.error())
```

### `table(table: String): SQLUpdate`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `table`   | String   | The table to update records in |

**Description**: Specifies the table to update records in.

**Return**: The `SQLUpdate` instance for method chaining.

**Example**:
```gdscript
sql_node.update().table("player_inventory")
```

### `table_in(scheme: String, table: String): SQLUpdate`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `scheme`  | String   | The schema name                |
| `table`   | String   | The table to update records in |

**Description**: Specifies the schema and table to update records in.

**Return**: The `SQLUpdate` instance for method chaining.

**Example**:
```gdscript
sql_node.update().table_in("save_data", "player_stats")
```

### `as(alias: String): SQLUpdate`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `alias`   | String   | Alias for the table            |

**Description**: Specifies an alias for the table being updated.

**Return**: The `SQLUpdate` instance for method chaining.

**Example**:
```gdscript
sql_node.update().table("inventory_items").as("inv")
```

## Available Clauses

`SQLUpdate` supports the following clauses that can be used for constructing an UPDATE statement:

- [Or Clause](Clauses/OrClause.md) - Specify conflict resolution behavior
- [Set Clause](Clauses/SetClause.md) - Specify columns and values to update
- [Where Clause](Clauses/WhereClause.md) - Add conditions to filter which rows to update

## Complete Example

```gdscript
# Begin transaction
sql_node.begin()

# Update player's stats after level up
var update_result = sql_node.update()
    .table("player_stats")
    .set("level", current_level + 1)
    .set("max_health", max_health + 10)
    .set("max_mana", max_mana + 5)
    .set_exp("skill_points = skill_points + ?", [skill_points_gained])
    .by_field("player_id", current_player_id)
    .update()

if update_result:
    print("Player stats updated for level up!")
    # Update last_level_up timestamp
    sql_node.update()
        .table("player_meta")
        .set_exp("last_level_up = datetime('now')", [])
        .by_field("player_id", current_player_id)
        .update()
    
    # Commit transaction
    sql_node.commit()
else:
    var error_info = sql_node.errors().last_err()
    print("Failed to update player stats: " + error_info.error())
    # Rollback transaction
    sql_node.rollback()
```