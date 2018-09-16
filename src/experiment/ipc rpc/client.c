#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define SOCKFILEPATH "./testsock"

typedef con_t int;


con_t open_connection()
{
    char c;
    FILE *fp;
    register int i, s, len;
    struct sockaddr_un saun;


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("client: socket");
        return -1;
    }


    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, SOCKFILEPATH);

    len = sizeof(saun.sun_family) + strlen(saun.sun_path);

    if (connect(s, &saun, len) < 0)
    {
        perror("client: connect");
        return -1;
    }
    return s;
}

void *marshall(int argc, int fnid, int arg1, int arg2)
{
    int *buf;

    buf = malloc(sizeof(int)*(argc+1));

    buf[0] = sizeof(*buf);
    buf[1] = fnid;
    buf[2] = arg1;
    buf[3] = arg2;

    return (void *)buf;
}


void *rpc(con_t con, void *buf, size_t len)
{
    FILE *fp;
    // send
    send(con, buf, len, 0);

    // recv
    fp = fdopen(con, "r");
    
}



int main(int argc, char *argv[])
{
    con_t con;
    void *buf, *retbuf;
    int sum;

    con = open_connection();

    buf = marshall(3,'+',1,2);

    retbuf = rpc( con, buf );

    sum = (int)(*retbuf);

    printf("1+2==%d\n",sum);

    
    free(retbuf);
    free(buf);
    close_connection();

    return 0;
}