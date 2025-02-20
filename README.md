[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub Tag](https://img.shields.io/github/v/tag/alexey-pkv/GodotLighter?label=Version)
[![](https://dcbadge.limes.pink/api/server/YTVeGYqCaC?style=flat)](https://discord.gg/YTVeGYqCaC)


# GodotLighter 

Godot SQLite plugin

# Road Map

### **v1.0.0**

- [ ] Add documentation / Tutorial
- [ ] Ensure that any existing statements are finalized when the DB connection is closed
- [ ] Add JOIN, JOIN LEFT and JOIN RIGHT to the select constructor
- [x] Add basic migration tools

### **v1.1.0**
- [ ] Add binding by name
- [ ] Add the ability to create and reuse prepared statements
- [ ] Make it thread safe

### **v1.2.0**  
- [ ] Add support for SQLite3 Backup's
- [ ] Basic Object to table Mapping 
- [ ] Add callback functions support

# Feature Examples

* [Database Migrations](./docs/Features/Migrations.md)

# References 

* [GLighter](./docs/GLighter.md)
* [SQLNode](./docs/SQLNode.md)
* [SQLMigrationNode](./docs/Migration/SQLMigrationNode.md)
* [SQLMigrationScript](./docs/Migration/SQLMigrationScript.md)


### Error Handling
* TODO: How the library handles errors.
* [SQLErrorInfo](./docs/Objects/SQLErrorInfo.md)
* [SQLErrors](./docs/Objects/SQLErrors.md)
