/*

http://www.cse.yorku.ca/~oz/hash.html

*/

/*  dboy tweak 2018-05-11
    NULL input -> 0
 */

    unsigned long
    hash_djb2(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

    unsigned long
    hash_sdbm(char * str)
    {
        unsigned long hash = 0;
        int c;


        /* dboy tweak */
        if( str == '\0' )
                return hash;
        

        while (c = *str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }