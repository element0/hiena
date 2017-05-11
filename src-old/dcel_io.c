

struct hiena_dcel_io {
	void *dcel;
	void *ops;
};


ssize_t hiena_dcel_io_read ( HIENA_DCEL_IO_T dio, void *buf, size_t count ) {
	if( dio == NULL || buf == NULL || count == 0 ) return -1;

	HIENA_DCEL_T   d = hiena_dcel_io_get_dcel( dio );
	HIENA_SOURCE_T s = hiena_dcel_get_source( d );
	HIENA_FILTER_T f = hiena_dcel_get_filter( d );

	ssize_t size_in, size_out, size_read;
	size_t count_rem = count;

	while( size_out <= count ) {
		if ((size_read = s.read( s, inbuf, count_rem )) == -1 )
			return -1;
		size_in  =+ size_read;

		if ((size_read = f.filter( inbuf, buf, count_rem )) == -1 )
			return -1;
		size_out =+ size_read 
		
		count_rem = count - size_out;
	}

	return size_out;
}
