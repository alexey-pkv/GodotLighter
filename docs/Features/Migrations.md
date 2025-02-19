# Database Initialization and Migrations  

One of the key features of the GodotLighter library is the 
[`SQLMigrationNode`](../Migration/SQLMigrationNode.md), which handles database initialization 
and ensures seamless migration to newer versions.  

There are two node types involved in the migration process:  

- [`SQLMigrationScript`](../Migration/SQLMigrationNode.md): Represents a single migration script used to update the database.  
- [`SQLMigrationNode`](../Migration/SQLMigrationNode.md): Manages the overall migration process.  

## Initialization vs. Migrations  

GodotLighter provides two ways to utilize migration functionality, determined by the value of 
the [`is_one_time`](../SQLMigrationNode.md#is_one_time-bool) property:  

1. **One-time database setup (`is_one_time = true`)**  
   - Used to set up a database once, typically for cases where persistence is unnecessary (e.g., an in-memory database used only during runtime).  
   - `SQLMigrationNode` expects a new, empty database each time it runs, so no migration log table is created.  


2. **Database with a migration log (`is_one_time = false`)**  
   - Allows `SQLMigrationNode` to be executed multiple times on the same database.  
   - Maintains a migration log table to track which `SQLMigrationScript` nodes have already been executed, ensuring that only pending migrations run.  
   - Example use case: for preserving the database between game runs and automatically applying updates when a new game version is released, keeping older save files compatible.  

The chosen functionality and how migrations are handled depend on the `is_one_time` property, making it a key factor in determining whether the database operates as a temporary instance or a persistent, version-controlled system.

## Setting Up