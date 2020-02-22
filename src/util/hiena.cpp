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
    string type_name;

    hienaMap *mapper(dcel &source) {}

    // conformance tree
    list<cosmosType> parents;
    list<cosmosType> children;

    void locateModule();
    void loadModule();

    cosmosType( string cosmos_typename = "" ) {
        // load module
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

    list<cosmosType> types;
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

    cosmosType loadTypeModule(string type_name) {};
    conformanceTree getTypes() {};

    void addType( string type_name ) {
        type.type_name = type_name;
    };

    string field( string fieldName ) {
	    return "field placeholder";
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

cosmosSystemObject cosmos;

int main(int argc, char *argv[]) {

    /* initialize global cosmos object */
    /* (systemwide globals are stored
        in the dcel class static vars.)
     */

    dcel url { argv[1] };

    // dcel::cosmos is being "optimized out" 
    // and the following says dcel::cosmos is undefined.
    // can we make cosmosSystemObject cosmos a global?
    string testStr = cosmos.testStr();

    /* overloaded op to type array:
        "url" will be located by cosmos_lookup()
     */
    url.addType( "url" );

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
      // return a map as part of the dcel
}
*/
