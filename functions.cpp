#include "graphviz.h"

void init_graph (FILE* graphviz, graph_t* settings)
{
    fprintf (graphviz, "digraph \n{\n");
    fprintf (graphviz, "rankdir = \"LR\"\n");
    fprintf (graphviz, "node [shape = Mrecord, fillcolor= \"#FA8072\", style = filled, fontcolor = white, "
                       "color = white, fontname = \"Calibri\", pin = true];\n\n");
}

void make_node (FILE* graphviz, int name, const char* fillcolor, size_t next, size_t prev, int value, const char* label)
{
    fprintf (graphviz, "node%d [fillcolor = \"%s\", label = \"{<cell> cell = %d\\n %s| {value = %d |<next> next = %ld |<prev> prev = %ld}}\"];\n\n", name, fillcolor, name, label,value, next, prev);
}

void make_edge (FILE* graphviz, int name_from, int name_to, const char* color, const char* style)
{
    fprintf (graphviz, "node%d:<prev> -> node%d:<cell> [color = \"%s\", style = \"%s\"\n", name_from, name_to, color, style);
}

void run_graphviz (FILE* graphviz)
{
    fprintf (graphviz, "}\n");
}
