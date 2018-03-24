
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





/**  snafu_vol

  @param  root_ino   snafufs maps ino "1" to root_ino in the cosmos_db

 */


struct snafu_vol {
        struct cosmos *cosmos_db;
        cosmos_id_t root_ino;
};


struct snafu_vol snafu_vol;





static void snafu_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
        (cosmos_id_t)ino;
        struct cosmos *cm;
        struct stat stbuf;

        cm = (struct cosmos *)fuse_req_userdata(req);

        memset(&stbuf, 0, sizeof(stbuf));


        if( ino == 1 )
                ino = snafu_vol.root_ino;


        if (cosmos_stat(cm, ino, &stbuf) == -1)
                fuse_reply_err(req, ENOENT);
        else
                fuse_reply_attr(req, &stbuf, 1.0);

}






static void snafu_lookup(fuse_req_t req, fuse_ino_t parent, const char *name)
{
        (cosmos_id_t)parent;
        struct fuse_entry_param e;
        cosmos_id_t ino;
        struct cosmos *cm;

        cm = (struct cosmos *)fuse_req_userdata(req);

        ino = cosmos_lookup(cm, parent, (char *)name);

        if (ino == 0)
        {
                fuse_reply_err(req, ENOENT);
                return;
        }



		memset(&e, 0, sizeof(e));

		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;

		cosmos_stat(cm, ino, &e.attr);

        if (ino == snafu_vol.root_ino) ino = 1;

		e.ino = (fuse_ino_t)ino;

		fuse_reply_entry(req, &e);

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
        (cosmos_id_t)ino;

        uint64_t dir;
        struct cosmos_dirent *e;
        struct dirbuf b;

        struct cosmos_dirh *dh;
        struct access_frame *af;
        
        memset(&b, 0, sizeof(b));




        if( ino == 1 ) ino = snafu_vol.root_ino;



        /*
        dh = fi->fh;
        */



        dh = cosmos_diropen(cm, ino);
        if( dh == NULL )
        {
                HIERR("snafu_readdir: err: dh NULL");

               return;
        }

        



        while((e = cosmos_readdir(dh)) != NULL)
        {
                dirbuf_add(req, &b, e->d_name, e->d_ino);

                cosmos_dirent_cleanup(e);
        }


        af = (struct access_frame *)ino;


        dirbuf_add(req, &b, ".", (ino_t)ino);
        dirbuf_add(req, &b, "..", (ino_t)(af->parent));

        reply_buf_limited(req, b.p, b.size, off, size);


        free(b.p);

        cosmos_closedir(dh);
}


static void snafu_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
        (cosmos_id_t)ino;

        void *fh;
        struct cosmos *cm;


        if (ino == 1)
                fuse_reply_err(req, EISDIR);

        else if ((fi->flags & 3) != O_RDONLY)
        {
                fuse_reply_err(req, EACCES);
                return;
        }



        cm = (struct cosmos *)fuse_req_userdata(req);

        fh = cosmos_open(cm, ino);

        fi->fh = (uint64_t)fh;

        fuse_reply_open(req, fi);
}


static void snafu_mknod(fuse_req_t req, fuse_ino_t par, const char *name, mode_t mode, dev_t rdev)
{
        (cosmos_id_t)par;

        struct fuse_entry_param e;
        struct cosmos *cm;
        cosmos_id_t ino;
        
        cm = (struct cosmos *)fuse_req_userdata(req);

        ino = cosmos_mknod(cm, par, (char *)name, mode, 0);


        if (ino == 0)
                fuse_reply_err(req, ENOENT);
        else
        {
		memset(&e, 0, sizeof(e));
		e.ino = (fuse_ino_t)ino;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		cosmos_stat(cm, ino, &e.attr);

		fuse_reply_entry(req, &e);
        }
}

 
static void snafu_mkdir(fuse_req_t req, fuse_ino_t par, const char *name, mode_t mode)
{
        (cosmos_id_t)par;

        struct fuse_entry_param e;
        struct cosmos *cm;
        cosmos_id_t ino;

        cm = (struct cosmos *)fuse_req_userdata(req);

        ino = cosmos_mkdir(cm, par, name, mode);



        if (ino == 0)
                fuse_reply_err(req, ENOENT);
        else
        {
		memset(&e, 0, sizeof(e));
		e.ino = (fuse_ino_t)ino;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		cosmos_stat(cm, ino, &e.attr);

		fuse_reply_entry(req, &e);
        }
}
   


static void snafu_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off, struct fuse_file_info *fi)
{
        void *buf;
        size_t size_read;
        cosmos_fh_t fh;

        if(fi == NULL)
        {
                HIERR("snafu_read: err: fi NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        fh = (cosmos_fh_t)fi->fh;
        
        if(fh == 0)
        {
                HIERR("snafu_read: err: FILE NULL");
                fuse_reply_err(req, EACCES);
                return;
        }

        size_read = cosmos_read(&buf, size, 1, fh);

        fuse_reply_buf(req, buf, size_read);

}






static struct cosmos *snafu_init(struct snafu_vol *snafu_vol, char *mountpoint)
{
        struct cosmos *cm;
        struct access_frame *root, *mount;

        int modc = 3;
        char *mod_path[] = {
            "/usr/lib/cosmos",
            "svc/file.so",
            "lookup/fudge.so",
        };



        cm = cosmos_init(modc, mod_path);

        snafu_vol->cosmos_db = cm;



        cmroot = cm->aframe;
        


        uroot = cosmos_simple_lookup(cm, cmroot, "demo@localhost");



        mount = cosmos_mkdir_path(cm, uroot, mountpoint, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );



        snafu_vol->root_ino = mount;



        cosmos_bind(cm, mount, "file", mountpoint);



        return cm;
}




static struct fuse_lowlevel_ops snafu_oper = {
	.lookup   = snafu_lookup,
	.getattr  = snafu_getattr,
	.readdir  = snafu_readdir,
	.open     = snafu_open,
	.read     = snafu_read,
         .mkdir  = snafu_mkdir,
         .mknod  = snafu_mknod,
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
