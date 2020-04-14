
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
#include <streambuf>
#include <string>
#include <list>
#include <map>
#include <stack>

extern "C" {
#include "cosm_lookup.h"
#include <dlfcn.h>
#include "cosmos_service_func_block.h"
}

using namespace std;

namespace Cosmos {


class hienaMap;
class dcel;


class cosmosModule {
  public:
    string name;
    void *module_dl;
};



class cosmosType : public cosmosModule {
  public:
    string MIMEType;
    list<cosmosType> superTypes;
    list<cosmosType> subTypes;


    // module init
    void initModule();

    // module ops
    dcel *(*mapper_fn)(istream *);

    cosmosType( string typeName );
    cosmosType( void *dl );
};



class cosmosService : public cosmosModule {
  public:
    string getMIMEType( string address );

    struct cosmos_service_func_block *ops;

    ostringstream & asOstringstream( string address );
    istream * open( string address );
    istream * open( dcel * );

    void close( istream * );

    void initModule();

    cosmosService( string address );
};



class dcel_streambuf : public std::streambuf {
  public:
            dcel_streambuf(dcel *);
           ~dcel_streambuf();
    void * handle;

  private:
    virtual int_type underflow() override;
    virtual int_type uflow() override;
    virtual int_type pbackfail(int_type ch) override;
    virtual std::streamsize showmanyc() override;
    virtual streampos seekpos( streampos sp, ios_base::openmode which) override;

    const char * begin_;
    const char * end_;
    const char * current_;

    cosmosService * svc;
    dcel * source;
};


/** cosmosSystemObject
 *
 *  - global config of cosmos system.
 *  - global cache of all cosms encountered
 *    by cosm_lookup.
 *  
 *    cache is file-system-like. each cached
 *    asset is mapped by filepath.
 *    convenience indices map filepaths to
 *    asset types.
 *
 *    eg:
 *    {
 *      "~/_Cosm/Types/url/lib/mapper.so",
 *      dylib ptr
 *    }
 *
 */  

class cosmosSystemObject {
  public:
    // config
    string metadir_re;
    string typedir_name;
    string servicedir_name;

    cosmosType typeTree;
    map<string, cosmosType *> typeModules;
    map<string, cosmosService *> serviceModules;
    map<string, cosmosModule *> modules;

    cosmosSystemObject();
    void * loadModule( string );
    cosmosModule * getModule( string );
    cosmosService * getService( string );
    cosmosType * getType( string );
};




class dcel {
  private:
    void fieldWalk( stack<dcel *> *, multimap<string, dcel *> *, string );

  public:
    cosmosService *service;
    string address;
    cosmosType *type;

    // alternative:
    // service="Cosmos::dcel", address=dcelPointer
    // remove this. just 
    dcel *dcelBacking = NULL;

    list<cosmosType*> types;
    list<dcel> children;
    multimap<string,dcel *> fields;

    // map field
    // string name;
    int start;
    int stop;
    dcel *superField;
    dcel *addField();
    dcel *addField(string,int,int);
    dcel *enter();
    dcel *exit();
    multimap<string, dcel *> *fieldMatch( string fieldName );
    string *field( string fieldName );

    string *str();
    string *str(size_t startpos, size_t stoppos);

    dcel( string );
    dcel( string serviceStr, string addrStr );
    dcel( dcel *source );

    void addType( string type_name );
    void setType( string type_name );
    void makeMap() ;

};

}
