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
#include "../cosmos/dcel.h"

using namespace std;
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

    string *uristring = url.field("uri");

    dcel base( "url", *uristring );

    string *urischeme = url.field("scheme");
    if(*urischeme == "http") {
        base.setType("HTML");
    }
    if(*urischeme == "sftp") {
        base.setType("HTML");
    }

    if ( argc > 2 ) {
        char *lookup_field = argv[2];
        string *return_field = base.field( lookup_field );

        if(return_field != NULL)
            cout << *return_field << endl;
       
        return 0;
    }
    return 0;
}

