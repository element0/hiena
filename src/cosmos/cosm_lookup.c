/** file @cosm_lookup.c
 *
 * Cosmos Project
 * Config directory cascade function
 * 2020-02-16 rh
 *
 * From the working directory, query each config directory up the tree for a matching subpath.
 *
 * e.g.:
 * 	cosm_lookup("sub/path/target.x", buf, len);
 *
 * 	printf("found %s\n", buf);
 *
 * if empty target, find the first config directory in or above PWD.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <glob.h>
#include <libgen.h> // XSI
#include <string.h>

#define CONFNAME_RE "[._][Cc]osm"

/* equivalent to shopt -s dotglob:
 * use glob() flag GLOB_PERIOD
 */



char *cosm_lookup(const char *subpath)
{
	size_t dir_len		= PATH_MAX;
	char  *startdir 	= malloc(sizeof(char)*dir_len);
	char  *globstr		= malloc(sizeof(char)*dir_len);
	size_t globstr_len;
	glob_t pglob;
	char *dir;
	char *target;
	char *retstr 		= NULL;
	size_t retstr_len 	= 0;

	if (getcwd(startdir, dir_len)==NULL) {
		fprintf(stderr,"cosm_lookup: cwd NULL, abort.");
		exit(-1);
	}

	dir = startdir;

	while ( strncmp(dir,"/",2) != 0 )
	{
		globstr_len = strlen(dir)
			+ strlen(CONFNAME_RE)
			+ strlen(subpath)+3;

		snprintf(globstr, globstr_len, "%s/%s/%s",
				dir, CONFNAME_RE, subpath); 

		glob(globstr, GLOB_PERIOD, NULL, &pglob);

		if(pglob.gl_pathc != 0)
			target = pglob.gl_pathv[0];
		else
			target = NULL;

		if(target != NULL)
		{
			retstr_len = strnlen(target, PATH_MAX)+1;
			retstr = malloc(sizeof(char)*retstr_len);
			strncpy(retstr, target, retstr_len);
			globfree(&pglob);
			break;

		}
		globfree(&pglob);
		dir = dirname(dir);
	}

	free(startdir);
	free(globstr);
	return retstr;
}

