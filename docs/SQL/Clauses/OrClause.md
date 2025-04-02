# Or Clause

The Or Clause is used in `INSERT` and `UPDATE` SQL commands to specify conflict resolution behavior when an operation conflicts with existing data.

## Supported Commands

The Or Clause is available in the following SQL command builders:

- [SQLInsert](../SQLInsert.md)
- [SQLUpdate](../SQLUpdate.md)

## Methods

### `or_abort(): Self`
**Description**: Specifies that the operation should abort with an error if a conflict occurs.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Insert a new item, abort if ID already exists
sql_node.insert()
    .into("inventory_items")
    .or_abort()
    .columns(["id", "name", "type"])
    .record([new_item_id, item_name, item_type])
```

---

### `or_fail(): Self`
**Description**: Specifies that the operation should fail silently without making changes if a conflict occurs.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Update player stats, fail silently if player doesn't exist
sql_node.update()
    .table("player_stats")
    .or_fail()
    .set("health", new_health_value)
    .by_field("player_id", player_id)
```

---

### `or_replace(): Self`
**Description**: Specifies that the operation should replace the existing record if a conflict occurs.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Insert or replace a player's high score
sql_node.insert()
    .into("high_scores")
    .or_replace()
    .columns(["player_id", "level_id", "score"])
    .record([player_id, level_id, new_score])
```

---

### `or_ignore(): Self`
**Description**: Specifies that the operation should ignore conflicts and proceed without making changes to the conflicting row.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Insert quest progress only if it doesn't already exist
sql_node.insert()
    .into("quest_progress")
    .or_ignore()
    .columns(["player_id", "quest_id", "progress"])
    .record([player_id, quest_id, 0])
```

---

### `or_rollback(): Self`
**Description**: Specifies that the operation should roll back the entire transaction if a conflict occurs.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Begin transaction
sql_node.begin()

# Try to insert multiple items, rollback if any conflict
sql_node.insert()
    .into("inventory_items")
    .or_rollback()
    .columns(["id", "player_id", "item_id", "quantity"])
    .record([item_record_id_1, player_id, new_item_id_1, 1])

# Attempt to insert another item
sql_node.insert()
    .into("inventory_items")
    .or_rollback()
    .columns(["id", "player_id", "item_id", "quantity"])
    .record([item_record_id_2, player_id, new_item_id_2, 1])

# Commit transaction
sql_node.commit()
```

