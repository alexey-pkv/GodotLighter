# `SQLSelect`

**Extends:** [`SQLCommand`](SQLCommand.md)

The `SQLSelect` class provides a fluent interface for constructing SQL `SELECT` statements. This class offers a type-safe and expressive way to build complex `SELECT` queries.

## Available Clauses

`SQLSelect` supports the following clauses for constructing a `SELECT` statement:

- [From Clause](Clauses/FromClause.md) - Specify the table(s) to select from
- [Where Clause](Clauses/WhereClause.md) - Filter rows based on conditions
- [Order By Clause](Clauses/OrderByClause.md) - Sort result rows
- [Limit Clause](Clauses/LimitClause.md) - Limit the number of returned rows

## Methods

### `distinct(): SQLSelect`
**Description**: Adds the `DISTINCT` keyword to the `SELECT` statement, filtering out duplicate rows.

**Return**: A reference to the current `SQLSelect` object for method chaining.

**Example**:
```gdscript
var query = sql_node.select().distinct().from("users")
print(query.assemble())
# Output: `SELECT` `DISTINCT` * `FROM` users
```

---

### `column(column: String): SQLSelect`

| Parameter | Type   | Description                      |
|-----------|--------|----------------------------------|
| `column`  | String | The name of the column to select. |

**Description**: Adds a specific column to the `SELECT` statement.

**Return**: A reference to the current `SQLSelect` object for method chaining.

**Example**:
```gdscript
var query = sql_node.select()
    .column("name")
    .column("age")
    .from("users")
print(query.assemble())
# Output: `SELECT` name, age `FROM` users
```

---

### `column_as(column: String, as: String): SQLSelect`

| Parameter | Type   | Description                      |
|-----------|--------|----------------------------------|
| `column`  | String | The name of the column to select. |
| `as`      | String | The alias for the column.         |

**Description**: Adds a column with an alias to the `SELECT` statement.

**Return**: A reference to the current `SQLSelect` object for method chaining.

**Example**:
```gdscript
var query = sql_node.select()
    .column_as("count(*)", "total_count")
    .from("users")
print(query.assemble())
# Output: `SELECT` count(*) `AS` total_count `FROM` users
```

---

### `columns(columns: Array): SQLSelect`

| Parameter  | Type   | Description                       |
|------------|--------|-----------------------------------|
| `columns`  | Array  | An array of column names to select. |

**Description**: Adds multiple columns to the `SELECT` statement.

**Return**: A reference to the current `SQLSelect` object for method chaining.

**Example**:
```gdscript
var query = sql_node.select()
    .columns(["name", "age", "email"])
    .from("users")
print(query.assemble())
# Output: `SELECT` name, age, email `FROM` users
```

---

### `column_exp(expression: String, binds: Array): SQLSelect`

| Parameter    | Type   | Description                                          |
|--------------|--------|------------------------------------------------------|
| `expression` | String | A SQL column expression                              |
| `binds`      | Array  | Array of values to bind to parameters in the expression |

**Description**: Adds a column expression with optional parameter binding.

**Return**: A reference to the current `SQLSelect` object for method chaining.

**Example**:
```gdscript
var query = sql_node.select()
    .column_exp("COUNT(*)", [])
    .column_exp("AVG(age) as avg_age", [])
    .from("users")
print(query.assemble())
# Output: `SELECT` COUNT(*), AVG(age) as avg_age `FROM` users
```

### `query_row(): Dictionary`
**Description**: Executes the `SELECT` statement and returns the first row as a dictionary.

**Return**: A dictionary representing the first row, or an empty dictionary if no rows are found.

### `query_row_numeric(): Array`
**Description**: Executes the `SELECT` statement and returns the first row as a numeric array.

**Return**: An array representing the first row, or an empty array if no rows are found.

### `query_all(): Array`
**Description**: Executes the `SELECT` statement and returns all rows as an array of dictionaries.

**Return**: An array of dictionaries representing the result rows.

### `query_column_all(): Array`
**Description**: Executes the `SELECT` statement and returns the first column of all rows.

**Return**: An array containing the values of the first column.

### `query_value(): Variant`
**Description**: Executes the `SELECT` statement and returns the value of the first column in the first row.

**Return**: The value of the first column in the first row, or `null` if no rows are found.

## Complete Example

```gdscript
var users = sql_node.select()
    .columns(["id", "name", "age"])
    .from("users")
    .where("age > ?", [18])
    .order_by_field_desc("age")
    .limit_by(10)
    .query_all()

for user in users:
    print("User %d: %s (Age: %d)" % [user["id"], user["name"], user["age"]])
```

## More Complex Example with Joins and Subqueries

```gdscript
var top_active_users = sql_node.select()
    .column_as("u.id", "user_id")
    .column_as("u.name", "username")
    .column_exp("COUNT(p.id) as post_count", [])
    .from("users", "u")
    .join("posts", "p", "u.id = p.user_id", [])
    .where("p.created_at > ?", [last_week])
    .order_by_field_desc("post_count")
    .limit_by(5)
    .query_all()
```