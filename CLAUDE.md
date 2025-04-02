# GodotLighter Development Guide

## Code Style
- C++17 standard with CMake build system
- Classes: PascalCase (SQLNode, GLighter)
- Methods: camelCase (execute_stmt)
- Member variables: snake_case with m_ prefix (m_errors)
- Constants: UPPER_SNAKE_CASE
- Type aliases: snake_case (gstr, uptr)
- Header guards: #ifndef GODOTLIGHTER_FILE_H
- Include order: project headers first, then external
- Error handling: use SQLErrors and SQLErrorInfo classes
- Memory: use smart pointers (uptr<>, sptr<>) and Godot's Ref<>
- Documentation: maintain markdown docs in /docs directory

## External Dependencies
- Godot C++ bindings (submodule)
- SQLighter library
- SQLite3