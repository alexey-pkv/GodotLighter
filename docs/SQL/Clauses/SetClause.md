# Set Clause

The Set Clause is used in SQL UPDATE commands to specify which columns should be updated and their new values.

## Supported Commands

The Set Clause is available in the following SQL command builders:

- [SQLUpdate](../SQLUpdate.md)
- [SQLInsert](../SQLInsert.md)

## Methods

### `set(field: String, value: Variant): Self`
| Parameter | Type     | Description                       |
|-----------|----------|-----------------------------------|
| `field`   | String   | The field/column to update        |
| `value`   | Variant  | The new value to set for the field|

**Description**: Sets a field to a specific value in the UPDATE statement.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Update player's health and mana
sql_node.update()
    .table("player_stats")
    .set("health", 100)
    .set("mana", 50)
    .by_field("player_id", current_player_id)
```

---

### `set_exp(expression: String, binds: Array): Self`
| Parameter    | Type     | Description                                          |
|--------------|----------|------------------------------------------------------|
| `expression` | String   | The SET expression                                   |
| `binds`      | Array    | Array of values to bind to parameters in expression  |

**Description**: Sets a field using a custom expression, which may include parameters.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Increment player's experience points
sql_node.update()
    .table("player_stats")
    .set_exp("experience = experience + ?", [earned_xp])
    .by_field("player_id", current_player_id)

# Update multiple fields with a single expression
sql_node.update()
    .table("game_state")
    .set_exp("last_save = datetime('now'), play_time = play_time + ?", [session_time])
    .by_field("save_slot", current_slot)
```
