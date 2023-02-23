#include "list.h"

void list_init (list_t* box)
{
    box->capacity = 10;

    box->data  = (list_type*) calloc (box->capacity, sizeof (list_type));
    MY_ASSERT    (box->data  != NULL);
    box->index = (struct access*) calloc (box->capacity, sizeof (struct access));
    MY_ASSERT    (box->index != NULL);
    memset (box->index + 1, -1, (box->capacity - 1) * sizeof (struct access));
    box->head  = 1;
    box->tail  = 1;
    box->free  = 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_push (list_t* box, list_type element, size_t position)
{
    bad_search (box);
    MY_ASSERT  (box->free != 0);

    if (box->size == 0)
    {
        box->data [box->free] = element;
        box->index[box->free].prev = 0;
        box->index[box->free].next = 0;
    }

    else if (position > box->size)
    {
        box->data [box->free]      = element;
        box->index[box->free].prev = box->tail;
        box->index[box->free].next = 0;
        box->index[box->tail].next = box->free;
        box->tail                  = box->free;
    }

    else if (position <= box->head)
    {
        printf ("hey\n");
        box->data [box->free]      = element;
        box->index[box->free].next = box->head;
        box->index[box->free].prev = 0;
        box->index[box->head].prev = box->free;
        box->head = box->free;
    }

    else
    {
        size_t next_cell = box->head;
        for (int i = 0; i < position - 2; i++)
        {
            printf ("%ld\n", position - 2);
            next_cell = box->index[next_cell].next;
        }

        box->data [box->free]      = element;
        box->index[box->index[next_cell].next].prev = box->free;
        box->index[box->free].prev = next_cell;
        box->index[box->free].next = box->index[next_cell].next;
        box->index[next_cell].next = box->free;
        //printf ("%d %ld %ld\n", box->data[box->free], box->index[box->free].next, box->index[box->free].prev);
    }
    box->size++;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void bad_search (list_t* box)
{
    for (int i = 0; i < box->capacity; i++)
    {
        if (box->index[i].next == -1)
        {
            box->free = i;
            break;
        }
        //printf ("Hello %ld\n", box->index[i].next);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

list_type  list_pop (list_t* box, size_t position )
{
    list_type element = box->index[position].next;
    return element;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_delete (list_t* box)
{
    free (box->data);
    free (box->index);
}
