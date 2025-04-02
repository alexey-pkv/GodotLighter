# SQLDirect

**Extends:** [SQLCommand](SQLCommand.md)

`SQLDirect` is a class that allows for executing direct SQL queries. It's a low-level interface that gives you more control over the SQL statement compared to the specialized query builders like `SQLSelect` or `SQLInsert`.

This class is particularly useful for executing complex or specialized SQL statements that don't fit well into the structured API provided by the other SQL builders.

## Methods

### `append(query_string: String, binds: Array): SQLDirect`

| Parameter      | Type   | Description                                       |
|----------------|--------|---------------------------------------------------|
| `query_string` | String | The raw SQL statement or fragment to be appended  |
| `binds`        | Array  | Array of values to bind to the query parameters   |

**Description**: Appends a SQL fragment to the current query, along with any bind parameters.

**Return**: The `SQLDirect` instance for method chaining.

**Example**:

```gdscript
var sql = $SQLNode

# Simple query with no parameters
sql.direct()
   .append("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)", [])
   .execute()

# Query with bound parameters
sql.direct()
   .append("INSERT INTO users (name, age) VALUES (?, ?)", ["Alice", 30])
   .execute()

# Building complex queries in parts
var query = sql.direct()
query.append("SELECT * FROM users", [])
query.append(" WHERE age > ?", [25])
query.append(" AND name LIKE ?", ["%A%"])
var result = query.execute()
```

## Usage Notes

1. `SQLDirect` is useful when you need to execute SQL commands that aren't easily represented by the specialized query builders.

2. SQL fragments are concatenated directly, so be careful about spaces between fragments to avoid syntax errors.

3. The query is only sent to the database when `execute()` is called.

4. Parameter placeholders (`?`) in the query are replaced by the corresponding values in the `binds` array, in order.

5. The bind parameters help prevent SQL injection attacks by ensuring values are properly escaped.

```gdscript
# Wrong way (vulnerable to SQL injection):
sql.direct()
   .append("SELECT * FROM users WHERE name = '" + user_input + "'", [])
   .execute()

# Correct way (using parameter binding):
sql.direct()
   .append("SELECT * FROM users WHERE name = ?", [user_input])
   .execute()
```

6. Complex queries can be built incrementally:

```gdscript
var query = sql.direct()
query.append("SELECT * FROM products", [])

if filter_by_category:
    query.append(" WHERE category = ?", [category])
    
if sort_by_price:
    query.append(" ORDER BY price", [])
    
if limit > 0:
    query.append(" LIMIT ?", [limit])
    
var result = query.execute()
```