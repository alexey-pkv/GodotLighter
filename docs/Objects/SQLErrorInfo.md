# SQLErrorInfo

The SQLErrorInfo object acts as a wrapper for errors, enabling users to access detailed information about errors that occur within the GodotLite library.

## Methods

### `code(): int`
**Description**: Returns the error code associated with the SQL error.  

> This error code is specific to the **SQLighter** library and not SQLite3. To retrieve the SQLite3 error code, use err_sqlite_code()  

---

### `error(): String`
**Description**: This is the full error message, providing detailed information about the error. 

---

### `err_additional_message(): String`
**Description**: Sometimes, additional information about an error may be available depending on the scope of the operation where the error occurred. When such a message is available, it can be retrieved using this method.

> This value is also appended to the output of error() string.

---

### `err_sqlite_code(): int`
**Description**: Get the SQLite-specific error code.

---

### `err_sqlite_str(): String`
**Description**: Get the SQLite error message associated with the SQLite error code.

---

### `err_lighter_str(): String`
**Description**: Get a human-readable error message for the **SQLighter**-specific error code. 

---

### `err_query(): String`
**Description**: Retrieve the SQL query string related to the error, if available.
