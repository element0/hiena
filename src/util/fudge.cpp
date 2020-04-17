/** @file furl.cpp
 *
 * Cosmos Project
 * fudge utility
 * 2020-04-17 rh
 *
 * Process a url using Fudge and return a stream.
 * Requires Services/fudge.
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



int main(int argc, char *argv[]) {

    if ( argc < 2 )
        return 0;
    
    dcel fudge( "fudge", argv[1] );

    string *result = fudge.str();

    return 0;
}

