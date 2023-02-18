#include "list.h"

void list_init (list_t* box)
{
    box->capacity = 10;

    box->data  = (list_type*) calloc (box->capacity, sizeof (list_type));
    MY_ASSERT    (box->data  != NULL);
    box->index = (struct access*) calloc (box->capacity, sizeof (struct access));
    MY_ASSERT    (box->index != NULL);
    box->index[0].next = 0;
    box->head  = 1;
    box->tail  = 1;
    box->free  = 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_push (list_t* box, list_type element, size_t position)
{
    bad_search (box);
    MY_ASSERT  (box->free != 0);


    if (box->free < box->head)
    {
        box->data[box->free]  = element;
        box->index[box->free].next = position;
    }

    else if (position == 1)
    {
        box->data[box->free] = element;
        box->index[box->free].next = position
    }

    else
    {
        box->data[box->free]          = element;
        box->index[box->free].next    = position;
        box->index[position - 1].next = box->free;
    }

    box->size++;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

size_t bad_search (list_t* box)
{
    for (int i = 0; i < box->capacity; i++)
    {
        if (box->index[i].next < 0)
        {
            box->free = -box->index[i].next;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

list_type  list_pop    (list_t* box)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_delete (list_t* box)
{
    free (box->data);
    free (box->index);
}
