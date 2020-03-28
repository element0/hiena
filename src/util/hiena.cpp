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
#include <sstream>
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


#include "../cosmos/dcel.h"

using namespace Cosmos;


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





int main(int argc, char *argv[]) {

    if ( argc < 2 )
        return 0;
    
    dcel url( argv[1] );
    url.setType( "url" );
    url.makeMap();


    if ( argc > 2 ) {
        char *lookup_field = argv[2];
        string *return_field = url.field( lookup_field );

        if(return_field != NULL)
            cout << *return_field << endl;

        return 0;
    }

    string *hello_test = url.field("uri");
    cout << *hello_test << endl;


/*
    string *scheme_field = url.field("scheme");
    string *address_field = url.field("address");
    // dcel source( *scheme_field, *address_field );
    hiena( source );
*/
    return 0;
}

