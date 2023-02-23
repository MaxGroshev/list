#include "list.h"

int main ()
{
    struct list_t box = {};
    list_init (&box);

    list_push (&box, 1, 1);
    list_push (&box, 12, 2);
    list_push (&box, 35, 3);
    //list_push (&box, 32, 2);
    list_push (&box, 113, 2);
    list_push (&box, 11, 2);
    list_push (&box, 18, 3);
    list_push (&box, 1, 1);
    //list_push (&box, 32, 7);

    for (int i = 0; i < box.capacity; i++)
    {
        printf ("%d %ld %ld\n", box.data[i], box.index[i].next, box.index[i].prev);
    }
    printf ("%ld %ld", box.head, box.tail);
    list_delete (&box);
    return 0;
}
