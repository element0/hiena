
struct cosmosd {
        void *temp;
        struct cosmos_db *db;
};


struct cosmosd *cosmosd_init()
{
        return NULL;
}

int cosmosd_cleanup(struct cosmosd *dmn)
{
        return NULL;
}


/**
 *  field requests from clients
 */
static int handleclients( struct cosmosd *dmn)
{
        return 0;
}

int main( int argc, char *argv[] )
{
        struct cosmosd *dmn;

        dmn = cosmosd_init();
        while( handleclients( dmn ) );
        cosmosd_cleanup( dmn );
}