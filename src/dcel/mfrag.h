





#ifndef HIENA_MFRAG_H
#define HIENA_MFRAG_H

/** @file mfrag.h
 *
 * CHANGE LOG
 *
 * 2019-03-17 Update
 * - moved `bufid` to `dcel.h`
 *
 * 2019-02-22 removed svc, addr
 * - use `source`
 * 2019-02-22 removed buf, len
 * - use `bufid` for buffer manager
 *   (may use the string db.)
*/

#include <sys/types.h>

#define HIMFRAG_BOUND_T off_t
#define HIMFRAG_BOUNDS_MIN 0
#define HIMFRAG_BOUNDS_MAX 2147483648
#define HIMFRAG_BOUND_ERR 0
#define HIMFRAG_BUFSIZE_T size_t

/* 17-03-24 pos and off are same type */

#define HIMFRAG_POS_T off_t
#define HIMFRAG_OFF_T off_t
#define HIMFRAG_OFF_MIN 0
#define HIMFRAG_OFF_MAX (2^31)

#include <stdlib.h>

#define HIMFRAG_SRC_T void *
#define HIMFRAG_SRC_VERIFY(src) (src != NULL)


/**
 * Tracks a byte sequence fragment within a dcel's stream buffer.
 * Used in leaf nodes of the dcel's fragment map.
 * Allows for non-destructive "editing" of a stream buffer.
 * Fragments can appear to insert bytes into a buffer at a point.
 * Allows for merging, or interleaving, stream buffers, by reference
 * without changing the underlying streams.
 */
struct hiena_mfrag {

        /**
         * Points to a `dcel`.
         * The `prod_instr` of the dcel
         * has the `svc` module and `addr`.
         * The `dcel` has a stream buffer.
         */
        void *source;  // dcel

	
	/**
	 * iForgot: possibly replaced by bufh, buft.
	 */
        HIMFRAG_BOUND_T boundhead;
        HIMFRAG_BOUND_T boundtail;

	/**
	 * Excerpt of stream buffer.
	 */
        HIMFRAG_BOUND_T bufh;
        HIMFRAG_BOUND_T buft;

        int flags;
};

struct hiena_mfrag *mfrag_new();
struct hiena_mfrag *mfrag_dup( struct hiena_mfrag * );

void mfrag_cleanup( struct hiena_mfrag *mf );

int mfrag_set_source( struct hiena_mfrag *f, void *source );


int mfrag_set_bounds( struct hiena_mfrag *mf, HIMFRAG_BOUND_T bh, HIMFRAG_BOUND_T bt );

int mfrag_set_boundhead( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

int mfrag_set_boundtail( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

HIMFRAG_BOUND_T mfrag_get_length( struct hiena_mfrag *mf );





#endif /* ! HIENA_MFRAG_H */
