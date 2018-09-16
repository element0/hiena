#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define SOCKFILEPATH "./testsock"

typedef int con_t;


con_t open_connection()
{
    register int s, len;
    struct sockaddr_un saun;


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("client: socket");
        return -1;
    }


    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, SOCKFILEPATH);

    len = sizeof(saun.sun_family) + strlen(saun.sun_path);

    if (connect(s, (struct sockaddr *)&saun, len) < 0)
    {
        perror("client: connect");
        return -1;
    }
    return s;
}

void *marshall(int argc, int fnid, int arg1, int arg2, int *lenptr)
{
    int *buf, len;

    len = sizeof(int)*(argc+1);

    buf = malloc(len);

    buf[0] = sizeof(*buf);
    buf[1] = fnid;
    buf[2] = arg1;
    buf[3] = arg2;

    *lenptr = len;

    return (void *)buf;
}


int rpc(con_t con, void *buf, size_t len)
{
    char c[2];
    FILE *fp;
    // send
    send(con, buf, len, 0);

    // recv
    fp = fdopen(con, "r");
    c[0] = fgetc(fp);
    c[1] = '\0';

    return atoi(c);
}



int main(int argc, char *argv[])
{
    con_t con;
    void *buf, *retbuf;
    int sum, len;

    con = open_connection();

    buf = marshall(3,'+',1,2, &len);

    sum = rpc( con, buf, len );

    printf("1+2==%d\n",sum);

    free(buf);
    close(con);

    return 0;
}
