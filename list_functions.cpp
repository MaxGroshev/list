#include "list.h"

void list_init (list_t* box)
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
    LIST_CHECK ((position > 0 && position - 1 <= box->size), LST_NEG_NUM_OF_CELL);

    if (box->size == 0)
    {
        box->index[free_cell].data = element;
        box->index[free_cell].prev = 0;
        box->index[free_cell].next = 0;
        box->size++;
    }
    else if (position > box->size)
    {
        list_push_back (box, element, free_cell);
    }
    else if (position == 1)
    {
        list_push_front (box, element, free_cell);
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
        box->size++;
    }
}

void list_push_front (list_t* box, list_type element, int free_cell)
{
    MY_ASSERT (box != NULL)

    if (free_cell == 0) int free_cell = find_first_free (box);
    box->free = box->index[free_cell].next;

    box->index[free_cell].data = element;
    box->index[free_cell].next = box->head;
    box->index[free_cell].prev = 0;
    box->index[box->head].prev = free_cell;
    box->head = free_cell;
    box->size++;
}

void list_push_back (list_t* box, list_type element, int free_cell)
{
    MY_ASSERT (box != NULL)

    if (free_cell == 0) int free_cell = find_first_free (box);
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
    LIST_CHECK (box->free != 0 && position > 0 && position - 1 <= box->size, LST_NEG_NUM_OF_CELL);

    list_type element = 0;
    if (box->size == 1)
    {
        element = box->index[box->tail].data;
        box->index[box->free].prev = 0;
        box->index[box->free].next = 0;
        clean_cell (box, box->tail);
        box->size--;
    }
    else if (position == box->size)
    {
        element = list_pop_back (box);
    }
    else if (position == 1)
    {
        element = list_pop_front (box);
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
        box->size--;
    }

    return element;
}

list_type list_pop_front (list_t* box)
{
    MY_ASSERT (box != NULL);

    list_type element = box->index[box->head].data;
    box->head = box->index[box->head].next;
    clean_cell (box, box->index[box->head].prev);
    box->index[box->head].prev = 0;
    box->size--;

    return element;
}

list_type list_pop_back (list_t* box)
{
    MY_ASSERT (box != NULL);

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
    LIST_CHECK (logic_pos <= box->size, LST_CELL_NOT_EXIST)

    int next_cell = box->head;
    for (int i = 0; i < logic_pos - 1; i++)
    {
        next_cell = box->index[next_cell].next;
    }
    return next_cell;
}

int  find_logic_by_phys (list_t* box, int phys_pos)
{
    LIST_CHECK ((phys_pos < 0 && box->index[phys_pos].data != 0xDEAD), LST_CELL_NOT_EXIST)

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

    lst_node_t* lineared_list = (lst_node_t*) calloc (box->capacity, sizeof (lst_node_t));
    MY_ASSERT (lineared_list != NULL);

    for (int i = 0; i < box->capacity; i++)
    {
        lineared_list[i].next = i + 1;
        lineared_list[i].prev = i - 1;
        lineared_list[i].data = 0xDEAD;
    }
    lineared_list[0].next = 0;
    lineared_list[0].prev = 0;

    int cur_node = box->head;
    for (int i = 1; i < box->size + 1; i++)
    {
        lineared_list[i].data = box->index[cur_node].data;
        cur_node = box->index[cur_node].next;
    }
    lineared_list[box->size].next = 0;
    box->head  = 1;
    box->tail  = box->size;
    box->free  = box->size + 1;

    list_delete (box);
    box->index = lineared_list;
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

