#include "limits.h"
#include "access_frame.h"

/* access frame paths */




struct access_frame *aframe_mkpathstr(struct cosmos *cm, struct access_frame *af, int segc, char *segv)
{
        struct access_frame *res;
        char *pathstr, *cur;
        size_t pathlen, len, buflen;
        size_t rlen;
        const size_t bufmax = PATH_MAX - 1;
        va_list ap;
        int er = NULL;


        buf = malloc(PATH_MAX);
        buflen = 0;

        va_start(ap, init);
        for(i = 0; i < (argc-1); i++)
        {
            cur = va_arg(ap, char *);
            if(cur == NULL)
            {
                HIERR("aframe_vpath: va_arg() NULL");
                er++;
                break;
            }

            len = strnlen(cur, PATH_MAX);
            if(len > bufmax)
            {
                HIERR("aframe_vpath: path segment length exceeds bufmax");
                HIERR(cur);
            }
            rlen = bufmax - buflen;
            if( len >= rlen )
            {
                HIERR("aframe_vpath: pathstr will exceed PATH_MAX");
                HIERR(cur);
                len = rlen;
            }
            
            strncat(buf, cur, len);
            buflen =++ len;
        }
        va_end(ap);

        pathstr = strndup(buf, buflen);
        free(buf);

        /* next, create branches */

        return res;
}



struct access_frame *aframe_mkflatpath(struct cosmos *cm, struct access_frame *af, int segc, ...)
{

}



struct access_frame *aframe_mkpath(struct cosmos *cm, struct access_frame *af, int segc, ...)
{

}


struct access_frame *aframe_by_path_id(struct access_frame *af, cosmos_strid_t id)
{
        struct access_frame *res = aframe_get_branch( af, id );

        return res;
}