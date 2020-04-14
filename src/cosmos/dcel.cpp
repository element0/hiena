/** @file dcel.cpp
 *
 * Cosmos Project
 * hiena utility
 * 2020-03-02 rh
 *
 * dcel methods
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <list>
#include <map>
#include <stack>
#include "dcel.h"

extern "C" {
#include "cosm_lookup.h"
#include <dlfcn.h>
#include "cosmos_service_func_block.h"
}

using namespace std;

namespace Cosmos {


    /***************************************/
    /* --- initialize global cosmos object */
    /***************************************/

    cosmosSystemObject cosmos;


    /********************/
    /* --- cosmosModule */
    /********************/

    // abstract type



    /******************/
    /* --- cosmosType */
    /******************/


    cosmosType::cosmosType( string cosmos_typename = "" )
	    : MIMEType{ cosmos_typename } {
	name = cosmos_typename;
    }

    void cosmosType::initModule() {
	if( module_dl == NULL ) {
	    return;
	}

	mapper_fn = (dcel *(*)(istream *))dlsym( module_dl, "mapper" );

    }


    /*************************/
    /* --- dcel_streambuf    */
    /*************************/


    dcel_streambuf::dcel_streambuf(dcel *dc)
    : source( dc ) {

        const char *address = dc->address.c_str();
        auto openfn = dc->service->ops->fopen;
        handle = openfn( address, "r" );
    }


    dcel_streambuf::~dcel_streambuf() {

        if(source && source->service && source->service->ops ) {
            auto closefn = source->service->ops->fclose;
            closefn( handle );
        }
    }

    int dcel_streambuf::underflow()  {

        auto readfn = source->service->ops->fread;
        char c[2];
        size_t n;

        c[1] = '\0';

        n = readfn( &c, 1, 1, handle );
        if(n) {
            // cout << c;
            return (int)c[0];
        }

        // cout << "dcel_streambuf::underflow() called" << endl;

        return EOF;
    }


    int dcel_streambuf::uflow()  {

        int i = 1;
        // cout << "dcel_streambuf::uflow() called." << endl;

        return EOF;
    }


    int dcel_streambuf::pbackfail(int ch)  {

        // cout << "dcel_streambuf::pbackfail() called." << endl;

        return 0;
    }

    std::streamsize dcel_streambuf::showmanyc()  {

        // cout << "dcel_streambuf::showmanyc() called." << endl;

        return 0;
    }



    streampos dcel_streambuf::seekpos( streampos sp, ios_base::openmode which) {

        // cout << "dcel_streambuf::seekpos( " << sp << " ) called." << endl;

        auto seekofn = source->service->ops->fseeko;

        off_t pos = sp;

        streampos ret = seekofn( handle, sp, SEEK_SET );

        // cout << "dcel_streambuf::seekpos(): seekofn() returned: " << ret << endl;
        
        return ret;
    }



    /*********************/
    /* --- cosmosService */
    /*********************/

    string cosmosService::getMIMEType( string address ) {
        return "not implemented";
    }
    
    istream * cosmosService::open( string address ) {
        if (name == "std::string") {
            istringstream *iss = new istringstream(address);
            return (istream *)iss;
        }
    }



    istream * cosmosService::open( dcel *dc ) {
        if (ops == NULL)
            return NULL;

        istream * is = new istream(new dcel_streambuf(dc));

        return is;
    }



    void cosmosService::close( istream *is ) {
        if(!is)
            return;

        dcel_streambuf *dsb = (dcel_streambuf *)is->rdbuf();

        if( dsb && dsb->handle ) {
            if( ops ) {
                ops->fclose(dsb->handle);
            }
        }

        delete is;
    }


    ostringstream & cosmosService::asOstringstream(string address) {
        if (name == "std::string") {
            ostringstream *s = new ostringstream(address);
            return *s;
        }
    }

    cosmosService::cosmosService( string newName ) {
        name = newName;
        module_dl = NULL;
    }


    void cosmosService::initModule() {

        if( module_dl == NULL ) {
            ops = NULL;
            return;
        }

        ops = (cosmos_service_func_block *)dlsym( module_dl, "cosmos_service_ops" );

    }




    /*************************/
    /*--- cosmosSystemObject */
    /*************************/


    void *cosmosSystemObject::loadModule( string moduleSOFullPath ) {

        if( moduleSOFullPath.empty() )
            return NULL;

        void *module_dl = dlopen( moduleSOFullPath.c_str(), RTLD_NOW );

        const char *err = dlerror();
        if( err != NULL ) {
            cerr<<"error:"<<err<<endl;
            module_dl = NULL;
        }

        return module_dl;
    }





    cosmosService * cosmosSystemObject::getService(string svc) {

        if( svc.empty() )
            return NULL;

        string moduleSoRelpath = servicedir_name + "/" + svc + "/lib/service.so";

        const char *moduleSoFullPath = cosm_lookup( moduleSoRelpath.c_str() );

        cosmosService *res;
	const char *moduleID = moduleSoFullPath;
        if( moduleID == NULL )
	    moduleID = svc.c_str();

        auto it = serviceModules.find( moduleID );
        if( it != serviceModules.end() ) {
            res = it->second;
            return res;
        } else if( moduleSoFullPath == NULL ){
            return NULL;
        }

        res = new cosmosService( svc );

        res->module_dl = loadModule( moduleSoFullPath );

        res->initModule();

        serviceModules[moduleSoFullPath] = res;
        modules[moduleSoFullPath] = res;

        return res;
    }


    cosmosType * cosmosSystemObject::getType( string typ ) {

        if( typ.empty() )
            return NULL;

        cosmosType *res;

        string moduleSoRelpath = typedir_name + "/" + typ + "/lib/mapper.so";

        const char *moduleSoFullPath = cosm_lookup( moduleSoRelpath.c_str() );

        if( moduleSoFullPath == NULL )
            return NULL;

        auto it = typeModules.find( moduleSoFullPath );
        if( it != typeModules.end() ) {
            res = it->second;
            return res;
        }

        res = new cosmosType( typ );
        res->module_dl = loadModule( moduleSoFullPath );

        res->initModule();

        typeModules[moduleSoFullPath] = res;
        modules[moduleSoFullPath] = res;

        return res;
    }


    cosmosSystemObject::cosmosSystemObject() {
        metadir_re = "[._][Cc]osm";
        typedir_name = "Types";
        servicedir_name = "Services";

	// BUILTINS

	auto builtinStdString = new cosmosService( "std::string" );

	serviceModules["std::string"] = builtinStdString;
    }


    /***********/
    /*--- dcel */
    /***********/


    dcel::dcel( string stringBacking = "" ) {
        service = cosmos.getService("std::string");
        address = stringBacking;
    }



    dcel::dcel( string svc, string addr ) {
        service = cosmos.getService( svc );
        address = addr;
    }



    void dcel::addType( string type_name ) {
        types.push_back( cosmos.getType( type_name ));
    }



    void dcel::setType( string type_name ) {
        type = cosmos.getType( type_name );
    }





    string *dcel::str() {
        if( service->name == "std::string" ) {
            auto value = new string(address);
            return value;
        }
        return NULL;
    }


    string *dcel::str(size_t startpos, size_t stoppos) {
        istream *stream;

        size_t len = stoppos - startpos + 1;

        if( service->name == "std::string" ) {
            stream = service->open( address );
        } else {
            stream = service->open( this );
        }

        stream->seekg(startpos);

        // working...


        string whole((istreambuf_iterator<char>(*stream)), istreambuf_iterator<char>());
        
        string *result = new string(whole, startpos, len);
        /*

        char *buffer = new char[len+1];
        string *result;
        if(stream->read(buffer, len)) {
            buffer[len] = '\0';
            result = new string(buffer);
        }else{
            delete buffer;
            result = NULL;
        }
        */

        service->close( stream );
        return result;
    }


    void dcel::fieldWalk( stack<dcel *> *level, multimap<string, dcel *> *result, string searchExpr ) {
        for (auto field : level->top()->fields ) {
            if(field.first == searchExpr )
                result->insert(field);

            level->push( field.second );
            fieldWalk( level, result, searchExpr );
            level->pop();
        }
    }

    
    multimap<string, dcel *> *dcel::fieldMatch( string fieldName ) {
        multimap<string, dcel *> *result = new multimap<string, dcel *>();
        stack<dcel *> level;
        level.push( this );
	
        while ( ! level.empty() ) {
            fieldWalk( &level, result, fieldName );
            level.pop();
        }

        return result;
    }




    string *dcel::field( string fieldName ) {

        multimap<string, dcel *> *matchlist = fieldMatch( fieldName );
        if(!matchlist->empty()) {
            dcel *field = matchlist->begin()->second;

            // cout << "dcel::field(string): field->start: " << field->start << endl;
            // cout << "dcel::field(string): field->stop: " << field->stop << endl;

            string *result = str(field->start, field->stop);
  
            // if(result == NULL)
                // cout << "dcel::field(string): couldn't read field." << endl;

            return result;
        }
        return NULL;
    }



    dcel *dcel::addField() {
        return new dcel("");
    }

    dcel *dcel::addField(string name, int start, int stop) {
        dcel *newField = new dcel();
        newField->dcelBacking = dcelBacking;
        newField->start = start;
        newField->stop = stop;

       newField->superField = this;

        fields.insert(pair<string,dcel *>(name,newField));

        return newField;
    }

    dcel *dcel::enter() {
        return this;
    }

    dcel *dcel::exit() {
        return superField;
    }



    void dcel::makeMap() {

        istream * stream;

        if( service->name == "std::string" )
            stream = (istream *)service->open( address );
        else
            stream = (istream *)service->open(this);

        dcel *map = type->mapper_fn(stream);

        // delete this
        map->dcelBacking = this;
	
        fields.insert(pair<string,dcel *>(type->name, map));

        service->close( stream );

    }
}


