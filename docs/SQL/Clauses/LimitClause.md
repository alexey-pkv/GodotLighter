# Limit Clause

The Limit Clause is used in various SQL commands to limit the number of rows returned or affected.

## Supported Commands

The Limit Clause is available in the following SQL command builders:

- [SQLSelect](../SQLSelect.md)
- [SQLDelete](../SQLDelete.md)

## Methods

### `limit_by(count: int): Self`
| Parameter | Type     | Description                              |
|-----------|----------|------------------------------------------|
| `count`   | int      | Maximum number of rows to return/affect  |

**Description**: Limits the number of rows to return or affect.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select top 10 high scores
sql_node.select()
    .from("high_scores")
    .order_by_field_desc("score")
    .limit_by(10)
```

---

### `limit(offset: int, count: int): Self`
| Parameter | Type     | Description                              |
|-----------|----------|------------------------------------------|
| `offset`  | int      | Number of rows to skip                   |
| `count`   | int      | Maximum number of rows to return/affect  |

**Description**: Limits the number of rows to return or affect with an offset.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select 10 enemies, starting from the 21st enemy
sql_node.select()
    .from("enemies")
    .limit(20, 10)
```

---

### `page(page: int, page_size: int): Self`
| Parameter   | Type     | Description                    |
|-------------|----------|--------------------------------|
| `page`      | int      | The page number (0-based)      |
| `page_size` | int      | Number of rows per page        |

**Description**: Limits the query to a specific page of results. This is a convenience method that calculates the appropriate `LIMIT` clause based on page number and size.

**Return**: The command instance for method chaining.

**Example**:
```gdscript
# Select the third page of quests with 15 quests per page
sql_node.select()
    .from("quests")
    .page(2, 15)  # Page is 0-based, so 2 is the third page
```
