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
    FILE* print_list = fopen ("./dump_info/list_dump.txt", "w");
    MY_ASSERT (print_list != NULL);

    fprintf (print_list, "=========================HEAD_&_TAIL====================================\n"
                          "%3ld [%d] - head point to this cell\n"
                          "%3ld [%d] - tail point to this cell\n"
                          "%3ld - capacity of list\n"
                          "%3ld - size of list\n"
                          "============================LIST=======================================\n\n"
                          ,box->head, box->index[box->head].data, box->tail, box->index[box->tail].data, box->capacity, box->size);

    fprintf (print_list, " [cell] | [prev] | [next] | [data]\n");
    for (int i = 0; i < box->capacity; i++)
    {
        if (i == box->tail)
        {
            if (box->tail == box->head)
            {
                fprintf (print_list, "%4d %8ld %8ld %9d - head & tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->index[i].data);
            }

            else
            {
                fprintf (print_list, "%4d %8ld %8ld %9d - tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->index[i].data);
            }
        }

        else if (i == box->head)
        {
            fprintf (print_list, "%4d %8ld %8ld %9d - head point to this cell\n", i, box->index[i].prev, box->index[i].next, box->index[i].data);
        }

        else
        {
            fprintf (print_list, "%4d %8ld %8ld %9d\n", i, box->index[i].prev, box->index[i].next, box->index[i].data);
        }
    }
    fclose (print_list);
}

//-----------------------------------------------------------------------------------------------------------------------------------------

void list_graph (list_t* box)
{
    FILE* graphviz               = fopen ("./dump_info/list_dump.dot", "w");
    dump_graph_t graph_dump_set  = {};
    graph_dump_set.info.capacity = box->capacity;
    graph_dump_set.info.size     = box->size;
    graph_dump_set.info.head     = box->head;
    graph_dump_set.info.tail     = box->tail;
    init_graph (graphviz, &graph_dump_set);

    for (int i = 0; i < box->capacity; i++)
    {

        if (i == box->head)
        {
            graph_dump_set.nodes[i].fillcolor = "#008080";
            make_node (graphviz, &graph_dump_set,i, graph_dump_set.nodes[i], box->index[i].next, box->index[i].prev, box->index[i].data);
        }
        else if (i == box->tail)
        {
            graph_dump_set.nodes[i].fillcolor = "#006400";
            make_node (graphviz, &graph_dump_set,i, graph_dump_set.nodes[i], box->index[i].next, box->index[i].prev, box->index[i].data);
        }
        else
        {
            make_node (graphviz, &graph_dump_set, i, graph_dump_set.nodes[i], box->index[i].next, box->index[i].prev, box->index[i].data);
        }
    }

    for (int i = 0, num_of_edges = 0; i < box->capacity - 1; i++, num_of_edges++)
    {
        graph_dump_set.edges[num_of_edges].style = "invis";
        make_edge (graphviz, &graph_dump_set, i, i + 1, graph_dump_set.edges[num_of_edges]);
        num_of_edges++;
        if (box->index[i].next != -1 && (box->index[i].next != 0 || box->index[i].prev != 0))
        {
            graph_dump_set.edges[num_of_edges].constraint = "false";
            graph_dump_set.edges[num_of_edges].color      = "#FF8C00";
            make_edge (graphviz, &graph_dump_set,i, box->index[i].next, graph_dump_set.edges[num_of_edges]);

            num_of_edges++;
            graph_dump_set.edges[num_of_edges].constraint = "false";
            graph_dump_set.edges[num_of_edges].color      = "blue";
            make_edge (graphviz, &graph_dump_set, i, box->index[i].prev, graph_dump_set.edges[num_of_edges]);
        }
    }

    run_graphviz (graphviz, &graph_dump_set);
    fclose (graphviz);
}
