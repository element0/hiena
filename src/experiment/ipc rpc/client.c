


#include <stdio.h>
#include <stdlib.h>

typedef con_t void


con_t *open_connection()
{
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


void *rpc(con_t *con, void *buf)
{
    // send

    // recv

}



int main(int argc, char *argv[])
{
    con_t *con
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