# SQLNode

**Extends:** [Node](https://docs.godotengine.org/en/4.3/classes/class_node.html)

This is the primary interface for interacting with the library. `SQLNode` represents a single connection to an SQLite database.

To connect to an existing database or create a new one, attach a new `SQLNode` to your scene tree. The connection is established either when the first command is executed or when the `open()` method is explicitly called.  If the specified database does not exist, the node will attempt to create it.

> When the node is deleted, if a connection is still open, it will be closed and safely disposed of (hopfully).


## Properties

### `db_path: String`

Specifies the path to the database instance. It can be:
* A full path.
* A relative path using `user://...` or `res://...`.
* `:memory:` for an in-memory database.

If modified after the connection is opened, the change will not take effect until the connection is closed and reopened.

---

### `in_memory: bool`

This property is directly linked to `db_path` and is true when `db_path` is set to `:memory:`.

Changing this property will update `db_path` to either `:memory:` or an empty string.


## Methods

### `get_full_path(): String`
**Description**: Returns the absolute path to the database by resolving the `user://` or `res://` prefixes.

---

### `open(): bool`
**Description**: Attempt to open a new database connection. If a connection is already open, this method has no effect.

If the specified database does not exist, a new one will be created.

**Return**: False if the action failed. See `errors()` for more information about the error

---

### `close(): void`
**Description**: Close any open connection. 

---

### `execute(): bool`
**Description**: Executes a query. This is the simplest way to run a query in the library.

**Return**: False if the query failed to execute; otherwise true. To get more information about the error, see `errors()`.

**Example**:

```
if sql.execute("DROP TABLE `Dignity`):
    print("Your Dignity was dropped")
```

---

### `execute_stmt(): SQLStmt`
**Description**: Executes a query and returns an [SQLStmt](Objects/SQLStmt.md) object containing the result.  

**Return**: Always returns an [SQLStmt](Objects/SQLStmt.md) object. Null will never be returned.  
If an error occurs, the returned object will store the error details and have a failed status.

**Example**:

```
var stmt_npcs: SQLStmt = sql.execute_stmt("SELECT * FROM People WHERE Status = ?", ["NPC"])

print("The list of all NPC's: ")
print(stmt_npcs.all())

var stmt: SQLStmt = sqlexecute_stmt("SELECT * FROM Invalid-Query");

print("Is Failed: " + str(stmt.is_error()))

if stmt.has_error_info():
    print("Error info: " + stmt.error_info().error())
```

---

### `errors(): SQLErrors`
**Description**: Returns the [SQLErrors](Objects/SQLErrors.md) container associated with this SQLNode.  

This container stores the most recent error that occurred within the context of this SQLNode.

---

### `begin(): bool`
**Description**: Executes the `BEGIN` SQL query and returns `true` if the query was successful.

---

### `commit(): bool`
**Description**: Executes the `COMMIT` SQL query and returns `true` if the query was successful.

---

### `rollback(): bool`
**Description**: Executes the `ROLLBACK` SQL query and returns `true` if the query was successful.

---

### `reindex(what: String): bool`
**Description**: Run the `REINDEX` command on the `what` element. Returns `true` if the query was successful.

---

### `reindex_in(scheme: String, what: String): bool`
**Description**: Run the `REINDEX` command on the `what` element in the `scheme` scheme. Returns `true` if the query was successful.

---

### `query_row(query: String, binds: Array): Dictionary`  

| Parameter  | Type    | Description                                         |
|------------|--------|------------------------------------------------------|
| `query`    | String | The SQL query to be executed.                        |
| `binds`    | Array  | An array of values to bind to the query parameters.  |

**Description**: Executes a query and returns the first record as a dictionary, where the key is the column name and the value is the selected value.  

> If the query selects more than one row, only the first row is returned.  

> If the query selects no rows at all, an empty dictionary will be returned, and an error is raised.

**Example**:
```
print(sql.query_row("SELECT 1, ? as col_2, ? = '2' as hel", ["Hello", '2']))
```
will output
```
{ "1": 1, "col_2": "Hello", "hel": 1 }
```

--- 

### `query_row_numeric(query: String, binds: Array): Array`

| Parameter  | Type    | Description                                        |
|------------|--------|-----------------------------------------------------|
| `query`    | String | The SQL query to be executed.                       |
| `binds`    | Array  | An array of values to bind to the query parameters. |

**Description**: Similar behaviour to `query_row_numeric` but the returned result is an array contianing the values only. 

**Example:**

```
print(sql.query_row_numeric("SELECT 1, ? as col_2, ? = '2' as hel", ["Hello", '2']))
```
will output
```
[1, "Hello", 1]
```

--- 

### `query_all(query: String, binds: Array): Dictionary`

| Parameter  | Type   | Description                                         |
|------------|--------|-----------------------------------------------------|
| `query`    | String | The SQL query to be executed.                       |
| `binds`    | Array  | An array of values to bind to the query parameters. |

--- 

### `query_column_all(query: String, binds: Array): Array`

| Parameter  | Type   | Description                                         |
|------------|--------|-----------------------------------------------------|
| `query`    | String | The SQL query to be executed.                       |
| `binds`    | Array  | An array of values to bind to the query parameters. |

--- 

### `query_value(query: String, binds: Array): Variant`

| Parameter  | Type   | Description                                         |
|------------|--------|-----------------------------------------------------|
| `query`    | String | The SQL query to be executed.                       |
| `binds`    | Array  | An array of values to bind to the query parameters. |

--- 

### `query_all_max(query: String, binds: Array, failsafe: int): Array`

| Parameter  | Type   | Description                                             |
|------------|--------|---------------------------------------------------------|
| `query`    | String | The SQL query to be executed.                           |
| `binds`    | Array  | An array of values to bind to the query parameters.     |
| `failsafe` | int    | The highest number of records expected to be retrieved. |

--- 

### `query_column_all_max(query: String, binds: Array, failsafe: int): Array`

| Parameter  | Type   | Description                                             |
|------------|--------|---------------------------------------------------------|
| `query`    | String | The SQL query to be executed.                           |
| `binds`    | Array  | An array of values to bind to the query parameters.     |
| `failsafe` | int    | The highest number of records expected to be retrieved. |

--- 

### `count_rows(table_name: String): int`
**Description**: Executes the query `SELECT COUNT(*) FROM {table_name}` and return the result as an integer

--- 

### `direct()`
TODO: 

--- 

### `select()`
TODO: 

--- 

### `insert()`
TODO: 

--- 

### `update()`
TODO: 

--- 

### `delete()`
TODO: 

--- 

### `create_table()`
TODO: 

--- 

### `drop()`
TODO: 

## Signals

### `on_error(error: SQLErrorInfo)`
**Description**: This signal is emitted whenever an error occurs within the context of SQLNode. The signal carries an [SQLErrorInfo](SQLErrorInfo.md) object, which provides details about the error.

> The signal is triggered by the corresponding signal from the attached `SQLErrors` object and acts as its alias. 

