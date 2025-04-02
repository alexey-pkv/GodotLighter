# SQLCommand

**Extends:** [RefCounted](https://docs.godotengine.org/en/4.3/classes/class_refcounted.html)

`SQLCommand` is an abstract base class for SQL command builders in the GodotLighter library. It provides common functionality shared by all SQL command types such as `SELECT`, `INSERT`, `UPDATE`, `DELETE`, `CREATE`, and `DROP`.

This class is not meant to be instantiated directly but serves as the parent class for specific SQL command implementations.

## Methods

### `assemble(): String`

**Description**: Returns the assembled SQL query string that would be executed by the command. Useful for debugging queries before execution.

**Return**: The SQL query string.

**Example**:
```gdscript
# Print the assembled SQL query for debugging
var select = $SQLNode.select().from("users").where("age > ?", [18])
print(select.assemble())  # Outputs: SELECT * FROM users WHERE age > ?
```

---

### `binds(): Array`

**Description**: Returns an array containing the bind values that would be used when executing the query. Useful for debugging parameter bindings.

**Return**: An array of values to be bound to the query parameters.

**Example**:
```gdscript
# Check the bind values for debugging
var select = $SQLNode.select().from("users").where("age > ?", [18])
print(select.binds())     # Outputs: [18]
```

---

### `execute(): SQLStmt`

**Description**: Executes the SQL command and returns a statement object with the results.

**Return**: An [SQLStmt](../Objects/SQLStmt.md) object representing the executed statement.

**Example**:
```gdscript
# Execute a SELECT query and process the statement
var stmt = $SQLNode.select().from("users").where("age > ?", [18]).execute()

# Check if the statement executed successfully
if !stmt.is_failed():
    # Process the results
    var results = stmt.all()
    print("Found %d users" % results.size())
else:
    print("Query failed: %s" % stmt.get_err().error())
```