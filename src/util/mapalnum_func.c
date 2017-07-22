#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dcel.h"
#include "../dcel_fh.h"
#include "../dcel_svc.h"
#include "../dcel_mapsvc.h"
#include "../mapcel.h"
#include "../hierr.h"



int mapalnum( struct hiena_dcel *dc )
{
        if( dc == NULL )
        {
                HIERR("mapalnum: dcel is NULL.");
                return -1;
        }

        struct dcel_fh *dfh;
        char c;
        int si, i;
        int stak[6];
        size_t pos[6], len[6];
        size_t matchlen;
        struct hiena_mapcel *val[4];
        struct map_anchor *ma, *ma2;
        const int num_rule = 21;

        enum {
INITOK,
ATOK,
NTOK,
ANTOK,
ENDTOK
        };

        enum {
_beginparse,
_endparse,
_growlen1,
_growlen2,
_new1_growlen2,
_new2_new4_parent412,
_new2_new4_parent412_endparse,
_new2_addchild12,
_new2_addchild12_endparse,
        };


        char rule[][8]={
ENDTOK,0,0,ENDTOK,0,0,3,_endparse,
0,0,0,0,0,0,0,_beginparse,
ATOK,0,0,ATOK,0,0,1,_growlen1,
NTOK,0,0,NTOK,0,0,1,_growlen1,

ATOK,NTOK,ENDTOK,ANTOK,ENDTOK,0,3, _new2_new4_parent412_endparse,
ATOK,ATOK,0,ATOK,0,0,1, _growlen1,
ATOK,NTOK,0,ATOK,NTOK,0,2, _new1_growlen2,
ATOK,NTOK,NTOK,ATOK,NTOK,0,2, _growlen2,
ATOK,NTOK,ATOK,ANTOK,ATOK,0,2, _new2_new4_parent412,

NTOK,ATOK,ENDTOK,ANTOK,ENDTOK,0,3, _new2_new4_parent412_endparse,
NTOK,NTOK,0,NTOK,0,0,1, _growlen1,
NTOK,ATOK,0,NTOK,ATOK,0,2, _new1_growlen2,
NTOK,ATOK,ATOK,NTOK,ATOK,0,2, _growlen2,
NTOK,ATOK,NTOK,ANTOK,NTOK,0,2, _new2_new4_parent412,


ANTOK,ATOK,ENDTOK,ANTOK,ENDTOK,0,3, _new2_addchild12_endparse,
ANTOK,NTOK,ENDTOK,ANTOK,ENDTOK,0,3, _new2_addchild12_endparse,
ANTOK,ENDTOK,0,ANTOK,ENDTOK,0,3, _endparse,
ANTOK,ATOK,ATOK,ANTOK,ATOK,0,2, _growlen2,
ANTOK,NTOK,NTOK,ANTOK,NTOK,0,2, _growlen2,
ANTOK,ATOK,NTOK,ANTOK,ATOK,0,2, _new2_addchild12,
ANTOK,NTOK,NTOK,ANTOK,NTOK,0,2, _new2_addchild12,
        };

        
        dfh = (struct dcel_fh *)dcel_svc_ops.open( (void *)dc, "r" );

        stak[0] = 0;
        stak[1] = 0;
        stak[3] = 0;
        si = 0;
        memset(&pos, 0, sizeof(pos));

parse_loop:

        matchlen = 0;
        si = 0;
        c = dfh->ops->getchar( (void *)dfh );

        if(( c >= 65
          && c <= 90 )
         ||( c >= 97
          && c <= 122 ))
                stak[si] = ATOK;
        if(  c >= 48
          && c <= 57 )
                stak[si] = NTOK;
        else
                stak[si] = ENDTOK;

        matchlen++;

        for(i=0; i<num_rule; i++)
        {

        if((stak[0] == rule[i][0])
         &&(stak[1] == rule[i][1])
         &&(stak[2] == rule[i][2]))
         {
               break;
         }

        }

        switch(rule[i][7])
        {
  
        case _growlen1:
                len[0] =+ matchlen;
                break;

        case _new1_growlen2:
                val[0] = dcel_mapsvc.newterm(dfh, stak[0], pos[0], len[0]);
                
                /* fall thru */

        case _growlen2:
                len[1] =+ matchlen;
                break;

        case _new2_new4_parent412:
                val[1] = dcel_mapsvc.newterm(dfh, stak[1], pos[1], len[1]);

                val[3] = dcel_mapsvc.new(dfh, stak[3], pos[3], len[3]);
                dcel_mapsvc.add(dfh, val[3], val[0]);
                dcel_mapsvc.add(dfh, val[3], val[1]);

                val[1] = val[3];
                break;

        case _new2_new4_parent412_endparse:

                val[1] = dcel_mapsvc.newterm(dfh, stak[1], pos[1], len[1]);

                val[3] = dcel_mapsvc.new(dfh, stak[3], pos[3], len[3]);

dcel_mapsvc.add(dfh, val[3],val[1]);
                dcel_mapsvc.add(dfh, val[3],val[2]);

                val[1] = val[3];

                goto post_parse;


        case _new2_addchild12:

                val[1] = dcel_mapsvc.newterm(dfh, stak[1], pos[1], len[1]);
                dcel_mapsvc.add(dfh, val[0],val[1]);

                break;

_new2_addchild12_endparse:

                val[1] = dcel_mapsvc.newterm(dfh,stak[1],pos[1], len[1]);
                dcel_mapsvc.add(dfh, val[0],val[1]);

                goto post_parse;

        case _endparse:
                goto post_parse;
                break;

        default:
                break;
        }

        stak[0] = rule[i][3];
        stak[1] = rule[i][4];
        stak[3] = rule[i][5];
        si = rule[i][6];

goto parse_loop;

post_parse:

        dcel_svc_ops.close( (void *)dfh );

        return 0;
}
