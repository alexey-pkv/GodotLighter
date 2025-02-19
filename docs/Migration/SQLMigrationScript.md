# SQLMigrationNode

**Extends:** [Node](https://docs.godotengine.org/en/4.3/classes/class_node.html)

A `SQLMigrationScript` represents an individual migration script used to update a database.  

While it is possible to use this node on its own for database updates, it is designed 
to function as a child (or grandchild) of the [`SQLMigrationNode`](SQLMigrationNode.md).


## Virtual Methods

### `_update(node: SQLNode): void`
| Parameter | Type                       | Description                                                    |
|-----------|----------------------------|----------------------------------------------------------------|
| `node`    | [`SQLNode`](../SQLNode.md) | This will be the Database node that is currently being updated |

**Description**: This is the method that will be called by the script node in order to update the database. 

## Methods

### `execute_update(): bool`  
**Description**: Executes the script on the first `SQLNode` parent of this node.  

This method calls the virtual `_update` method.  

**Return**: `true` if the migration executes without errors.  

---

### `execute_update_for(node: SQLNode): bool`  
| Parameter | Type                       | Description                 |
|-----------|----------------------------|-----------------------------|
| `node`    | [`SQLNode`](../SQLNode.md) | The database node to update |

**Description**: Executes the script on a specific `SQLNode`.  

This method is called by the parent [`SQLMigrationNode`](SQLMigrationNode.md) and invokes the 
virtual `_update` method.  

**Return**: `true` if the migration executes without errors.

## Signals  

### `before_update(script: SQLMigrationScript)`  
| Parameter | Type                 | Description       |  
|-----------|----------------------|-------------------|  
| `script`  | `SQLMigrationScript` | Reference to self |  

**Description**: Triggered when execution is initiated on this node, before any checks or scripts are run.  

---  

### `on_updated(script: SQLMigrationScript)`  
| Parameter | Type                 | Description       |  
|-----------|----------------------|-------------------|  
| `script`  | `SQLMigrationScript` | Reference to self |  

**Description**: Triggered if the script executes successfully.  

---  

### `on_failed(script: SQLMigrationScript)`  
| Parameter | Type                 | Description       |  
|-----------|----------------------|-------------------|  
| `script`  | `SQLMigrationScript` | Reference to self |  

**Description**: Triggered if the script execution fails.
