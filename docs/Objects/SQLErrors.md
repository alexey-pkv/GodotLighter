# SQLErrors

`SQLErrors` is an object designed to store and reference the most recent error that occurred within the GodotLighter library.

This object cannot be instantiated directly. It is accessible exclusively through the global `GLighter` static class or the `SQLNode` object.


## Properties

### `print_errors: bool`
**Description**: When set to `true`, any error that propagates to this `SQLErrors` object will be printed to the Godot log.

By default, all `SQLErrors` objects associated with an `SQLNode` have this property set to `false`, while the object within the `GLighter` class has it set to `true`. Since all errors handled by an `SQLNode` instance propagate to the global static `GLighter` class, any error will be printed to the Godot log exactly once unless you explicitly change the value of `print_errors`.


## Methods

### `has_err(): bool`
**Description**: Returns true if an error is available within the object.      

---

### `last_err(): SQLErrorInfo`
**Description**: Get the last error info object. 

**Return**: An [SQLErrorInfo](SQLErrorInfo.md) object, or null if no error occurred or if `reset_error()` was called. 


## Signals

### `on_error(error: SQLErrorInfo)`
**Description**: This signal is emitted whenever an error occurs within the associated SQLNode or its context. The signal carries an [SQLErrorInfo](SQLErrorInfo.md) object, which provides details about the error.

> The signal is called after the value of `last_err` is updated

