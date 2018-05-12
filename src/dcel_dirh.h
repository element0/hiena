#ifndef HIENA_DCEL_DIRHANDLE_H
#define HIENA_DCEL_DIRHANDLE_H





struct hiena_dcel;
struct dcel_dirent;


struct dcel_dirh {

        /** for retain */
        struct hiena_dcel *dcel;

        struct dcel_dirent *cur;
        struct dcel_dirent *cur_ord;
};





#endif /* ! HIENA_DCEL_DIRHANDLE_H */
