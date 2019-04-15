Cosmos and Hiena	{#mainpage}
================

![Travis CI Status](https://api.travis-ci.org/element0/hiena.svg?branch=iphdev)



## Description ##


Cosmos is an extensible, distributed file system which aggregates file systems (or portions of) from any number of devices into a single file system.

Extensibility:

- Pluggable file accessors
- Pluggable file analyzers
- Pluggable file transformers
- Pluggable syncronization manager
- Pluggable pathwalk function


Distributed:

- Configurable storage flows between hosts
- Intermittent and high-latency syncronization tolerance
- Modules are virtualized among all hosts, and run native on capable hosts or within virtual machines.


Availability:

The database can be built into a project, accessed via a network service or exported as a file system via FUSE (or similar framework.)

Any instances of the database intercommunicate to create a distributed filespace.



## Pluggable Hierarchical Analyzer: Hiena ##


With Hiena, a mapper module maps one or more levels of hierarchy within a seekable data source, which in turn can be mapped by other modules. The result is a file tree accessable via regular file paths.

Mapper modules are defined by parser grammars and are compiled via dispatch from Hiena to a compiler such as Bison or Antler.




## Cascading Configuration Directories ##


Cosmos provides automatic cascading of configuration directories such that a child directory inherits and overrides configurations within the parent directory.

A user has the advantage of automatic cascading merely by placing config files into the directory.

Cosmos is configured via the cascading directory from its file system root. So file system behavior can be modified on an abitrary subdirectory level.

Useful modifications include distributed host memberships, storage flows and the ability to change the configuration directory name.



## DEVELOPMENT NEWS ##


2019-04-14  Currently designing mobile app and shared library. Nothing works yet.


2017-03-25	`./util/byterange FILENAME STARTBYTE ENDBYTE` extracts a byte range from a file.



