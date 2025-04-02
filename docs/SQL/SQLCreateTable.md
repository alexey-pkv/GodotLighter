# SQLCreateTable

**Extends:** [`SQLCommand`](SQLCommand.md)

The `SQLCreateTable` class provides a fluent interface for constructing SQL `CREATE TABLE` statements. This class helps with defining table schemas, including column definitions and table constraints.

## Methods

### `temp(): SQLCreateTable`
**Description**: Specifies that a temporary table should be created (adds the `TEMP` keyword to the SQL statement).

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table().temp().table("temp_data")
print(query.assemble())
# Output:
# CREATE TEMP TABLE temp_data (
# 
# )
```

---

### `if_not_exists(): SQLCreateTable`
**Description**: Adds the `IF NOT EXISTS` modifier to the statement, ensuring that the table will only be created if it doesn't already exist.

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table().if_not_exists().table("players")
print(query.assemble())
# Output:
# CREATE TABLE IF NOT EXISTS players (
# 
# )
```

---

### `table(name: String): SQLCreateTable`

| Parameter | Type   | Description                      |
|-----------|--------|----------------------------------|
| `name`    | String | The name of the table to create. |

**Description**: Sets the name of the table to be created. If the name includes a dot (e.g., `"scheme.table"`), it will be interpreted as a table in a specific schema.

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table().table("players")
print(query.assemble())
# Output:
# CREATE TABLE players (
# 
# )

# With schema in name
var query2 = sql_node.create_table().table("game_data.players")
print(query2.assemble())
# Output:
# CREATE TABLE game_data.players (
# 
# )
```

---

### `table_in(scheme: String, name: String): SQLCreateTable`

| Parameter | Type   | Description                            |
|-----------|--------|----------------------------------------|
| `scheme`  | String | The name of the schema or database.    |
| `name`    | String | The name of the table within the schema. |

**Description**: Sets the name of the table to be created within a specific schema.

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table().table_in("game_data", "players")
print(query.assemble())
# Output:
# CREATE TABLE game_data.players (
# 
# )
```

---

### `column_exp(expression: String): SQLCreateTable`

| Parameter    | Type   | Description                        |
|--------------|--------|------------------------------------|
| `expression` | String | The SQL column definition statement. |

**Description**: Adds a column definition to the table. The `expression` should be a valid SQL column definition string.

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table().table("players")
    .column_exp("id INTEGER PRIMARY KEY")
    .column_exp("name TEXT NOT NULL")
    .column_exp("score INTEGER DEFAULT 0")
print(query.assemble())
# Output:
# CREATE TABLE players (
#   id INTEGER PRIMARY KEY,
#   name TEXT NOT NULL,
#   score INTEGER DEFAULT 0
# )
```

---

### `without_rowid(): SQLCreateTable`
**Description**: Adds the `WITHOUT ROWID` modifier to the table, which prevents `SQLite` from creating the implicit rowid column.

**Return**: A reference to the current `SQLCreateTable` object for method chaining.

**Example**:
```gdscript
var query = sql_node.create_table()
    .table("players")
    .column_exp("id INTEGER PRIMARY KEY")
    .column_exp("name TEXT NOT NULL")
    .without_rowid()
print(query.assemble())
# Output:
# CREATE TABLE players (
#   id INTEGER PRIMARY KEY,
#   name TEXT NOT NULL
# ) WITHOUT ROWID
```

---

### `strict(): SQLCreateTable`
**Description**: Adds the `STRICT` modifier to the table definition, which enforces strict typing on the table columns.

**Return**: A reference to the current SQLCreateTable object for method chaining.

**Example**:
```gdscript
var table = sql_node.create_table()
    .table("players")
    .column_exp("id INTEGER PRIMARY KEY")
    .column_exp("name TEXT NOT NULL")
    .strict()
```

---

### `create(): bool`
**Description**: Executes the `CREATE TABLE` statement.

**Return**: `true` if the table was created successfully, `false` otherwise.

**Example**:
```gdscript
var query = sql_node.create_table()
    .table("players")
    .column_exp("id INTEGER PRIMARY KEY")
    .column_exp("name TEXT NOT NULL")
    .column_exp("score INTEGER DEFAULT 0")

# First examine the SQL to be executed
print(query.assemble())
# Output:
# CREATE TABLE players (
#   id INTEGER PRIMARY KEY,
#   name TEXT NOT NULL,
#   score INTEGER DEFAULT 0
# )

# Then execute it
if query.create():
    print("Table created successfully")
else:
    print("Failed to create table")
```

### All Options Combined

```gdscript
var query = sql_node.create_table()
    .temp()
    .if_not_exists()
    .table("temp_players")
    .column_exp("id INTEGER PRIMARY KEY")
    .column_exp("name TEXT NOT NULL")
    .column_exp("score INTEGER DEFAULT 0")
    .column_exp("last_login DATETIME")
    .strict()
    .without_rowid()

print(query.assemble())
# Output:
# CREATE TEMP TABLE IF NOT EXISTS temp_players (
#   id INTEGER PRIMARY KEY,
#   name TEXT NOT NULL,
#   score INTEGER DEFAULT 0,
#   last_login DATETIME
# ) WITHOUT ROWID, STRICT

if query.create():
    print("Temporary table created successfully")
```