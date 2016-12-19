Hiena	{#mainpage}
=====

![Travis CI Status](https://api.travis-ci.org/element0/hiena.svg?branch=master)



## Description ##

A library and architecture for mapping a hierarchy.  Suitable for creating file space addresses in arbitrary data files.


## Hiena Main Function ##

`THIS IS A LITTLE OUT OF DATE`

The main function of hiena is to "map a domain".

You can use the `hiena` function recursively in your own pathwalk or (tree renderer) to iterate over a hierarchy of domains.

The domain is passed in the form of a "domain cell" or `dcel` which keeps internal mappings as well as info about its storage location and retrieval method.  It also has an optional internal 'filter' which can process the data from storage before sending it out to the mappers. (The actual "read" which the mappers should use, will be the "dcel source" module encapsulated within a `dcel_io` object.)

A mapper module need only use the `dcel_io` API.

The hiena function accesses its modules through a module list.  So if you wish, you can pass different modules to different levels of hierarchy.

	hiena( dcel_io, module_list )

	BEGIN
	- clone input dcel (aspire to COW process)
	- select mapper based on dcel's `expect` property
	- run mapper from module on `dcel_io` object
		- mapper may create data mappings
		- mapper may create a directory of child dcels
		- mapper may assign server modules to each child dcel
		- mapper may assign `expect` to each child dcel
		- dcel_io will select source server
		- dcel_io will filter the stream before output to mapper
	- return mapped dcel
	END


## Hiena DCel Structure ##

A dcel is a "Domain Cell".  It contains the following.

	- inner data source 	// the location of data and location server
	- inner data filter		// functions to filter data from address
	- inner file directory	// directory index to child dcels
	- inner data mappings	// named or classified data locations
	- inner type expect		// scanner module names to constrain content

## Data Source ##

At a minimum, a data source needs to be

	- location of data
	- server functions for reading the location

This could be a complex object.  Location could be fragmented across storage or could include data bindings to other objects.

## Default Sources ##

A minimum configuration of hiena should include modules for these sources:

	- buf server
	- dcel server

This allows you to create a dcel which has storage inside a buffer.  And it hiena to create dcels which have virtual storage inside other dcels.

## Hiena Grammar ##

Hiena grammar takes after bison.

	#include <hiena.h>

	%%
	hiena_rule 	: mapping
				| dcel_nest
				;

	dcel_nest	: dcel_raw dcel_server dcel_content_expect
				;

	%%
	void *a_decel_server ( ... );

## Hiena Main ##


## Hiena Module ##

When you write a hiena module, you must include both parser functions and some stream server functions.

	void *read( struct hiena_dcel_io * );

	void *moduleid_parse( void *parserstate, struct hiena_dcel_io * );	


	

