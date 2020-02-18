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

#include "antlr4-runtime.h"

#include "cosmos.h"  // string db, global cosmos

#include "cosmosLexer.h"
#include "cosmosParser.h"

using namespace antlr4;
using namespace std;


dcel hiena(dcel source) {

    cosmosType type { source.service.getMIMEType( source.address ) };

    conformanceSubtree = conformanceTree.findSubtreeWithType( type );
    
    /* map a single layer of hierarchy
        with multiple grammars
     */
    for ( type : conformanceSubtree ) {
        map = type.mapper( source );
        if ( map != NULL )
            source.map += map;
    }

    /* recursive */
    for ( child : source.children ) {
        hiena( child );
    }

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
      / * return a map as part of the dcel */
}
