
#include <stdio.h>


int daemonize()
{
    return 0;
}


int connect()
{
    
}


int do_session()
{
}


int main(int argc, char *argv[])
{
    int run = 1


    if(daemonize() == 1)
        return 0;

    make_socket();


    while(run == 1)
    {
        connect();
        do_session();
    }


    cleanup_socket();
    

    return 0;
}
