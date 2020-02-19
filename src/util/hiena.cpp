/** @file hiena.cpp
 *
 * Cosmos Project
 * hiena utility
 * 2020-02-15 rh
 *
 * CLI entry point tool for hierarchy analysis.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

#include "../cosmos/cosm_lookup.h" // requires 'libcosmos'

// #include "cosmos.h"  // string db, global cosmos
// #include "cosmosLexer.h"
// #include "cosmosParser.h"
// #include "antlr4-runtime.h"
// using namespace antlr4;

class cosmosType;

class conformanceTree : public list<cosmosType> {
  public:
    conformanceTree findSubtreeWithType( cosmosType type );
};

class cosmosSystemObject {
  public:
    conformanceTree typeTree;
    map<string, cosmosType> typeModules;


    conformanceTree typeTree = source.cosmos.typeTree;
};


class dcelService : public string {
  public:
    string getMIMEType( string address );
    iostream openStream();
};

class cosmosType {
  public:
    string MIMEType;
    string moduleFilePath;

    // conformance tree
    list<cosmosType> parents;
    list<cosmosType> children;

    void locateModule();
    void loadModule();
};


class dcel {
  public:
    cosmosSystemObject cosmos;

    dcelService service;
    string address;

    list<cosmosType> types;

    list<dcel> children;

    cosmosType loadTypeModule(string type_name);

    dcel ( string serviceStr, string addrStr )
	    : service( serviceStr ),
	      address( addrStr ),
	      type( cosmosService::getMIMEType( addrStr ) {};
};

class hienaMap {
};


dcel hiena(dcel source) {


    conformanceTree subtree = source.getTypes();
	    // typeTree.findSubtreeWithType( type );
    
    /* map a single layer of hierarchy
        with multiple grammars
     */

    hienaMap *map;
   
    for ( auto curType : subtree ) {
        map = curType.mapper( source );
        if ( map != NULL )
            source.map += map;
    };

    /* recursive */

    for ( auto child : source.children ) {
        hiena( child );
    };

    return target;
}


int main(int argc, char *argv[]) {

    /* initialize global cosmos object */
    /* (some systemwide globals are stored
        in the dcel class static vars.)
     */

    cosmos_init();

    dcel url { argv[1] };

    /* overloaded op to type array:
        "url" will be located by cosmos_lookup()
     */
    url.type += "url";

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
