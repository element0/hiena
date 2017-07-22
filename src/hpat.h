

#ifndef _HIENA_HPAT_H_
#define _HIENA_HPAT_H_

typedef struct hiena_pattern_buffer Hpat;

int hpat_is_c_string(Hpat *);

Hpat *new_hpat_from_str(const char *);


/* == TITLE: hpat.h == */
/* -------- */
typedef struct hiena_pattern_buffer
{
    void   *buf;
    size_t  len;
}Hpat;



Hpat *new_hpat();
Hpat *new_hpat_from_string(const char *);
Hpat *new_hpat_from_argv(int, char **);
Hpat *dupe_hpat(Hpat *);
int   compare_hpat(Hpat *, Hpat *);
int   cleanup_hpat(Hpat *);

/* These should replace the above.
   */
Hpat *hpat_create();
Hpat *hpat_from_str(const char *);
Hpat *hpat_from_argv(int, char **);
char *hpat_str_ptr(Hpat *);
Hpat *hpat_dupe(Hpat *);
int   hpat_cmp(Hpat *, Hpat*);
FILE *hpat_fopen(Hpat *, char *);
int   hpat_cleanup(Hpat *);



#endif /*!_HIENA_HPAT_H_*/
