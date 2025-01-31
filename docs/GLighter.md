# GLighter

This is a static class that currently provides version information and access to an [SQLErrors](Objects/SQLErrors.md) object, which stores the last error that occurred within the context of this library.


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
