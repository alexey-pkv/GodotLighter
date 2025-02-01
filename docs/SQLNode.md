# SQLNode

**Extends:** [Node](https://docs.godotengine.org/en/4.3/classes/class_node.html)

This is the primary interface for interacting with the library. `SQLNode` represents a single connection to an SQLite database.

To connect to an existing database or create a new one, attach a new `SQLNode` to your scene tree. The connection is established either when the first command is executed or when the `open()` method is explicitly called.  

> When the node is deleted, if a connection is still open, it will be closed and safely disposed of.

## Methods

### `errors(): SQLErrors`
**Description**: Returns the global [SQLErrors](Objects/SQLErrors.md) object.

---

### `sqlighter_version(): String`
**Description**: Returns the version of the SQLighter C++ library.

---

### `library_version(): String`
**Description**: Returns the version of this library.

---

### `sqlite_version(): String`
**Description**: Returns the version of the SQLite library.

---

### `versions_info(): String`
**Description**: A helper function that returns all the versions in one string, each on a new line. 

**Example**
```
func _ready() -> void:
	print(GLighter.versions_info())
```

will output

```
GodotLighter : 0.1.0
SQLighter    : 0.1.4
SQLite       : 3.48.0
```
