#include "list.h"

int main ()
{
    struct list_t box = {};
    list_init (&box);

    list_delete (&box);
    return 0;
}
