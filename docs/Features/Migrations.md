# Database Initialization and Migrations

One of the key features of the GodotLighter library is the [`SQLMigrationNode`](../SQLMigrationNode.md), 
which is responsible for database initialization and smooth migration to newer versions.

There are two node types used in the migration process:  

- `SQLMigrationScript` contains a single migration script used to update the database.  
- [`SQLMigrationNode`](../SQLMigrationNode.md) manages the migration process itself.  

When the `execute()` method of `SQLMigrationNode` is called, the node searches for any child or grandchild
`SQLMigrationScript` nodes and attempts to run them one after another in order.  

The `SQLMigrationScript` must have a script with the `_update(node: SQLNode)` method implemented. This is the method
that will be called by `SQLMigrationNode` to initialize or update the database. 

```
extends SQLMigrationScript

func _update(node: SQLNode) -> void:
	var create = node.create_table()
	
	create.table("NPCs")
	create.column_exp("FirstName TEXT")
	create.column_exp("LastName TEXT")
	create.column_exp("Age INTEGER")
	create.create()
```

## One-time database setup

Used to set up the database once, ideal for cases where you don't need to persist the database between
runs (e.g., an in-memory database used only during runtime).

To achieve this behaviour, simple create a `SQLMigrationNode` with the property 
[`is_one_time`](../SQLMigrationNode.md#is_one_time-bool) set to `true`.

## Database with a migration log
This option allows the node to maintain a migration log table within the database, ensuring that only scripts that 
haven't been run yet are executed.

Useful when you need to maintain the database between game runs and automatically upgrade it 
when a new version of the game is launched. For example, if you release a game with a specific database structure
and later need to modify it (e.g., by adding a new column), loading an old save in the new version may cause 
issues due to the structure mismatch. To handle this, you'd add a migration script that only adds the 
necessary changes, such as the new column. When loading an old save, the game will automatically update 
the database by running only the new migration script. For new saves, all scripts will run in order, ensuring 
the database structure is consistent across both new and migrated saves.

The exact behaviour of the node depends on the value of the [`is_one_time`](../SQLMigrationNode.md#is_one_time-bool)
property.

To achieve this behaviour, create a `SQLMigrationNode` with the property 
[`is_one_time`](../SQLMigrationNode.md#is_one_time-bool) set to `false`. When executed, a migration table
will be created. The name of the table is defined by the 
[`migration_table`](../SQLMigrationNode.md#migration_table-string) property.

