
/**
  Hacked and slashed version of hello_ll.c fuse example
 */


/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

/** @file
 *
 * minimal example filesystem using low-level API
 *
 * Compile with:
 *
 *     gcc -Wall hello_ll.c `pkg-config fuse3 --cflags --libs` -o hello_ll
 *
 * ## Source code ##
 * \include hello_ll.c
 */

#define FUSE_USE_VERSION 31

#include <fuse_lowlevel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "cosmos.h"




static void snafu_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	struct stat stbuf;

	memset(&stbuf, 0, sizeof(stbuf));

	if (cosmos_stat(ino, &stbuf) == -1)
		fuse_reply_err(req, ENOENT);
	else
		fuse_reply_attr(req, &stbuf, 1.0);
}


static void snafu_lookup(fuse_req_t req, fuse_ino_t parent, const char *name)
{
	struct fuse_entry_param e;

   cosmos_id_t ino;

   ino = cosmos_lookup(parent, name);

   if (ino == 0)
		fuse_reply_err(req, ENOENT);
	else {
		memset(&e, 0, sizeof(e));
		e.ino = ino;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		cosmos_stat(e.ino, &e.attr);

		fuse_reply_entry(req, &e);
	}
}



struct dirbuf {
	char *p;
	size_t size;
};



static void dirbuf_add(fuse_req_t req, struct dirbuf *b, const char *name, fuse_ino_t ino)
{
	struct stat stbuf;
	size_t oldsize = b->size;
	b->size += fuse_add_direntry(req, NULL, 0, name, NULL, 0);
	b->p = (char *) realloc(b->p, b->size);
	memset(&stbuf, 0, sizeof(stbuf));
	stbuf.st_ino = ino;
	fuse_add_direntry(req, b->p + oldsize, b->size - oldsize, name, &stbuf, b->size);
}


#define min(x, y) ((x) < (y) ? (x) : (y))


static int reply_buf_limited(fuse_req_t req, const char *buf, size_t bufsize, off_t off, size_t maxsize)
{
	if (off < bufsize)
		return fuse_reply_buf(req, buf + off, min(bufsize - off, maxsize));
	else
		return fuse_reply_buf(req, NULL, 0);
}




static void snafu_readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off, struct fuse_file_info *fi)
{
        uint64_t DIR;
        struct dirent *e;

        DIR = fi->fh;
        if( DIR == 0 )
        {
                HIERR("snafu_readdir: err: DIR 0");
                fuse_reply_err(req,ENOTDIR);

                return;
        }

        struct dirbuf b;
        memset(&b, 0, sizeof(b));

        while((e = cosmos_readdir( DIR )) != NULL)
        {
                dirbuf_add(req, &b, e->name, e->ino);
                free(e);
        }

        reply_buf_limited(req, b.p, b.size, off, size);

        free(b.p);
}


static void snafu_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
        void *FILE;

        FILE = cosmos_open( ino );

        fi->fh = FILE;

        if (ino == 0)
                fuse_reply_err(req, EISDIR);

        else if ((fi->flags & 3) != O_RDONLY)
                fuse_reply_err(req, EACCES);

        else
                fuse_reply_open(req, fi);
}

   


static void snafu_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off, struct fuse_file_info *fi)
{
        void *buf;
        size_t len, size_read;
        void *FILE;

        if(fi == NULL)
        {
                HIERR("snafu_read: err: fi NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        FILE = fi->fh;
        
        if(FILE == 0)
        {
                HIERR("snafu_read: err: FILE NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        size_read = cosmos_read(&buf, size, 1, FILE);

        fuse_reply_buf(req, buf, size_read);

}




void *snafu_init(struct fuse_conn_info *conn, struct fuse_config *cfg)
{
        struct cosmos *cm;
        int modc = 6;

        char *mod_path[] = {
  "/usr/lib/cosmos",
  "/usr/lib/cosmos/svc/file.so",
  "/usr/lib/cosmos/svc/dylib.so",
  "/usr/lib/cosmos/svc/ptr.so",
  "/usr/lib/cosmos/xformr/dcelcosm.so",
  "/usr/lib/cosmos/lookup/fudge.so",

        };

        cm = cosmos_init(modc, mod_path);

        return (void *)cm;
}

static struct fuse_lowlevel_ops snafu_oper = {
	.lookup   = snafu_lookup,
	.getattr	= snafu_getattr,
	.readdir	= snafu_readdir,
	.open		= snafu_open,
	.read		= snafu_read,
	.init		= snafu_init,
};




int main(int argc, char *argv[])
{
	struct fuse_args args;
	struct fuse_session *se;
	struct fuse_cmdline_opts opts;
	int ret;

        args = FUSE_ARGS_INIT(argc, argv);
        ret = -1;


	if (fuse_parse_cmdline(&args, &opts) != 0)
		return 1;
	if (opts.show_help) {
		printf("usage: %s [options] <mountpoint>\n\n", argv[0]);
		fuse_cmdline_help();
		fuse_lowlevel_help();
		ret = 0;
		goto err_out1;
	} else if (opts.show_version) {
		printf("FUSE library version %s\n", fuse_pkgversion());
		fuse_lowlevel_version();
		ret = 0;
		goto err_out1;
	}

	se = fuse_session_new(&args, &snafu_oper, sizeof(snafu_oper), NULL);

	if (se == NULL)
	    goto err_out1;

	if (fuse_set_signal_handlers(se) != 0)
	    goto err_out2;

	if (fuse_session_mount(se, opts.mountpoint) != 0)
	    goto err_out3;

	fuse_daemonize(opts.foreground);

	/* Block until ctrl+c or fusermount -u */

	if (opts.singlethread)
		ret = fuse_session_loop(se);
	else
		ret = fuse_session_loop_mt(se, opts.clone_fd);

	fuse_session_unmount(se);
err_out3:
	fuse_remove_signal_handlers(se);
err_out2:
	fuse_session_destroy(se);
err_out1:
	free(opts.mountpoint);
	fuse_opt_free_args(&args);

	return ret ? 1 : 0;
}