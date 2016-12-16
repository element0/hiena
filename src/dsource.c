
#define HIENA_DSOURCE_T struct hiena_dsource *

struct hiena_dsource {
	void *addr;
	void *sourcemod;
};

ssize_t hiena_dsource_read ( HIENA_DSOURCE_T s, void *buf, size_t count ) {
	if( s == NULL ||  buf == NULL || count == 0 ) return -1;

	SOURCEMOD_T  sm = hiena_dsource_get_sourcemod( s );
	SOURCEADDR_T sa = hiena_dsource_get_addr( s );

	ssize_t size_out = 0;
	size_t count_rem = count;

	while( size_out <= count ) {
		if ((size_out = sm.read( sa, buf, count_rem )) == -1 )
			return -1;

		count_rem = count - size_out;
	}

	return size_out;
}
