#include <stdio.h>

#include "cosmos_config.h"


#define MODELNUM "FA-18"
#define NICKNAME "Hornet"

#define MODEL2 "A-10"
#define NICK2 "Thunderbolt"

#define JETFIGHTER MODELNUM " " NICKNAME

#define PROPFIGHTER MODEL2 " " NICK2

#define AIRFLEET ROOTNAME JETFIGHTER "s and " PROPFIGHTER "s"

#define ROOTNAME "/"

int main(int argc, char **argv)
{
        char *jetstring;

        jetstring = AIRFLEET;

        printf("%s\n", jetstring);
        printf(COSMOS_HOST_ROOTDIR_NAME);
        printf("\n");
        
        return 0;
}