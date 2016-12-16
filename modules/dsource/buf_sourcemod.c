#include <string.h>

struct buf_sourcemod_addr {
	void   *buf;
	size_t *len;
};


ssize_t buf_sourcemod_read ( void *addr, void *buf, size_t count ) {
	if( addr == NULL || outbuf == NULL || count == 0 ) return 0;

	struct buf_sourcemod_addr *ba = addr;
	memcpy( buf, ba->buf,  );

	return count;
}
