# SQLInsert

**Extends:** [SQLCommand](SQLCommand.md)

`SQLInsert` is a class representing a SQL INSERT statement builder. It provides a fluent interface for constructing INSERT queries in a type-safe manner.

## Methods

### `insert(): bool`
**Description**: Executes the constructed INSERT statement against the database.

**Return**: `false` if the query failed to execute; otherwise `true`. To get more information about the error, see the [SQLErrors](Objects/SQLErrors.md) object available through the parent [SQLNode](SQLNode.md)'s `errors()` method.

**Example**:
```gdscript
# Insert a new item into the player's inventory
if sql_node.insert().into("player_inventory").columns(["player_id", "item_id", "quantity"]).record([player_id, item_id, 1]).insert():
    print("Item added to inventory successfully")
else:
    var error_info = sql_node.errors().last_err()
    print("Failed to add item to inventory: " + error_info.error())
```

### `into(table: String): SQLInsert`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `table`   | String   | The table to insert into       |

**Description**: Specifies the table to insert records into.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
sql_node.insert().into("game_saves")
```

### `into_scheme(scheme: String, table: String): SQLInsert`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `scheme`  | String   | The schema name                |
| `table`   | String   | The table to insert into       |

**Description**: Specifies the schema and table to insert records into.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
sql_node.insert().into_scheme("save_data", "player_stats")
```

### `as(alias: String): SQLInsert`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `alias`   | String   | Alias for the table            |

**Description**: Specifies an alias for the table being inserted into.

**Return**: The `SQLInsert` instance for method chaining.

### `column(name: String): SQLInsert`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `name`    | String   | Column name to insert into     |

**Description**: Adds a column to the list of columns for the INSERT statement.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
sql_node.insert()
    .into("game_scores")
    .column("player_id")
    .column("level_id")
    .column("score")
```

### `columns(names: Array): SQLInsert`
| Parameter | Type     | Description                             |
|-----------|----------|-----------------------------------------|
| `names`   | Array    | Array of column names to insert into    |

**Description**: Adds multiple columns to the list of columns for the INSERT statement.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
sql_node.insert()
    .into("player_inventory")
    .columns(["player_id", "item_id", "quantity", "equipped"])
```

### `record(values: Array): SQLInsert`
| Parameter | Type     | Description                              |
|-----------|----------|------------------------------------------|
| `values`  | Array    | Values to insert for a single record     |

**Description**: Adds a record (row) to be inserted. Values should match the order of columns specified.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
sql_node.insert()
    .into("player_inventory")
    .columns(["player_id", "item_id", "quantity"])
    .record([current_player_id, new_item_id, 1])
```

### `records(values_set: Array): SQLInsert`
| Parameter    | Type     | Description                                  |
|--------------|----------|----------------------------------------------|
| `values_set` | Array    | Array of arrays, each representing a record  |

**Description**: Adds multiple records (rows) to be inserted. Each inner array represents one record and should match the order of columns specified.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
# Insert multiple quest rewards
var rewards = [
    [player_id, "quest_1", "gold", 100],
    [player_id, "quest_1", "exp", 500],
    [player_id, "quest_1", "item_123", 1]
]

sql_node.insert()
    .into("quest_rewards")
    .columns(["player_id", "quest_id", "reward_type", "reward_amount"])
    .records(rewards)
```

### `default_values(): SQLInsert`
**Description**: Specifies that the INSERT should use default values for all columns.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
# Create a new player record with all default values
sql_node.insert()
    .into("players")
    .default_values()
```

### `on_conflict_do_nothing(): SQLInsert`
**Description**: Specifies that the INSERT should do nothing if a conflict occurs.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
# Insert an achievement only if it doesn't already exist
sql_node.insert()
    .into("player_achievements")
    .columns(["player_id", "achievement_id", "unlocked_date"])
    .record([player_id, achievement_id, current_date])
    .on_conflict_do_nothing()
```

### `on_conflict(column: String): SQLInsert`
| Parameter | Type     | Description                              |
|-----------|----------|------------------------------------------|
| `column`  | String   | Column to check for conflict             |

**Description**: Specifies the column(s) that may have a conflict. This is used together with the [Set Clause](Clauses/SetClause.md) to update existing rows when a conflict occurs.

**Return**: The `SQLInsert` instance for method chaining.

**Example**:
```gdscript
# Insert or update high score if player already has one for this level
sql_node.insert()
    .into("high_scores")
    .columns(["player_id", "level_id", "score", "completion_time"])
    .record([player_id, level_id, new_score, completion_time])
    .on_conflict("player_id")  # Conflict on player_id
    .set("score", new_score)   # Update only the score if conflict occurs
    .set("completion_time", completion_time)
```

## Available Clauses

`SQLInsert` supports the following clauses that can be used for constructing an INSERT statement:

- [Or Clause](Clauses/OrClause.md) - Specify conflict resolution behavior
- [Set Clause](Clauses/SetClause.md) - Used with ON CONFLICT to specify updates for existing rows

## Complete Example

```gdscript
# Begin transaction
sql_node.begin()

# Insert a new player character
var new_character_id = 1001  # Generated ID for new character
var insert_result = sql_node.insert()
    .into("characters")
    .columns(["id", "player_id", "name", "class", "level", "experience", "creation_date"])
    .record([
        new_character_id, 
        current_player_id, 
        character_name, 
        character_class, 
        1,  # Starting level 
        0,  # Starting XP
        "datetime('now')"
    ])
    .insert()

if insert_result:
    print("New character created!")
    
    # Insert starting inventory items
    var starting_items = [
        [new_character_id, "item_sword", 1, true],  # Equipped sword
        [new_character_id, "item_potion", 5, false] # 5 potions
    ]
    
    sql_node.insert()
        .into("character_inventory")
        .columns(["character_id", "item_id", "quantity", "equipped"])
        .records(starting_items)
        .insert()
    
    # Insert starting stats
    sql_node.insert()
        .into("character_stats")
        .columns(["character_id", "strength", "dexterity", "intelligence", "health", "mana"])
        .record([new_character_id, 10, 10, 10, 100, 50])
        .insert()
    
    # Commit the transaction
    sql_node.commit()
else:
    var error_info = sql_node.errors().last_err()
    print("Failed to create character: " + error_info.error())
    # Rollback the transaction
    sql_node.rollback()
```