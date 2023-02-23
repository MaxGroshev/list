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

    else if (position == 1)
    {
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
            next_cell = box->index[next_cell].next;
        }

        box->data [box->free]      = element;
        box->index[box->index[next_cell].next].prev = box->free;
        box->index[box->free].prev = next_cell;
        box->index[box->free].next = box->index[next_cell].next;
        box->index[next_cell].next = box->free;
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
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

list_type  list_pop (list_t* box, size_t position )
{
    list_type element = 0;

    if (box->size == 1)
    {
        element = box->data[box->tail];
        box->index[box->free].prev = 0;
        box->index[box->free].next = 0;
        clean_cell (box, box->tail);
    }

    else if (position == box->size)
    {
        element = box->data[box->tail];
        box->index[box->index[box->tail].prev].next = 0;
        clean_cell (box, box->tail);
        box->tail = box->index[box->tail].prev;
    }

    else if (position == 1)
    {
        list_type element = box->data[box->head];
        box->index[box->index[box->head].next].prev = 0;
        clean_cell (box, box->head);
        box->head = box->index[box->head].next;
    }

    else
    {
        size_t next_cell = box->head;
        for (int i = 0; i < position - 1; i++)
        {
            next_cell = box->index[next_cell].next;
        }

        element = box->data[next_cell];
        box->index[box->index[next_cell].next].prev = box->index[next_cell].prev;
        box->index[box->index[next_cell].prev].next = box->index[next_cell].next;
        clean_cell (box, next_cell);
    }
    box->size--;

    return element;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_delete (list_t* box)
{
    free (box->data);
    free (box->index);
}

void clean_cell (list_t* box, size_t num_cell)
{
    box->index[num_cell].next = -1;
    box->index[num_cell].prev = -1;
    box->data [num_cell]      = 0xDEAD;
}
