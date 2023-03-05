#include "list.h"

void list_check (list_t* box, const char* DUR_FILE, const char* FUNCTION, int LINE)
{
    if (box->free == 0)
    {
        fprintf (stderr, "Free cell was't found in %s: %s: %d:\n", DUR_FILE, FUNCTION, LINE);
        list_print (box);
    }

    else
    {
        fprintf (stderr, "Impossible to use numbers of elements that does't belong to list in %s: %s: %d:\n", DUR_FILE, FUNCTION, LINE);
        list_print (box);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void list_print (list_t* box)
{
    FILE* print_list = fopen ("list.txt", "w");
    MY_ASSERT (print_list != NULL);

    fprintf (print_list, "=========================HEAD_&_TAIL====================================\n"
                          "%3ld [%d] - head point to this cell\n"
                          "%3ld [%d] - tail point to this cell\n"
                          "%3ld - capacity of list\n"
                          "%3ld - size of list\n"
                          "============================LIST=======================================\n\n"
                          ,box->head, box->data[box->head], box->tail, box->data[box->tail], box->capacity, box->size);

    fprintf (print_list, " [cell] | [prev] | [next] | [data]\n");
    for (int i = 0; i < box->capacity; i++)
    {
        if (i == box->tail)
        {
            if (box->tail == box->head)
            {
                fprintf (print_list, "%4d %8ld %8ld %9d - head & tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
            }

            else
            {
                fprintf (print_list, "%4d %8ld %8ld %9d - tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
            }
        }

        else if (i == box->head)
        {
            fprintf (print_list, "%4d %8ld %8ld %9d - head point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
        }

        else
        {
            fprintf (print_list, "%4d %8ld %8ld %9d\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
        }
    }
    fclose (print_list);
}

void list_graph (list_t* box)
{
    FILE* graphviz = fopen ("list_dump.dot", "w");
    graph_t settings = {};
    init_graph (graphviz, &settings);

    for (int i = 0; i < box->capacity; i++)
    {

        if (i == box->head)
        {
            make_node (graphviz, i, "#008080", box->index[i].next, box->index[i].prev, box->data[i], "HEAD");
        }

        else if (i == box->tail)
        {
            make_node (graphviz, i, "#006400", box->index[i].next, box->index[i].prev, box->data[i], "TAIL");
        }

        else
        {
            make_node (graphviz, i, "#FA8072", box->index[i].next, box->index[i].prev, box->data[i], "");
        }
    }

    for (int i = 0; i < box->capacity - 1; i++)
    {
        make_edge (graphviz, i, i + 1, "", "invis");
        if (box->index[i].next != -1 && (box->index[i].next != 0 || box->index[i].prev != 0))
        {
            make_edge (graphviz,  i, box->index[i].next, "#FF8C00", "");
            make_edge (graphviz,  i, box->index[i].prev, "blue", "");
        }
    }

    run_graphviz (graphviz);
    fclose (graphviz);
}
