# SQLMigrationNode

**Extends:** [Node](https://docs.godotengine.org/en/4.3/classes/class_node.html)

`SQLMigrationNode` manages the migration process against the SQLite database. 

## Properties

### `auto_free: bool`

If true, when a migration is complete successfully, the `SQLMigrationNode` will free itself automatically by calling `queue_free()`. 

If a migration process fails, the node will not be freed automatically, even if this property is set to true.

---

### `auto_run: bool`

If set to true, the migration process will be executed as soon as this node enters the tree. In other words, the `execute()` method will be called when the `_enter_tree` signal is triggered. 

It's useful to use this flag with the `auto_free` especially for in-memory databases, ensuring a valid state when the parent SQLNode is mounted.

---

### `is_one_time: bool`

A one-tme migration node is designed to only initialize the database once, and not update an existing database. 
Therefore, if this setting is `true`, the node will only run on an empty database and, it will not create migration tables. 

This setting is useful for in-memory databases that will never be upgraded.  

---

### `migration_table: String`

The name of the migration table used to keep track of what script nodes were executed. Irrelevant if `is_one_time` is set to `true`.

> You should not change this value for an existing database. Doing so will prevent any future migrations from running successfully. 

**Default Value**: `_glighter_migration_`  


## Methods

### `execute(): bool`
**Description**: Runs the migration scripts attached to this node. 

**Return**: `true` if the migration executed without errors. If all migrations have already been applied, this method also returns `true`.

---

### `create_migration_table(): bool`
**Description**: Only creates the migration table if it does not already exist. `execute()` will invoke this method
when called, so you don't need to call this method manually. 

A migration table will only be created in an empty database. For this reason, if the `execute()` method is called for
the first time on a database that is **not** empty, the migration script will fail while trying to create the 
migration table. 

**Return**: `true` if the table was created successfully or already exists. 

---

### `get_migration_scripts_metadata(): Array`
**Description**: Returns information about the migration scripts attached to this node.

**Returns**: Each record in the array is a dictionary with the following keys:

| Name     | Description                                                                                                   |
|----------|---------------------------------------------------------------------------------------------------------------|
| `Path`   | The relative path to the script from the migration node, used to uniquely identify migrations in future runs. |
| `Script` | A reference to the script node itself.                                                                        |

**Example**:
```
[
  {
    "Path": "/InitDB",
    "Script": [Wrapped:0]
  },
  {
    "Path": "/Statistics/RuntimeTable",
    "Script": [Wrapped:0]
  },
  {
    "Path": "/Statistics/DeltaTable",
    "Script": [Wrapped:0]
  }
]
```

---

### `is_migration_table_exists(): bool`
**Description**: Checks if the migration table, as defined by the property `migration_table`, already exists. 

**Return**: `true` if the table exists. 

Neither the table's structure nor its content is validated.

---

### `load_migration_log(include_errors: bool): Array`
| Parameter        | Type | Description                                                                                               |
|------------------|------|-----------------------------------------------------------------------------------------------------------|
| `include_errors` | bool | If set to `true`, all log records will be returned; otherwise, only the successful runs will be returned. |


**Description**: Load metadata about previous migration script runs from the migration table.  

**Return**: Each record in the array is a dictionary with the following keys:

| Name      | Description                                                                                           |
|-----------|-------------------------------------------------------------------------------------------------------|
| `Created` | Date and time when the record was created in local user time                                          |
| `Index`   | The sequence number of the script. Used to identify desync issues.                                    |
| `Path`    | The relative path to the script from the migration node, used to uniquely identify migration scripts. |
| `Result`  | `true` or `false` value indicating if the execution was successful or not.                            |
| `Error`   | The error message for unsuccessful runs.                                                              |

**Example**:

```
extends Control

@onready var migrations: SQLMigrationNode = $SQLNode/SQLMigrationNode

func _ready() -> void:
    migrations.execute()
    print(migrations.load_migration_log(false))
```

```
[{ "Created": "2025-02-17 08:32:20", "Index": 0, "Path": "/InitDB", "Result": true, "Error": "" }]
```

---

### `get_desync_issues(): SQLStmt`
**Description**: Identifies discrepancies between the migration table and the migration scripts.

This method is primarily used to detect and log migration issues when a migration fails.

> Desync issues in a production build are **CRITICAL**. Running mismatched scripts
can result in a corrupt save file or leave the database in an inconsistent state.

**Return**: An array containing details of each discrepancy found between the migration log table and the migration scripts. 

A non-empty value indicates an issue. An empty value means there are no desync issues.

**Example**:

```
extends Control

@onready var migrations: SQLMigrationNode = $SQLNode/SQLMigrationNode

func _ready() -> void:
    # First we run the migration script once
    migrations.execute()
    
    # DeltaTable is the first script and 
    # RuntimeTable is the second.
    
    # Now, let's rearrange the order of the scripts.
    $SQLNode/SQLMigrationNode/Statistics.move_child(
        $SQLNode/SQLMigrationNode/Statistics/DeltaTable, 
        1)
    
    
    
    # Because the order of the scripts must be preserved,
    # the rearrangement we made will cause an error.
    print(migrations.get_desync_issues())
```

Outputs:
```
[
    "At position 1 expected script /Statistics/DeltaTable but got /Statistics/RuntimeTable", 
    "At position 2 expected script /Statistics/RuntimeTable but got /Statistics/DeltaTable"
]
```

Additionally, following execute commands will fail due to the desync issue.

---

### `is_up_to_date(): SQLErrors`
**Description**: Checks if the database is up to date.  

**Return**: `true` if all scripts have been applied and there are no desync issues.

## Signals

### `begin_migration()`
**Description**: The signal is triggered by the `execute()` method before any validations are made or any scripts run.

---

### `migration_failed()`
**Description**: The signal is triggered if the `execute()` method fails to complete successfully.

---

### `migration_complete()`
**Description**: The signal is triggered if the `execute()` method completes successfully, 
even if no scripts were called (This can happen if the database is already up to date). 

---

### `before_script(path: String, script: SQLMigrationScript)`
| Parameter | Type                | Description                                                                                       |
|-----------|---------------------|---------------------------------------------------------------------------------------------------|
| `path`    | String              | The relative path of the script to this migration node. Also use to uniquely identify the script. |
| `script`  | SQLMigrationScript  | Reference to the script itself.                                                                   |

**Description**: This method is called before each script is executed.

---

### `script_complete(path: String, script: SQLMigrationScript)`
| Parameter | Type                | Description                                                                                       |
|-----------|---------------------|---------------------------------------------------------------------------------------------------|
| `path`    | String              | The relative path of the script to this migration node. Also use to uniquely identify the script. |
| `script`  | SQLMigrationScript  | Reference to the script itself.                                                                   |

**Description**: Triggered after each script, if it was executed successfully. 

---

### `script_failed(path: String, script: SQLMigrationScript)`
| Parameter | Type                | Description                                                                                       |
|-----------|---------------------|---------------------------------------------------------------------------------------------------|
| `path`    | String              | The relative path of the script to this migration node. Also use to uniquely identify the script. |
| `script`  | SQLMigrationScript  | Reference to the script itself.                                                                   |

**Description**: Triggered when a script execution failed. 
