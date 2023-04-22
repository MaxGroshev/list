#include "list.h"

int main ()
{
    struct list_t box = {};
    list_init (&box);

    list_insert (&box, 1,  1);
    list_insert (&box, 4,  2);
    list_insert (&box, 5,  3);
    list_insert (&box, 3,  2);
    list_insert (&box, 2,  2);

    list_insert (&box, 6,  6);


   // int elem = list_pop_back (&box);
    // printf ("%d\n", elem);

   // list_pop  (&box, 2);

    // elem = find_phys_by_logic (&box, 1);
    // printf ("%d\n", elem);
    // elem = find_logic_by_phys (&box, 11);
    // printf ("%d\n", elem);

    list_linear (&box);

    list_print  (&box);
    list_graph  (&box);
    list_delete (&box);



    return 0;
}
