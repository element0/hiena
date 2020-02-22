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

#include "../cosmos/cosm_lookup.h" // requires 'libcosmos'

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
    cosmosService( string address ) {
        // construct here
    }
    string getMIMEType( string address ) {
        // custom module implements this
    }
    iostream openStream();
};

class hienaMap {
};

class dcel;

class cosmosType {
  public:
    string MIMEType;
    string moduleFilePath;

    hienaMap *mapper(dcel &source) {}

    // conformance tree
    list<cosmosType> parents;
    list<cosmosType> children;

    void locateModule();
    void loadModule();
    cosmosType( string cosmos_typename ) {
        // load module
    }
};


class cosmosSystemObject {
  public:
    conformanceTree typeTree;
    map<string, cosmosType> typeModules;
    map<string, cosmosService> serviceModules;

    int init() {
        cout<<"cosmosSystemObject::init()"<<endl;
        return 0;
    }

    cosmosService getServiceModule( string serviceStr ) {
    }

};


class dcel {
  public:
    static cosmosSystemObject cosmos;

    cosmosService service;
    string address;
    cosmosType type;

    list<cosmosType> types;
    list<dcel> children;

    int initCosmos() {
        cosmos.init();
    }

    cosmosType loadTypeModule(string type_name);

    dcel( string stringBacking )
          : service("std::string")
            address(stringBacking) {
    }

    dcel( string serviceStr, string addrStr )
	    : service( serviceStr ),
	      address( addrStr ),
            type( service.getMIMEType( addrStr ))
    {
        service = cosmos.getServiceModule( serviceStr );
    }

    conformanceTree getTypes() {};
};




void hiena(dcel &source) {


    /* map a single layer of hierarchy
        with multiple grammars
     */
    hienaMap *map;
    for ( auto curType : source.getTypes() ) {
        map = curType.mapper( source );
        if ( map != NULL )
            // source.map += map;
            ;
    };

    /* recursive mapping */

    for ( auto child : source.children ) {
        hiena( child );
    };
}


int main(int argc, char *argv[]) {

    /* initialize global cosmos object */
    /* (systemwide globals are stored
        in the dcel class static vars.)
     */
    dcel::initCosmos();

    dcel url{ argv[1] };

    /* overloaded op to type array:
        "url" will be located by cosmos_lookup()
     */
    // url.type += "url";
    url.

    dcel source { url.field("scheme"), url.field("address") };

    hiena( source );
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
      /* return a map as part of the dcel */
}
*/
