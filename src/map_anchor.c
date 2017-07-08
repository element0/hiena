





#include <stdlib.h>
#include "map_anchor.h"


struct map_anchor *map_anchor_new()
{
        struct map_anchor *ma;

        ma = malloc(sizeof(*ma));

        return ma;
}