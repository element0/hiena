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



class cosmosType {
  public:
    string MIMEType;
    string type_name;

    string moduleMapperPath;
    void *mapper_dl;

    int (*mapper_fn)(istream &);
    
    
    // conformance tree
    list<cosmosType> parents;
    list<cosmosType> children;

    // module-defined elements
    hienaMap *(*mapper)(dcel &source) {};


    // module management
    void loadModule() {

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
		mapper_fn = (int (*)(istream &))dlsym( mapper_dl, "mapper" );
          } else {
              mapper_dl = NULL;
          }
    }

    void set_type_name( string cosmos_typename = "" )
    {
	    type_name = cosmos_typename;
	    loadModule();
    }

    // constructors
    cosmosType( string cosmos_typename = "" )
	    : type_name(cosmos_typename),
	      MIMEType(cosmos_typename)
    {
	    loadModule();
    }
};


class cosmosSystemObject {
  public:
    conformanceTree typeTree;
    map<string, cosmosType> typeModules;
    map<string, cosmosService> serviceModules;


    cosmosSystemObject() {
        cout<<"cosmosSystemObject constructor called."<<endl;
    }

    cosmosService getServiceModule( string serviceStr ) {
    }

    string testStr() {
        return "cosmosSystemObject::testStr()";
    }
};

class dcel {
  public:
    static cosmosSystemObject cosmos;

    cosmosService service;
    string address;
    cosmosType type;

    list<cosmosType*> types;
    list<dcel> children;
    list<dcel> fields;

    /// map
    string name;



    dcel( string stringBacking )
          : service("std::string"),
            address(stringBacking)
    {
    }

    dcel( string serviceStr, string addrStr )
	    : service( serviceStr ),
	      address( addrStr ),
              type( service.getMIMEType( addrStr ) )
    {
        // service = cosmosSystemObject::getServiceModule( serviceStr );
    }


    void addType( string type_name ) {
        types.push_back( new cosmosType( type_name ) );
    };

    void setType( string type_name ) {
        type.set_type_name( type_name );
    };

    void makeMap() {
	istringstream & stream = service.open( address );
	type.mapper_fn((istream &)stream);
    }


    string field( string fieldName ) {
	    string tmpString { fieldName };
	    return tmpString;
    };
};
