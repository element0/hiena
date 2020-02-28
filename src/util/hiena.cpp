/** @file hiena.cpp
 *
 * Cosmos Project
 * hiena utility
 * 2020-02-20 rh
 *
 * CLI entry point tool for hierarchy analysis.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
using namespace std;

extern "C" {
#include "../cosmos/cosm_lookup.h" // requires 'libcosmos'
#include <dlfcn.h>
}

// #include "cosmos.h"  // string db, global cosmos
// #include "cosmosLexer.h"
// #include "cosmosParser.h"
// #include "antlr4-runtime.h"
// using namespace antlr4;

class cosmosType;

template <typename T>
class accessTree {
    private:
    public:
        T *pointer;
        list<accessTree> parents;
        list<accessTree> children;

    accessTree(T *p)
    {
        pointer = p;
    }
};

template <typename T>
class inheritanceTree : public accessTree<T> {
    public:
        // override sequence getter methods
};

class conformanceTree : public list<cosmosType> {
  public:
    conformanceTree findSubtreeWithType( cosmosType type );
};


class cosmosService : public string {
  public:
    string name;

    string getMIMEType( string address ) {
        return address;
    }

    iostream openStream();

    cosmosService( string address ) : name( address ) {}
};


class hienaMap;
class dcel;

class cosmosType {
  public:
    string MIMEType;
    string type_name;

    string moduleMapperPath;
    void *mapper_dl;

    int (*mapper_fn)();
    
    
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
		mapper_fn = (int (*)())dlsym( mapper_dl, "mapper" );
		mapper_fn();

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

    string field( string fieldName ) {
	    string tmpString { fieldName };
	    return tmpString;
    };
};




void hiena(dcel &source) {


    /* map a single layer of hierarchy
        with multiple grammars
     */
    hienaMap *map;

    /* fix dcel::types
    for ( auto curType : source.getTypes() ) {
        map = curType.mapper( source );
        if ( map != NULL )
            // source.map += map;
            ;
    };
    */

    /* recursive mapping */

    /* implement dcel::children
    for ( auto child : source.children ) {
        hiena( child );
    };
    */
}


/* initialize global cosmos object */

cosmosSystemObject cosmos;



int main(int argc, char *argv[]) {

    if ( argc < 2 )
        return 0;
    
    dcel url { argv[1] };

    /*
        "url" will be located by cosmos_lookup()
     */
    url.setType( "url" );


    string scheme_field = url.field("scheme");
    string address_field = url.field("address");

    dcel source { scheme_field, address_field };

    hiena( source );

    return 0;
}


/*
void mapper(dcel) {
    cosmosStream urlStream(dcel.open());

	if (urlStream.is_open()) {

		ANTLRInputStream input(urlStream);
		cosmosLexer lexer(&input);
		CommonTokenStream tokens(&lexer);

		tokens.fill();
		cosmosParser parser(&tokens);
		tree::ParseTree *tree = parser.stored_definition();

		urlStream.close();

	}
      // return a map as part of the dcel
}
*/
