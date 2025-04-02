# SQLErrorInfo

The SQLErrorInfo object provides detailed information about errors that occur within the GodotLighter library. It acts as a wrapper for capturing and examining SQL-related error details.

## Methods

### `code(): int`
**Description**: Returns the unique error code associated with the SQL error.  

> This error code is specific to the **SQLighter** library and differs from the SQLite error code. To retrieve the SQLite-specific error code, use `err_sqlite_code()`.  

**Return**: An integer representing the SQLighter library's error code.

---

### `error(): String`
**Description**: Provides a comprehensive error message describing the specific error that occurred. 

**Return**: A string containing the full error description.

---

### `err_additional_message(): String`
**Description**: Retrieves additional contextual information about the error when available. 

> This supplementary message provides extra details that can help diagnose the underlying issue.

**Return**: A string with supplementary error information.

---

### `err_sqlite_code(): int`
**Description**: Returns the SQLite-specific error code associated with the error.

**Return**: An integer representing the precise SQLite error code.

---

### `err_sqlite_str(): String`
**Description**: Retrieves the raw error message directly from SQLite.

**Return**: A string containing the SQLite error message.

---

### `err_lighter_str(): String`
**Description**: Returns a human-readable error message specific to the SQLighter library's error code.

**Return**: A user-friendly description of the error.

---

### `err_query(): String`
**Description**: Retrieves the SQL query string associated with the error, if available.

**Return**: The SQL query that triggered the error, or an empty string if no query was associated.