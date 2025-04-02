# Where Clause

The Where Clause is used in various SQL commands to filter rows based on specified conditions.

## Supported Commands

The Where Clause is available in the following SQL command builders:

- [SQLSelect](../SQLSelect.md)
- [SQLDelete](../SQLDelete.md)
- [SQLUpdate](../SQLUpdate.md)

## Methods

### `where(expression: String, binds: Array): Self`
| Parameter    | Type     | Description                                          |
|--------------|----------|------------------------------------------------------|
| `expression` | String   | The WHERE condition expression                       |
| `binds`      | Array    | Array of values to bind to parameters in expression  |

**Description**: Adds a WHERE clause to the query. Multiple calls to `where()` will be combined with AND.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select characters with level greater than 30 and class is 'warrior'
sql_node.select()
    .from("characters")
    .where("level > ?", [30])
    .where("class = ?", ["warrior"])
```

---

### `where_null(column: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `column`  | String   | Column to check for NULL       |

**Description**: Adds a WHERE clause checking if the specified column is NULL.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select items with no enchantment
sql_node.select()
    .from("inventory_items")
    .where_null("enchantment_id")
```

---

### `where_not_null(column: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `column`  | String   | Column to check for NOT NULL   |

**Description**: Adds a WHERE clause checking if the specified column is NOT NULL.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select items with enchantment
sql_node.select()
    .from("inventory_items")
    .where_not_null("enchantment_id")
```

---

### `by_field(column: String, value: Variant): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `column`  | String   | Column name                    |
| `value`   | Variant  | Value to compare against       |

**Description**: Adds a WHERE clause checking if the specified column equals the provided value.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select quest with ID 123
sql_node.select()
    .from("quests")
    .by_field("id", 123)
```

