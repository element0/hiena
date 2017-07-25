#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <fnmatch.h>
#include <string.h>
#include <sys/types.h>	/* for stat() */
#include <sys/stat.h>
#include <unistd.h>	/* for stat() */

#include "scanner.h"
#include "slib.h"



typedef struct hiena_scanner scannerserver;

typedef struct hiena_slib scanlib;



/**** SCANLIB MANAGEMENT ****/

struct hiena_slib *slib_create()
{
    struct hiena_slib *scanlib = malloc(sizeof(scanlib));

    scanlib->newest = NULL;

    return scanlib;
}


void slib_cleanup( struct hiena_slib *scanlib )
{
        /* cleanup scanner linked list */
        struct hiena_scanner *killscanner = NULL;
    while((killscanner=scanlib->newest)!=NULL) {
	fprintf(stderr,"hiena scanners subsystem closing: %s\n",killscanner->name);
	scanlib->newest = killscanner->prev;
	hiena_scanner_cleanup(killscanner);
    }

    free(scanlib);
}



void slib_print(scanlib *scanlib){
    scannerserver *curscanner = scanlib->newest;
    while(curscanner != NULL){
	printf("scanner: %s\t", curscanner->name);
	printf("dl: %p\n", curscanner->dl);
	curscanner = curscanner->prev;
    }

}


/* SCANNER LOOKUP */
/* TBD:
   the following on 6-15-2015 performs a first match wins scenario.

   an interesting side effect to this, is because the link list is
   pushed like a stack, the newest additions will be found.

   so if the searchpath is like one:two:three, the scanner in "three"
   will be found.

*/



struct hiena_scanner *slib_get_scanner(char *name, struct hiena_slib *scanlib)
{
    scannerserver *curscanner = scanlib->newest;
    while(curscanner != NULL){
	if(strcmp(name, curscanner->name)==0){
	    return curscanner;
	}
	curscanner = curscanner->prev;
    }
    return NULL;
}


scannerserver * slib_get_next_scanner( struct hiena_slib *slib, scannerserver *s)
{
    if(slib == NULL) {
	return NULL;
    }
    if(s==NULL) {
	return slib->newest;
    }
    return s->prev;	
}


scannerserver *
slib_new_scanner(scanlib *scanlib)
{
    scannerserver *newscanner = hiena_scanner_create();

    /* TBD check error */

    newscanner->prev   = scanlib->newest;

    scanlib->newest    = newscanner;

    return newscanner;
}


int slib_rm_scanner( scanlib *scanlib, scannerserver *rmthis)
{

    /* LINKED LIST VERSION */
    /* remove from linked list */

    if(scanlib==NULL)
    {
	/* no point in removing scanner from scanlib */
	/* we should assume this was a mistake
	   and not try to free "rmthis" */
	fprintf(stderr,"scanners_system: trying to remove scanner from NULL library.\n");
	return -1;
    }

    if(scanlib->newest==rmthis){
	if(rmthis->next==NULL){
	    /*then this is the only scanner in the library*/
	    /*blank out the list*/
	    scanlib->newest=NULL;
	}else{
	    /*shift the list upward*/
	    scanlib->newest=rmthis->next;
	}
    }else{
	/*remove the link and close the gap*/
	/*if next is NULL no biggy*/
    	rmthis->prev->next=rmthis->next;
    }

    /*cleanup the bugger*/
    hiena_scanner_cleanup(rmthis);

    return 0;
}


static int slib_scandir_filter(const struct dirent *de)
{
    return !fnmatch("*.so", de->d_name,0);
}


void *wrap_dlsym(void *dl, const char *symbol, int *errc)
{
    void *func = dlsym(dl,symbol);
    char *err  = dlerror();
    if(err != NULL)
    {
	fprintf(stderr, "libhiena:sslib: %s\n", err);
	if(errc != NULL)
	{
	    (*errc)++;
	}
	return NULL;
    }
    return func;
}

scanlib *
slib_load_dir(char *fpath, scanlib *scanlib)
{
    void *dl;
    char *dlerr, *newstring;
    char *chop_point;
    int dlerrcount, n;
    int strlen1, strlen2;
    int *compiler_version_ptr;
    struct dirent **namelist;
    int *name_str_dim_ptr;
    scannerserver *newscanner;

    if(scanlib == NULL)
	     scanlib = slib_create();

    dl = NULL;
    dlerr = NULL;
    dlerrcount = 0;

    /* look in fpath
       for SCANNER_SO_SUFFIX
       shared object files */

    strlen1 = strlen(fpath);
    strlen2 = 0;
    newstring = NULL;
    namelist = NULL;

    n = scandir(fpath, &namelist, slib_scandir_filter, alphasort);

    if (n < 0)
        perror("scandir");

    else {
        chop_point = NULL;
        compiler_version_ptr = NULL;

        while (n--)
        {
	    /* got a match... */
	    /* prepare the filename of 
          the shared object file */

            strlen2 = strlen(namelist[n]->d_name);

            newstring = malloc(sizeof(char)*(strlen1+strlen2+2));

            strncpy(newstring, fpath, strlen1);

	    /* strncpy() may not add a null byte... */

	    newstring[strlen1] = '\0';

	    strncat(newstring,"/",1);
	    strncat(newstring, namelist[n]->d_name, strlen2);
	    
	    /* get a new scannerserver holding object */

	    newscanner = slib_new_scanner(scanlib);
	    
	    /* INIT SCANNER VARS */

	    newscanner->name = strndup(namelist[n]->d_name,strlen2);

	    /* chop ".so" off the end */
	    if(newscanner->name!=NULL){
	        chop_point = newscanner->name+strlen2-3;
		*chop_point='\0';
	    }

	    /* check to see if we've already loaded an identical scannerserver */
	    /* if so, link to the already loaded one */
	    /* TBD */
	    
	    /* else, */
	    /* dlopen the scannerserver and save in the holding object */
	   
	    /*clear dlerror*/
	    //dlerror();

	    dl = dlopen(newstring, RTLD_LAZY);

	    //dlerr = dlerror();

	    if (dl==NULL)
        {
		fprintf(stderr,
		"hiena scanners_system can't load %s: %s\n",newstring, dlerr);
		goto abort;
	    }

	    /* INITIALIZE SCANNER DYLIB  */
	    newscanner->dl = dl;


	    /* INITIALIZE FUNCTION POINTERS */

	    /* load it's symbols into our scannerserver holding object */

	    /*clear dlerror*/
	    //dlerror();

	    compiler_version_ptr = (int *)dlsym(dl,"compiler_version"); 

	    //dlerr=dlerror();

	    if(compiler_version_ptr==NULL)
{

		/* older compiled scanners 
          during development
		   did not have a 
        "compiler_version" symbol */

		newscanner->compiler_version = 0;
	    }else{
	        newscanner->compiler_version = *compiler_version_ptr;
	    }


	    /* MULTIPLE COMPILER VERSIONS SUPPORTED */
	    /* ==================================== */

	    /* It's simple to leave the original development version
	       of scannerserver .so files in play because we've added
	       a check for compiler_version.
	       (version ascends in whole numbers from 1) */

	    dlerrcount=0;

	    switch(newscanner->compiler_version)
        {
		case 0:

		    /* NOTE:  at one point during development
		       running dlerror() gave errors in valgrind
		       when the project was linked with libfuse.
		     */

		    dlerror();

		    /* TBD: This symbol name is evolving... */
		    /* hiena_scannerop_parse may be renamed */


		    newscanner->op->parse
			= (int (*)(Hsp *))wrap_dlsym(dl, "hiena_scannerop_parse",
				&dlerrcount);

//----------

		    dlerror();
		    newscanner->op->show_allowed_child_scanners
		      =(char **(*)())wrap_dlsym(dl,"show_allowed_child_scanners",
			        &dlerrcount);

		    dlerror();
		    newscanner->op->get_tok_name
			= (char *(*)(int))wrap_dlsym(dl, "get_tok_name",
				&dlerrcount);

		    dlerror();
		    newscanner->op->yyparse
			= (int (*)(yyscan_t *, Hsp *))wrap_dlsym(dl, "yyparse",
				&dlerrcount);

		    dlerror();
		    newscanner->op->yylex_init_extra
			= (int (*)(Hsp *, yyscan_t *))wrap_dlsym(dl, "yylex_init_extra",
				&dlerrcount);

		    dlerror();
		    newscanner->op->yylex_destroy
			= (int (*)(yyscan_t *))wrap_dlsym(dl, "yylex_destroy",
				&dlerrcount);

		    dlerror();
		    newscanner->op->yyset_in
			= (void (*)(struct dcel_fh *, yyscan_t *))wrap_dlsym(dl, "yyset_in",
				&dlerrcount);

		    dlerror();
		    newscanner->op->yyget_in
			= (struct dcel_fh *(*)(yyscan_t *))wrap_dlsym(dl, "yyget_in",
				&dlerrcount);


		    /* if error count is equal to the number of symbols
		       in hiena_scannerserver_ops, then none have loaded. */

		    if(dlerrcount == HIENA_SCANNER_SVC_OPS_COUNT)
        {
			/* three strikes */

			dlerror();

			if(dlclose(dl)!=0)
			    dlerr=dlerror();
			    fprintf(stderr,"dlclose err %s\n",dlerr);
			goto abort;
		    }

		    break;

		/*COMPILER VERSION 1: LOAD SCANNER*/
		case 1:
		    //dlerror();
		    name_str_dim_ptr = (int *)dlsym(dl, "name_str_dim");

		    //dlerr=dlerror();

		    if(name_str_dim_ptr==NULL){
			dlerrcount++;
			newscanner->name_str_dim=0;
			/* name_str not searchable */
		    }else{
		        newscanner->name_str_dim = *name_str_dim_ptr;
		    }

		    //dlerror();

		    newscanner->name_str
			= (char **)dlsym(dl,"name_str");
		    //dlerr=dlerror();
		    if(newscanner->name_str==NULL){
			dlerrcount++;
			newscanner->name_str=NULL; /* precaution */
			/* human readable names not available */
		    }

		    //dlerror();
		    newscanner->name_table
			=(int *)dlsym(dl,"name_table");
		    //dlerr=dlerror();
		    if(newscanner->name_table==NULL){
			dlerrcount++;
			newscanner->name_table=NULL; /* precaution */
			/* without a name_table, unusable */
			fprintf(stderr,
			"hiena can't load version 1 scanner name_table\n");
			//dlerror();
			if(dlclose(dl)!=0){
			    //dlerr=dlerror();
			    fprintf(stderr,"dlclose err %s\n",dlerr);
			}
			goto abort;
		    }

		    //dlerror();
		    newscanner->fsm_table
			=(int *)dlsym(dl,"fsm_table");
		    //dlerr=dlerror();
		    if(newscanner->fsm_table==NULL){
			dlerrcount++;
			newscanner->fsm_table=NULL; /* precaution */
			/* without a fsm_table, unusable */
			fprintf(stderr,
			"hiena can't load version 1 scanner fsm_table\n");
			goto abort;
		    }

		    break;
	    }


	    fprintf(stderr,"hiena scanners subsystem loaded: %s\n", newscanner->name);


	    goto cleanup;
	    /* skipping abort */
abort:
	    fprintf(stderr,"hiena scanners subsystem failed: %s\n", newscanner->name);
	    slib_rm_scanner(scanlib,newscanner);

cleanup:
            free(newstring);
	    free(namelist[n]);
	}
	free(namelist);
	// dlclose(dl); //<----- WHAT?
    }

    return scanlib;
}



scanlib *
slib_load_path(const char *SCANNERPATH) {

    /* So this is the first scanner library function that is called.
       It's supposed to set up the entire scanner library.

       Two thoughts,
       1) the scanner library should be daemonized
       2) scanner lookup should be efficient,
       		how about a B tree?

       */
    scanlib *slib_scanners = slib_create();

    /* LOAD SCANNERS */
    /* look through SCANNERPATH locations
       to find scanner so files.
    */
    char *pathstr = strdup(SCANNERPATH);
    char *pathstr_cleanup_handle = pathstr;
    char *current_path;
    char *strtoksave;
    /*
    int  strlen1, strlen2=strlen(SCAN_LIB_DIR_NAME);
    char *homedir = getenv("HOME");
    int  strlen3=strlen(homedir);
    char *newstring;
    */

    struct stat sbuf;

    while( (current_path = strtok_r(pathstr,":",&strtoksave)) != NULL)
    {
	pathstr=NULL; /* required by strtok_r */

	/*
	// append SCAN_LIB_DIR_NAME 
	strlen1 = strlen(current_path);
	if(current_path[0]=='~'){
	    newstring = malloc(sizeof(char)*(strlen1-1+strlen2+strlen3+3+1));
	    strcpy(newstring,homedir);
	    strncat(newstring,++current_path,strlen1-1);
	}else{
	    newstring = malloc(sizeof(char)*(strlen1+strlen2+2+1));
	    strcpy(newstring,current_path);
	}
	strncat(newstring,"/",1);
	strncat(newstring,SCAN_LIB_DIR_NAME,strlen2);

slin mm	
	// test for existance
	if ( stat(newstring, &sbuf) != -1 ) {
	    slib_load_dir(newstring, slib_scanners);
	}
	// cleanup
	free(newstring);
	*/
	// test for existance
	
	if ( stat(current_path, &sbuf) != -1 ) {
	    slib_load_dir(current_path, slib_scanners);
	}

    }
    free(pathstr_cleanup_handle);

    return slib_scanners;
}
