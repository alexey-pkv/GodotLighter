# SQLDelete

**Extends:** [SQLCommand](SQLCommand.md)

`SQLDelete` is a class representing a SQL DELETE statement builder. It provides a fluent interface for constructing DELETE queries in a type-safe manner.

## Methods

### `del(): bool`
**Description**: Executes the constructed DELETE statement against the database.

**Return**: `false` if the query failed to execute; otherwise `true`. To get more information about the error, see the [SQLErrors](Objects/SQLErrors.md) object available through the parent [SQLNode](SQLNode.md)'s `errors()` method.

**Example**:
```gdscript
# Delete all completed quests from the player's quest log
if sql_node.delete().from("player_quests").by_field("status", "completed").del():
    print("Completed quests cleared from log")
else:
    print("Failed to clear completed quests")
```

## Available Clauses

`SQLDelete` supports the following clauses that can be used for constructing a DELETE statement:

- [From Clause](Clauses/FromClause.md) - Specify the table to delete from
- [Where Clause](Clauses/WhereClause.md) - Add conditions to filter which rows to delete
- [Order By Clause](Clauses/OrderByClause.md) - Specify the order in which rows are deleted
- [Limit Clause](Clauses/LimitClause.md) - Limit the number of rows deleted

## Complete Example

```gdscript
# Delete the 10 oldest items in the player's inventory
var delete_result = sql_node.delete()
    .from("player_inventory")
    .by_field("player_id", current_player_id)
    .order_by_field("acquire_date", true)  # true for ascending (oldest first)
    .limit_by(10)
    .del()

if delete_result:
    print("Successfully removed oldest items from inventory")
else:
    var error_info = sql_node.errors().last_err()
    print("Failed to clean inventory: " + error_info.error())
```