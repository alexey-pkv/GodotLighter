# Order By Clause

The Order By Clause is used in various SQL commands to sort the results of a query.

## Supported Commands

The Order By Clause is available in the following SQL command builders:

- [SQLSelect](../SQLSelect.md)
- [SQLDelete](../SQLDelete.md)

## Methods

### `order_by_exp(exp: String, binds: Array): Self`
| Parameter | Type     | Description                                          |
|-----------|----------|------------------------------------------------------|
| `exp`     | String   | The ORDER BY expression                              |
| `binds`   | Array    | Array of values to bind to parameters in expression  |

**Description**: Adds an ORDER BY clause to the query.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select enemies ordered by a calculated threat level
sql_node.select()
    .from("enemies")
    .order_by_exp("CASE WHEN type = ? THEN 1 ELSE 2 END", ["boss"])
```

---

### `order_by_field(field: String, asc: bool): Self`
| Parameter | Type     | Description                                          |
|-----------|----------|------------------------------------------------------|
| `field`   | String   | The field to order by                                |
| `asc`     | bool     | `true` for ascending, `false` for descending order   |

**Description**: Adds an ORDER BY clause for a specific field with specified direction.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select characters ordered by level (ascending)
sql_node.select()
    .from("characters")
    .order_by_field("level", true)
```

---

### `order_by_field_asc(field: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `field`   | String   | The field to order by          |

**Description**: Adds an ORDER BY clause for a specific field in ascending order.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select items ordered by name (ascending)
sql_node.select()
    .from("inventory_items")
    .order_by_field_asc("item_name")
```

---

### `order_by_field_desc(field: String): Self`
| Parameter | Type     | Description                    |
|-----------|----------|--------------------------------|
| `field`   | String   | The field to order by          |

**Description**: Adds an ORDER BY clause for a specific field in descending order.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select high scores ordered by score (highest first)
sql_node.select()
    .from("high_scores")
    .order_by_field_desc("score")
```
