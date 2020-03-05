
/** @file dcel.h
 *
 * Cosmos Project
 * hiena utility
 * 2020-03-04 rh
 *
 * dcel
 */

#pragma once

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

namespace Cosmos {

class hienaMap;
class dcel;

class cosmosType {
  public:
    string MIMEType;
    string type_name;

    string moduleMapperPath;
    void *mapper_dl;
    dcel *(*mapper_fn)(istream &);

    list<cosmosType> superTypes;
    list<cosmosType> subTypes;

    cosmosType( string );

    void loadModule();
    void set_type_name( string );
};

class cosmosService {
  public:
    string name;

    cosmosService( string address );

    string getMIMEType( string address );
    istringstream & open( string address );
};



class cosmosSystemObject {
  public:
    cosmosType typeTree;
    map<string, cosmosType> typeModules;
    map<string, cosmosService> serviceModules;

    cosmosSystemObject();
    cosmosService getServiceModule( string );
    string testStr();
};


class dcel {
  public:
    // static cosmosSystemObject cosmos;

    cosmosService service;
    string address;
    cosmosType type;

    // alternative as if:
    // service="Cosmos::dcel", address=dcelPointer
    dcel *dcelBacking;

    list<cosmosType*> types;
    list<dcel> children;
    multimap<string,dcel *> fields;

    // map field
    // string name;
    int start;
    int stop;
    dcel *addField();
    dcel *addField(string,int,int);
    dcel *enter();
    dcel *exit();
    string field( string fieldName );

    dcel( string );
    dcel( string serviceStr, string addrStr );
    dcel( dcel *source );

    void addType( string type_name );
    void setType( string type_name );
    void makeMap() ;

};

}
