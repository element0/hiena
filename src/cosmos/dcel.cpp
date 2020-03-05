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


    /* --- cosmosType */

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
		}
		mapper_fn = (dcel *(*)(istream &))dlsym( mapper_dl, "mapper" );
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

    cosmosService::cosmosService( string address ) : name( address ) {}





    /*--- cosmosSystemObject */

    cosmosSystemObject::cosmosSystemObject() {
        cout<<"cosmosSystemObject constructor called."<<endl;
    }

    cosmosService cosmosSystemObject::getServiceModule( string serviceStr ) {
    }

    string cosmosSystemObject::testStr() {
        return "cosmosSystemObject::testStr()";
    }




    /*--- dcel */

    dcel::dcel( string stringBacking = "" )
          : service("std::string"),
            address(stringBacking)
    {}

    dcel::dcel( string serviceStr, string addrStr )
	    : service( serviceStr ),
	      address( addrStr ),
              type( service.getMIMEType( addrStr ) )
    {
        // service = cosmosSystemObject::getServiceModule( serviceStr );
    }

    dcel::dcel( dcel *source )
	    : service( "" ),
	      address( "" ),
            dcelBacking( source )
    {
    }

    void dcel::addType( string type_name ) {
        types.push_back( new cosmosType( type_name ) );
    }

    void dcel::setType( string type_name ) {
        type.set_type_name( type_name );
    }

    void dcel::makeMap() {
	istringstream & stream = service.open( address );
	type.mapper_fn((istream &)stream);
    }


    /* return contents of field as a string
     */
    string dcel::field( string fieldName ) {
	    string tmpString { fieldName };
	    return tmpString;
    }

    dcel *dcel::addField() {
        return new dcel("");
    }

    dcel *dcel::addField(string name, int start, int stop) {
        dcel *newField = new dcel(this);
        fields.insert(pair<string,dcel *>(name,newField));
        newField->start = start;
        newField->stop = stop;
        return newField;
    }

    dcel *dcel::enter() {
        return new dcel("");
    }

    dcel *dcel::exit() {
        return new dcel("");
    }


}
