# SQLDrop

**Extends:** [SQLCommand](SQLCommand.md)

`SQLDrop` is a wrapper for SQLite's DROP command, allowing you to remove database objects like tables, views, triggers, and indexes.

## Methods

### `if_exists(): SQLDrop`
**Description**: Adds the `IF EXISTS` clause to the DROP command. This prevents errors when trying to drop objects that don't exist.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop a table only if it exists
$SQLNode.drop().if_exists().table("old_table").drop()
```

---

### `scheme(name: String): SQLDrop`

| Parameter | Type   | Description              |
|-----------|--------|--------------------------|
| `name`    | String | The schema name to use.  |

**Description**: Specifies the schema name to operate within.

**Return**: Returns the `SQLDrop` object for method chaining.

---

### `table(name: String): SQLDrop`

| Parameter | Type   | Description                                                   |
|-----------|--------|---------------------------------------------------------------|
| `name`    | String | The table name. Can include schema (e.g., "schema.table").    |

**Description**: Specifies a table to drop.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop a table
$SQLNode.drop().table("users").drop()
```

---

### `view(name: String): SQLDrop`

| Parameter | Type   | Description                                               |
|-----------|--------|-----------------------------------------------------------|
| `name`    | String | The view name. Can include schema (e.g., "schema.view").  |

**Description**: Specifies a view to drop.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop a view
$SQLNode.drop().view("active_users").drop()
```

---

### `trigger(name: String): SQLDrop`

| Parameter | Type   | Description                                                       |
|-----------|--------|-------------------------------------------------------------------|
| `name`    | String | The trigger name. Can include schema (e.g., "schema.trigger").    |

**Description**: Specifies a trigger to drop.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop a trigger
$SQLNode.drop().trigger("after_insert_user").drop()
```

---

### `index(name: String): SQLDrop`

| Parameter | Type   | Description                                                    |
|-----------|--------|----------------------------------------------------------------|
| `name`    | String | The index name. Can include schema (e.g., "schema.index").     |

**Description**: Specifies an index to drop.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop an index
$SQLNode.drop().index("idx_user_email").drop()
```

---

### `table_in(scheme: String, name: String): SQLDrop`

| Parameter | Type   | Description        |
|-----------| -------|-------------------|
| `scheme`  | String | The schema name.   |
| `name`    | String | The table name.    |

**Description**: Specifies a table to drop in a particular schema.

**Return**: Returns the `SQLDrop` object for method chaining.

**Example**:
```gdscript
# Drop a table in a specific schema
$SQLNode.drop().table_in("main", "users").drop()
```

---

### `view_in(scheme: String, name: String): SQLDrop`

| Parameter | Type   | Description        |
|-----------| -------|-------------------|
| `scheme`  | String | The schema name.   |
| `name`    | String | The view name.     |

**Description**: Specifies a view to drop in a particular schema.

**Return**: Returns the `SQLDrop` object for method chaining.

---

### `trigger_in(scheme: String, name: String): SQLDrop`

| Parameter | Type   | Description        |
|-----------| -------|-------------------|
| `scheme`  | String | The schema name.   |
| `name`    | String | The trigger name.  |

**Description**: Specifies a trigger to drop in a particular schema.

**Return**: Returns the `SQLDrop` object for method chaining.

---

### `index_in(scheme: String, name: String): SQLDrop`

| Parameter | Type   | Description        |
|-----------| -------|-------------------|
| `scheme`  | String | The schema name.   |
| `name`    | String | The index name.    |

**Description**: Specifies an index to drop in a particular schema.

**Return**: Returns the `SQLDrop` object for method chaining.

---

### `drop(): bool`
**Description**: Executes the DROP command.

**Return**: Returns `true` if the execution was successful; otherwise `false`.

**Example**:
```gdscript
# Complete example of dropping a table with error handling
var sql = $SQLNode
if sql.drop().if_exists().table("users").drop():
    print("Table dropped successfully")
else:
    var error = sql.errors().last_err()
    print("Failed to drop table: " + error.error())
```

## Complete Examples

### Dropping a Table
```gdscript
# Drop a table if it exists
$SQLNode.drop().if_exists().table("users").drop()
```

### Dropping Multiple Objects During Database Cleanup
```gdscript
func cleanup_database():
    var sql = $SQLNode
    
    # Drop tables
    sql.drop().if_exists().table("users").drop()
    sql.drop().if_exists().table("posts").drop()
    
    # Drop views
    sql.drop().if_exists().view("active_users").drop()
    
    # Drop indexes
    sql.drop().if_exists().index("idx_user_email").drop()
    
    # Drop triggers
    sql.drop().if_exists().trigger("after_insert_user").drop()
```

### Dropping Objects in a Specific Schema
```gdscript
# Drop a table in the temp schema
$SQLNode.drop().table_in("temp", "cache_data").drop()

# Alternative syntax
$SQLNode.drop().scheme("temp").table("cache_data").drop()
```