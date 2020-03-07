/** @file dcel.cpp
 *
 * Cosmos Project
 * hiena utility
 * 2020-03-02 rh
 *
 * dcel methods
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>

using namespace std;

extern "C" {
#include "cosm_lookup.h" // requires 'libcosmos'
#include <dlfcn.h>
}

#include "dcel.h"


namespace Cosmos {


    /***************************************/
    /* --- initialize global cosmos object */
    /***************************************/

    cosmosSystemObject cosmos;



    /******************/
    /* --- cosmosType */
    /******************/

    void cosmosType::loadModule() {

	if( type_name.empty() )
		return;

	string moduleSoRelpath = "Types/" + type_name + "/lib/mapper.so";
	const char *moduleMapperPath = cosm_lookup( moduleSoRelpath.c_str() );
	if( moduleMapperPath != NULL ) {
	    mapper_dl = dlopen( moduleMapperPath, RTLD_NOW );
	    const char *err = dlerror();
	    if( err != NULL ) {
		cout<<"error:"<<err<<endl;
		mapper_dl = NULL;
		mapper_fn = NULL;
	    } else {
		mapper_fn = (dcel *(*)(istream &))dlsym( mapper_dl, "mapper" );
	    }
	    cosmos.typeModules[moduleMapperPath] = this;
	} else {
	    mapper_dl = NULL;
	}
    }

    void cosmosType::set_type_name( string cosmos_typename = "" ) {
	    type_name = cosmos_typename;
	    loadModule();
    }

    cosmosType::cosmosType( string cosmos_typename = "" )
	    : type_name(cosmos_typename),
	      MIMEType(cosmos_typename)
    {
	    loadModule();
    }




    /*--- cosmosService */

    string cosmosService::getMIMEType( string address ) {
	return address;
    }

    istringstream & cosmosService::open( string address ) {
	if (name == "std::string") {
	    istringstream *s = new istringstream(address);
	    return *s;
        }
    }

    ostringstream & cosmosService::asOstringstream(string address) {
        if (name == "std::string") {
	    ostringstream *s = new ostringstream(address);
	    return *s;
        }
    }

    cosmosService::cosmosService( string newName ) : name( newName ) {}




    /*************************/
    /*--- cosmosSystemObject */
    /*************************/

    cosmosSystemObject::cosmosSystemObject() {
        cout<<"cosmosSystemObject constructor called."<<endl;
    }

    cosmosService *cosmosSystemObject::getService( string serviceStr ) {
        return serviceModules[serviceStr] = new cosmosService(serviceStr);
    }

    cosmosType *cosmosSystemObject::getType( string typeStr ) {
	return typeModules[typeStr] = new cosmosType(typeStr);
    }





    /***********/
    /*--- dcel */
    /***********/

    dcel::dcel( string stringBacking = "" ) {
	service = cosmos.getService("std::string");
	address = stringBacking;
    }

    dcel::dcel( string serviceStr, string addrStr ) {
        service = cosmos.getService( serviceStr );
        address = addrStr;
    }


    // delete this
    dcel::dcel( dcel *source ) {
	// remove
        dcelBacking = source->dcelBacking;
    }



    void dcel::addType( string type_name ) {
        types.push_back( new cosmosType( type_name ) );
    }


    void dcel::setType( string type_name ) {
	type = cosmos.getType( type_name );
    }

    void dcel::makeMap() {
	istringstream & stream = service->open( address );

       // the map needs to have its dcelBacking
       // pointed to 'this.'
	dcel *map = type->mapper_fn((istream &)stream);

	// delete this
        map->dcelBacking = this;
	
	fields = map->fields;
    }


    string *dcel::str() {
        if( service->name == "std::string" ) {
            auto value = new string(address);
            return value;
        }
    }


    /* return contents of field as a string
     */
    string *dcel::field( string fieldName ) {

        // no need dcelBacking, just find field and use 'this' as backing.

        multimap<string, dcel *>::iterator it = fields.find(fieldName);

	// how do we judge if not found?
	/*
        if( it.end ) {
            return NULL;
        }
	*/

        dcel *target = it->second;

        string *value = target->str();

        // copy string out
        // tbd

        if( target == NULL ) {
            return NULL;
        }

	return new string("temp output");
    }

    dcel *dcel::addField() {
        return new dcel("");
    }

    dcel *dcel::addField(string name, int start, int stop) {
        dcel *newField = new dcel();
        newField->dcelBacking = dcelBacking;
        newField->start = start;
        newField->stop = stop;

       newField->superField = this;

        fields.insert(pair<string,dcel *>(name,newField));

        return newField;
    }

    dcel *dcel::enter() {
        return this;
    }

    dcel *dcel::exit() {
        return superField;
    }



}


