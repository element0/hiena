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
#include <string>
#include <list>
#include <map>
#include <stack>
#include "dcel.h"

extern "C" {
#include "cosm_lookup.h" // requires 'libcosmos'
#include <dlfcn.h>
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

    void cosmosType::moduleInit() {
	if( module_dl == NULL ) {
	    return;
	}

	mapper_fn = (dcel *(*)(istream &))dlsym( module_dl, "mapper" );

    }



    /*********************/
    /* --- cosmosService */
    /*********************/

    string cosmosService::getMIMEType( string address ) {
	return "not implemented";
    }
    
    istringstream & cosmosService::open( string address ) {
	if (name == "std::string") {
	    istringstream *s = new istringstream(address);
	    return *s;
        }
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
        } else if( moduleSoFullPath == NULL ) {
	    return NULL;
	}

        res = new cosmosService( svc );

        res->module_dl = loadModule( moduleSoFullPath );

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

	res->moduleInit();

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
    }


    string *dcel::str(int startpos, int stoppos) {
        int len = stoppos - startpos + 1;

        istringstream & stream = service->open( address );
        stream.seekg(startpos);

        char *buffer = new char[len+1];
        stream.read(buffer, len);
        buffer[len] = '\0';

        string *result = new string(buffer);
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
	    string *result = str(field->start, field->stop);
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

	istringstream & stream = service->open( address );

	dcel *map = type->mapper_fn((istream &)stream);

	// delete this
        map->dcelBacking = this;
	
	fields.insert(pair<string,dcel *>(type->name, map));
    }
}


