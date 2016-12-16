

ssize_t dcel_sourcemod_read ( HIENA_DCEL_T d, void *buf, size_t count ) {
	if( d == HIENA_DCEL_T_NULL || buf == NULL || count == 0 ) return -1;

	ssize_t size_out = 0;
	size_t count_rem = count;

	while( size_out <= count ) {
		size_out = sm.read( addr, buf, count_rem );

		count_rem = count - size_out;
	}

	return size_out;
}
