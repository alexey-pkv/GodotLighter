# GLighter

This is a static class that currently provides version information and access to an [SQLErrors](Objects/SQLErrors.md) object, which stores the last error that occurred within the context of this library.


## Methods

### `errors(): SQLErrors`
**Description**: Returns the global [SQLErrors](Objects/SQLErrors.md) object used for tracking and managing library-wide errors.

**Return**: A singleton [SQLErrors](Objects/SQLErrors.md) object for error handling.

**Example**:

```gdscript
# Access global error tracking
var errors = GLighter.errors()

if errors.has_err():
    print("An error occurred: %s" % errors.last_err().error())
```

---

### `sqlighter_version(): String`
**Description**: Returns the version of the underlying SQLighter C++ library.

**Return**: A string representing the SQLighter library version.

**Example**:

```gdscript
print("SQLighter Library Version: %s" % GLighter.sqlighter_version())
```

---

### `library_version(): String`
**Description**: Returns the version of the GodotLighter plugin.

**Return**: A string representing the GodotLighter plugin version.

**Example**:

```gdscript
print("GodotLighter Plugin Version: %s" % GLighter.library_version())
```

---

### `sqlite_version(): String`
**Description**: Returns the version of the SQLite library used by the plugin.

**Return**: A string representing the SQLite library version.

**Example**:

```gdscript
print("SQLite Library Version: %s" % GLighter.sqlite_version())
```

---

### `versions_info(): String`
**Description**: Provides a comprehensive string with version information for SQLighter, GodotLighter, and SQLite libraries.

**Return**: A multi-line string containing version details.

**Example**:

```gdscript
print(GLighter.versions_info())

# Outputs something like:
# GodotLighter : 0.1.0
# SQLighter    : 0.1.4
# SQLite       : 3.48.0
```

## Error Tracking Use Cases

```gdscript
# Global error tracking across SQLite operations
GLighter.errors().on_error.connect(func(error): 
    push_error("SQLite Error: %s" % error.error())
)
```
