// == TITLE: hpat.c == //
// -------- //


// == FORWARD DECLARATIONS: == //

typedef struct hiena_pattern_buffer Hpat;
Hpat *new_hpat();
Hpat *new_hpat_from_string(const char *);
int   cleanup_hpat(Hpat *);

// -------- //


typedef struct hiena_pattern_buffer
{
    void   *buf;
    size_t  len;
}Hpat;


Hpat *new_hpat()
{
    Hpat *hpat = malloc(sizeof(Hpat));
    hpat->buf  = NULL;
    hpat->len  = 0;
    return hpat;
};

Hpat *new_hpat_from_string(const char *str) {
    Hpat *hpat = new_hpat();
    hpat->len  = strlen(str);
    hpat->buf  = strndup(str, hpat->len);
    fprintf(stderr,"hiena:new_hpat_from_string:hpat->buf=%s\n",(char *)hpat->buf);
    return hpat;
}

Hpat *dupe_hpat(Hpat *pat1) {
    Hpat *pat2 = new_hpat();

    pat2->len = pat1->len;
    pat2->buf = malloc(pat2->len);
    memcpy(pat2->buf, pat1->buf, pat2->len);

    return pat2;
}

int compare_hpat(Hpat *pat1, Hpat *pat2) {
    if(pat1 == pat2)
	return 0;
    if(pat1 != NULL && pat2 != NULL) {
	if(pat1->buf != NULL && pat2->buf != NULL)
	    if(pat1->len == pat2->len)
		if(memcmp(pat1->buf, pat2->buf, pat1->len))
		    return 0;
    }
    return -1;  // failure
}

int cleanup_hpat(Hpat *hpat) {
    if (hpat != NULL) {
	memset(hpat->buf, 0, hpat->len);	// SECURITY: call me paranoid.
        free(hpat->buf);
        free(hpat);
    }
    return 0;
}

