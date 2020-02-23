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
	char  *dir;
	size_t dir_len;
	char  *globstr;
	size_t globstr_len;
	glob_t pglob;
	char *target;
	char *retstr;
	size_t retstr_len;

	dir_len = PATH_MAX;
	dir = malloc(sizeof(char)*dir_len);

	if (getcwd(dir, dir_len)==NULL) {
		fprintf(stderr,"cosm_lookup: cwd NULL, abort.");
		exit(-1);
	}

	globstr = malloc(sizeof(char)*PATH_MAX);

	while ( strncmp(dir,"/",2) != 0 )
	{
		target = NULL;
		globstr_len = strlen(dir)
			+ strlen(CONFNAME_RE)
			+ strlen(subpath)+3;

		/* target = */
		snprintf(globstr, globstr_len, "%s/%s/%s",
				dir, CONFNAME_RE, subpath); 

		glob(globstr, GLOB_PERIOD, NULL, &pglob);

		if(pglob.gl_pathc != 0)
			target = pglob.gl_pathv[0];

		if(target != NULL) // todo: check if exits
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

	free(dir);
	free(globstr);
	return retstr;
}

