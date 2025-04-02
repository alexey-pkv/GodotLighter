# GodotLighter 

SQLite plugin for Godot. 

An example project can be found here: [docs/Example.md](./docs/Example.md) 


# Road Map

### **v1.0.0**

- [x] Add documentation / Tutorial
- [ ] Ensure that any existing statements are finalized when the DB connection is closed
- [x] Add JOIN, JOIN LEFT and JOIN RIGHT to the select constructor
- [x] Add basic migration tools

### **v1.1.0**
- [ ] Add binding by name
- [ ] Add the ability to create and reuse prepared statements
- [ ] Make it thread safe

### **v1.2.0**  
- [ ] Add support for SQLite3 Backup's
- [ ] Basic Object to table Mapping 
- [ ] Add callback functions support


# Guides

* [Database Migrations](./docs/Guides/Migrations.md)
* [Error Handling](./docs/Guides/ErrorHandling.md)


# References 

* [GLighter](./docs/GLighter.md)
* [SQLNode](./docs/SQLNode.md)
* [SQLMigrationNode](./docs/Migration/SQLMigrationNode.md)
* [SQLMigrationScript](./docs/Migration/SQLMigrationScript.md)


### Errors
* [SQLErrorInfo](./docs/Objects/SQLErrorInfo.md)
* [SQLErrors](./docs/Objects/SQLErrors.md)