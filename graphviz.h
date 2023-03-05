#pragma once
#include <stdio.h>

struct graph_t
{
    const char* orientation;

};


void init_graph   (FILE* graphviz, graph_t* settings);
void make_node    (FILE* graphviz, int name, const char* fillcolor, size_t next, size_t prev, int value, const char* label);
void make_edge    (FILE* graphviz, int name_from, int name_to, const char* color, const char* style);
void run_graphviz (FILE* graphviz);
