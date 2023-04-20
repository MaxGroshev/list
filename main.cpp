#include "list.h"

int main ()
{
    struct list_t box = {};
    list_init (&box);

    list_insert (&box, 1,   1);
    list_insert (&box, 12,  2);
    list_insert (&box, 35,  3);
    list_insert (&box, 32,  2);
    list_insert (&box, 113, 2);
    list_insert (&box, 11,  2);
    list_insert (&box, 12,  2);
    list_insert (&box, 13,  2);
    list_insert (&box, 14,  2);
    list_insert (&box, 18,  3);
    list_insert (&box, 1,   1);
    list_pop  (&box, 7);
    // for (int i = 7; i < 1000; i++)
    // {
    //     list_insert (&box, i, i);
    // }
    list_insert (&box, 32, 7);
    list_print(&box);
    list_graph(&box);
    list_delete (&box);
    return 0;
}
