[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub Tag](https://img.shields.io/github/v/tag/alexey-pkv/GodotLighter?label=Version)

# GodotLighter 

Godot SQLite plugin

# Road Map

> Road map for version **v1.0.0**

- [ ] Add documentation
- [ ] Ensure that any existing statements are finalized when the DB connection is closed. 
- [ ] Add JOIN, JOIN LEFT and JOIN RIGHT to the select constructor.  
- [ ] Add support for SQLite3 Backup's.
- [ ] Add basic migration tools.

> Road map for version **v1.1.0**
- [ ] Unit tests? UNIT TESTS!
- [ ] Add binding by name
- [ ] Add the ability to create and reuse prepared statements.  
- [ ] Make it thread safe.

> Road map for version **v1.2.0**
- [ ] Basic Object to table Mapping 
- [ ] Add callback functions support

# References 

* [GLighter](./docs/GLighter.md)
* [SQLNode](./docs/SQLNode.md)

### Error Handling
* TODO: How the library handles errors.
* [SQLErrorInfo](./docs/Objects/SQLErrorInfo.md)
* [SQLErrors](./docs/Objects/SQLErrors.md)
