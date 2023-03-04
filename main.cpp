#include "list.h"

int main ()
{
    struct list_t box = {};
    list_init (&box);

    list_push (&box, 1, 1);
    list_push (&box, 12, 2);
    list_push (&box, 35, 3);
    list_push (&box, 32, 2);
    list_push (&box, 113, 2);
    list_push (&box, 11, 2);
    list_push (&box, 12, 2);
    list_push (&box, 13, 2);
    list_push (&box, 14, 2);
    list_push (&box, 18, 3);
    list_push (&box, 1, 1);
    list_pop  (&box, 7);
    list_push (&box, 32, 7);
    list_print(&box);
    list_graph(&box);
    list_delete (&box);
    return 0;
}
