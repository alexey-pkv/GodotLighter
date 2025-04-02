# Error Handling in GodotLighter

The GodotLighter library provides a comprehensive and flexible error handling mechanism that allows developers to gracefully manage and respond to database-related errors.

## Error Objects

### [SQLErrorInfo](../Objects/SQLErrorInfo.md)

[`SQLErrorInfo`](../Objects/SQLErrorInfo.md) is the primary object for error details. It provides methods to access different aspects of an error:

- `code()`: Returns the library-specific error code
- `error()`: Returns the full error message
- `err_additional_message()`: Provides any additional context about the error
- `err_sqlite_code()`: Returns the underlying SQLite error code
- `err_sqlite_str()`: Provides the SQLite-specific error message
- `err_lighter_str()`: Returns a human-readable description of the library-specific error
- `err_query()`: Returns the SQL query that caused the error (if applicable)

### [SQLErrors](../Objects/SQLErrors.md)

[`SQLErrors`](../Objects/SQLErrors.md) manages error tracking and provides several key features:

#### Properties
- `print_errors`: A boolean that controls error printing behavior

#### Methods
- `has_err()`: Checks if an error is present
- `last_err()`: Retrieves the most recent error
- `reset_error()`: Clears the current error state

## Error Handling Strategies

### Global Error Tracking

Every `SQLNode` has an associated `SQLErrors` object that can track errors:

```gdscript
# Connect to the error signal
sql_node.errors().on_error.connect(func(error): 
    print("SQL Error occurred: " + error.error())
)
```

### Error Checking After Operations

Most database operations return a boolean or an `SQLStmt` that can be checked for errors:

```gdscript
# Insert example with error handling
if not sql_node.insert().into("users").columns(["name"]).record(["John"]).insert():
    var error = sql_node.errors().last_err()
    print("Insert failed: " + error.error())
```

### Detailed Error Inspection

```gdscript
var stmt = sql_node.execute_stmt("SELECT * FROM non_existent_table")
if stmt.is_failed():
    var error = stmt.get_err()
    print("Error Code: " + str(error.code()))
    print("SQLite Error: " + error.err_sqlite_str())
    print("Query: " + error.err_query())
```

## Configuring Error Handling

The library provides two levels of error printing:

### Global Error Printing

Global error printing is controlled through `GLighter.errors()`:

```gdscript
# Enable global error printing (true by default)
GLighter.errors().set_print_errors(true)

# Disable global error printing
GLighter.errors().set_print_errors(false)
```

### Node-Specific Error Printing

Each `SQLNode` can have its own error printing configuration:

```gdscript
# By default, node-specific error printing is false
sql_node.errors().set_print_errors(true)
```

### Printing Behavior Notes

- When both global and node-specific `print_errors` are set to `true`, the same error will be printed twice.
- Global printing is on by default, while node-specific printing is off by default.
- This allows for flexible error logging strategies:
  - Global logging for application-wide errors
  - Granular control for specific database nodes

Example of duplicate error printing:
```gdscript
# This will print the error twice
GLighter.errors().set_print_errors(true)
sql_node.errors().set_print_errors(true)

# Database operation that causes an error
sql_node.execute_stmt("invalid query")
```

In this scenario, the error will be printed once by the global error handler and once by the node-specific error handler.