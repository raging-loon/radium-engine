# radium-engine/core

Core Functionality of the engine

## Sub Directories

### Application
Application class. 
- Holds all subsystems the game needs
- Controls loading of resource packs

### Config 
Configuration Data

Reads data from a config file.
Config file should look like this:

```ini
[Some Section]
key1=value1
...
...
[Some Other Section]
otherkey=othervalue
```

### Debug
Controls access to loggers (via spdlog)

### Event
Holds an event system and built-in types

### Input
PIMPL Abstraction over input.

Implementations can be found in `platform/<platform>/<platform>Input.cpp`

## Files


### radpch.[h/cpp]
Precompiled header

### SmartPtr.h
Wrapper around builtin smart pointers

`radium::Ref` ⇒  `std::shared_ptr`

`radium::Scope` ⇒  `std::unique_ptr`

`radium::makeRef` ⇒  `std::make_shared`

`radium::makeScope` ⇒ `std::make_unique`

### types.h
Types for Integers and Float with shortened names.

E.g. `U32` = `uint32_t`


### `Variant.[h/cpp]`
Variant class. Mainly used in `Config`

Supported types right now are
- `int`
- `bool`
