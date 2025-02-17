# Database Initialization and Migrations

One of the key features of the GodotLighter library is the [`SQLMigrationNode`](../SQLMigrationNode.md), 
which is responsible for database initialization and smooth migration to newer versions.

There are two main ways to use the migration node:

* **One-time database setup**: Use the node to set up the database once, ideal for cases where you
don’t need to persist the database between runs (e.g., an in-memory database used only during runtime).

* **Database with a migration log**: This option allows the node to maintain a migration log table 
within the database, ensuring that only scripts that haven’t been run yet are executed.

The second option is useful when you need to maintain the database between game runs and automatically upgrade it 
when a new version of the game is launched. For example, if you release a game with a specific database structure
and later need to modify it (e.g., by adding a new column), loading an old save in the new version may cause 
issues due to the structure mismatch. To handle this, you’d add a migration script that only adds the 
necessary changes, such as the new column. When loading an old save, the game will automatically update 
the database by running only the new migration script. For new saves, all scripts will run in order, ensuring 
the database structure is consistent across both new and migrated saves.

The exact behaviour of the node depends on the value of the [`is_one_time`](../SQLMigrationNode.md#is_one_time-bool)
property.

## One-Time setup