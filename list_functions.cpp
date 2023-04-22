#include "list.h"

void list_init (list_t* box) //return int (code of error), better without void
{
    box->capacity = 10;
    box->index = (struct lst_node_t*) calloc (box->capacity, sizeof (struct lst_node_t));
    MY_ASSERT    (box->index != NULL);
    for (int i = 0; i < box->capacity; i++)
    {
        box->index[i].next = i + 1;
        box->index[i].prev = i - 1;
        box->index[i].data = 0xDEAD;
    }
    box->index[0].next = 0;
    box->index[0].prev = 0;
    box->head  = 1;
    box->tail  = 1;
    box->free  = 1;
}

//-----------------------------------------------INSERT_FUNC--------------------------------------------------------------------------------------------------------------------

void list_insert (list_t* box, list_type element, size_t position)
{
    int free_cell = find_first_free (box);
    box->free = box->index[free_cell].next;
    LIST_CHECK (box->free != 0 && position > 0 && position - 1 <= box->size);

    if (box->size == 0)
    {
        box->index[free_cell].data = element;
        box->index[free_cell].prev = 0;
        box->index[free_cell].next = 0;
    }
    else if (position > box->size)
    {
        box->index[free_cell].data = element;
        box->index[free_cell].prev = box->tail;
        box->index[free_cell].next = 0;
        box->index[box->tail].next = free_cell;
        box->tail                  = free_cell;
    }
    else if (position == 1)
    {
        box->index[free_cell].data = element;
        box->index[free_cell].next = box->head;
        box->index[free_cell].prev = 0;
        box->index[box->head].prev = free_cell;
        box->head = free_cell;
    }
    else
    {
        size_t next_cell = box->head;
        for (int i = 0; i < position - 2; i++)
        {
            next_cell = box->index[next_cell].next;
        }

        box->index[free_cell].data = element;
        box->index[box->index[next_cell].next].prev = free_cell;
        box->index[free_cell].prev = next_cell;
        box->index[free_cell].next = box->index[next_cell].next;
        box->index[next_cell].next = free_cell;
    }
    box->size++;
}

void list_push_front (list_t* box, list_type element)
{
    MY_ASSERT (box != NULL)
    int free_cell = find_first_free (box);
    box->free = box->index[free_cell].next;

    box->index[free_cell].data = element;
    box->index[free_cell].next = box->head;
    box->index[free_cell].prev = 0;
    box->index[box->head].prev = free_cell;
    box->head = free_cell;
    box->size++;
}

void list_push_back (list_t* box, list_type element)
{
    MY_ASSERT (box != NULL)
    int free_cell = find_first_free (box);
    box->free = box->index[free_cell].next;

    box->index[free_cell].data = element;
    box->index[free_cell].prev = box->tail;
    box->index[free_cell].next = 0;
    box->index[box->tail].next = free_cell;
    box->tail                  = free_cell;
    box->size++;
}

//--------------------------------------------------POP_FUNC-----------------------------------------------------------------------------------------------------------------------

list_type  list_pop (list_t* box, size_t position)
{
    list_type element = 0;
    LIST_CHECK (position > 0 && position - 1 <= box->size );

    if (box->size == 1)
    {
        element = box->index[box->tail].data;
        box->index[box->free].prev = 0;
        box->index[box->free].next = 0;
        clean_cell (box, box->tail);
    }
    else if (position == box->size)
    {
        element   = box->index[box->tail].data;
        box->tail = box->index[box->tail].prev;
        clean_cell (box, box->index[box->tail].next);
        box->index[box->tail].next = 0;
    }
    else if (position == 1)
    {
        element   = box->index[box->head].data;
        box->head = box->index[box->head].next;
        clean_cell (box, box->index[box->head].prev);
        box->index[box->head].prev = 0;
    }
    else
    {
        size_t next_cell = box->head;
        for (int i = 0; i < position - 1; i++)
        {
            next_cell = box->index[next_cell].next;
        }

        element =  box->index[next_cell].data;
        box->index[box->index[next_cell].next].prev = box->index[next_cell].prev;
        box->index[box->index[next_cell].prev].next = box->index[next_cell].next;
        clean_cell (box, next_cell);
    }
    box->size--;

    return element;
}

list_type list_pop_front (list_t* box)
{
    //if (box->size == 0)  // add recognize of errors

    list_type element = box->index[box->head].data;
    box->head = box->index[box->head].next;
    clean_cell (box, box->index[box->head].prev);
    box->index[box->head].prev = 0;
    box->size--;

    return element;
}

list_type list_pop_back (list_t* box)
{
    list_type element = box->index[box->tail].data;
    box->tail = box->index[box->tail].prev;
    clean_cell (box, box->index[box->tail].next);
    box->index[box->tail].next = 0;
    box->size--;

    return element;
}

//-------------------------------------------SEARCH_FUNC---------------------------------------------------------------------------------------------------------------------------

int find_first_free (list_t* box)
{
    if (box->capacity < box->free + 3)
    {
        list_resize (box);
    }
    return box->free;
}

int  find_phys_by_logic (list_t* box, int logic_pos)
{
    //if (logic_pos <=)
    int next_cell = box->head;
    for (int i = 0; i < logic_pos - 1; i++)
    {
        next_cell = box->index[next_cell].next;
    }
    return next_cell;
}

int  find_logic_by_phys (list_t* box, int phys_pos)
{
    //if (logic_pos <=)
    int logic_pos = 1;

    while (phys_pos != box->head)
    {
        phys_pos = box->index[phys_pos].prev;
        logic_pos++;
    }
    return logic_pos;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_linear (list_t* box)
{
    MY_ASSERT (box != NULL);

    static int change_flag = 0;
    int init_cell = box->index[box->head].next;
    for (int phys_pos = 2; phys_pos < box->size - 1; phys_pos++)
    {
        printf ("%d\n", init_cell);
        printf ("%d - init_cell; %d - phys_pos\n", init_cell, phys_pos);
        if (init_cell != phys_pos)
        {

            lst_node_t init_cell_val = box->index[init_cell];
            lst_node_t phys_val = box->index[phys_pos];

            box->index[box->index[init_cell].next].prev = phys_pos;
            box->index[box->index[init_cell].prev].next = phys_pos;

            box->index[box->index[phys_pos].next].prev = init_cell;
            box->index[box->index[phys_pos].prev].next = init_cell;

            box->index[phys_pos].data  = init_cell_val.data;
            box->index[init_cell].next = phys_val.next;
            box->index[init_cell].prev = phys_pos;

            box->index[phys_pos].prev  = init_cell_val.prev;
            box->index[phys_pos].next  = init_cell_val.next;
            box->index[init_cell].data = phys_val.data;
            change_flag = 1;
        }

        init_cell = box->index[phys_pos].next;
   }
//  if (change_flag != 0) list_linear (box);

}


void clean_cell (list_t* box, size_t num_cell)
{
    box->index[num_cell].next = -1;
    box->index[num_cell].prev = -1;
    box->index[num_cell].data = 0xDEAD;
}

void list_resize (list_t* box)
{
    size_t prev_size = box->capacity;
    box->capacity *= 2;
    struct lst_node_t* index_resize = box->index;
    index_resize = (struct lst_node_t*) realloc (box->index, box->capacity * sizeof (struct lst_node_t));
    MY_ASSERT (index_resize != NULL);

    box->index = index_resize;
    for (int i = prev_size; i < box->capacity; i++)
    {
        box->index[i].next = i + 1;
        box->index[i].prev = i - 1;
        box->index[i].data = 0xDEAD;
    }
}

void list_delete (list_t* box)
{
    free (box->index);
}

