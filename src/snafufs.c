
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

#define FUSE_USE_VERSION 30

#include <fuse_lowlevel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "cosmos.h"
#include "hierr.h"
#include "access_frame.h"


/** TODO: snafu_vol
  @param root_ino snafufs translates ino "0" to this root_ino in the cosmos_db

 */
struct snafu_vol {
        cosmos_id_t root_ino;
        struct cosmos *cosmos_db;
};


struct snafu_vol snafu_vol;


static void snafu_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
        struct cosmos *cm;
	struct stat stbuf;

	memset(&stbuf, 0, sizeof(stbuf));

        cm = (struct cosmos *)fuse_req_userdata(req);



	if (cosmos_stat(cm, (cosmos_id_t)ino, &stbuf) == -1)
		fuse_reply_err(req, ENOENT);
	else
		fuse_reply_attr(req, &stbuf, 1.0);
}


static void snafu_lookup(fuse_req_t req, fuse_ino_t parent, const char *name)
{
        struct fuse_entry_param e;
        cosmos_id_t ino;
        struct cosmos *cm;

        cm = (struct cosmos *)fuse_req_userdata(req);

        ino = cosmos_lookup(cm, (cosmos_id_t)parent, (char *)name);

   if (ino == 0)
		fuse_reply_err(req, ENOENT);
	else {
		memset(&e, 0, sizeof(e));
		e.ino = (fuse_ino_t)ino;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		cosmos_stat(cm, (cosmos_id_t)(e.ino), &e.attr);

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

        while((e = cosmos_readdir( (cosmos_dirh_t)DIR )) != NULL)
        {
                dirbuf_add(req, &b, e->d_name, e->d_ino);
                free(e);
        }

        reply_buf_limited(req, b.p, b.size, off, size);

        free(b.p);
}


static void snafu_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
        void *FILE;
        struct cosmos *cm;
        
        cm = (struct cosmos *)fuse_req_userdata(req);

        FILE = cosmos_open( cm, (cosmos_id_t)ino );

        fi->fh = (uint64_t)FILE;

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
        size_t size_read;
        void *FILE;

        if(fi == NULL)
        {
                HIERR("snafu_read: err: fi NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        FILE = (void *)fi->fh;
        
        if(FILE == 0)
        {
                HIERR("snafu_read: err: FILE NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        size_read = cosmos_read(&buf, size, 1, (cosmos_fh_t)FILE);

        fuse_reply_buf(req, buf, size_read);

}



static struct cosmos *snafu_init(struct snafu_vol *snafu_vol, char *mountpoint)
{
        struct cosmos *cm;
        struct access_frame *root, *mount;
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

        root = cm->aframe;
        mount = cosmos_mknod(cm, root, mountpoint, S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);

        snafu_vol->root_ino = mount;
        snafu_vol->cosmos_db = cm;

        return cm;
}




static struct fuse_lowlevel_ops snafu_oper = {
	.lookup   = snafu_lookup,
	.getattr  = snafu_getattr,
	.readdir  = snafu_readdir,
	.open     = snafu_open,
	.read     = snafu_read,
};




int main(int argc, char *argv[])
{
        struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
        struct fuse_chan *ch;
        char *mountpoint;
        struct cosmos *cm;
	int err = -1;
        int cmdline_err;

        cmdline_err = fuse_parse_cmdline(&args, &mountpoint, NULL, NULL);
        
        cm = snafu_init(&snafu_vol, mountpoint);

	if ( cmdline_err != -1 &&
	    (ch = fuse_mount(mountpoint, &args)) != NULL) {
		struct fuse_session *se;

		se = fuse_lowlevel_new(&args, &snafu_oper,
				       sizeof(snafu_oper), (void *)cm);
		if (se != NULL) {
			if (fuse_set_signal_handlers(se) != -1) {
				fuse_session_add_chan(se, ch);

				/* Block until ctrl+c or fusermount -u */
				err = fuse_session_loop(se);

				fuse_remove_signal_handlers(se);
				fuse_session_remove_chan(ch);
			}
			fuse_session_destroy(se);
		}
		fuse_unmount(mountpoint, ch);
	}
	fuse_opt_free_args(&args);

	return err ? 1 : 0;
}
