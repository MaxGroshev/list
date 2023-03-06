#include "graphviz.h"

void init_graph (FILE* graphviz, list_graph_t* graph_dump_set)
{
    fprintf (graphviz, "digraph   \n{\n");
    fprintf (graphviz, "rankdir = \"%s\"\n", graph_dump_set->orientation);
    fprintf (graphviz, "splines = \"%s\"\n", graph_dump_set->splines);
    fprintf (graphviz, "node [shape = %s, fillcolor = \"%s\",   style = %s,      fontcolor = %s,      fontname = \"%s\",  color = %s, pin = true];\n\n",
                        graph_dump_set->shape,  graph_dump_set->fillcolor, graph_dump_set->style, graph_dump_set->fontcolor, graph_dump_set->fontname, graph_dump_set->color);

    fprintf (graphviz, "node_stat [margin = \"0.3*0.3\", shape = \"record\", fillcolor = \"#8DB6CD\" label = \"capacity = %ld | size = %ld | head point = %ld | tail point = %ld\"]\n",
                        graph_dump_set->inform.capacity, graph_dump_set->inform.size, graph_dump_set->inform.head, graph_dump_set->inform.tail);
    fprintf (graphviz, "{rank = source; node_stat}\n");
}

void make_node (FILE* graphviz, int name, const char* fillcolor, size_t next, size_t prev, int value, const char* label)
{
    fprintf (graphviz, "node%d [fillcolor = \"%s\", label = \"{<cell> cell = %d\\n %s| {value = %d |<next> next = %ld |<prev> prev = %ld}}\"];\n\n", name, fillcolor, name, label,value, next, prev);
}

void make_edge (FILE* graphviz, int name_from, int name_to, const char* color, const char* style, const char* constraint)
{
    fprintf (graphviz, "node%d -> node%d [color = \"%s\", style = \"%s\", constraint = %s];\n", name_from, name_to, color, style, constraint);
}

void run_graphviz (FILE* graphviz)
{
    fprintf (graphviz, "}\n");
}
