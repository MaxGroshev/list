#pragma once
#include <stdio.h>
#include "def_set.h"

struct stat_t
{
    size_t  capacity;
    size_t  size;
    size_t  head;
    size_t  tail;
};

struct graph_t
{
    const char*   orientation;
    const char*   splines;
    const char*   shape;
    const char*   fillcolor;
    const char*   style;
    const char*   fontcolor;
    const char*   fontname;
    const char*   color;
    struct stat_t inform;
};


void init_graph   (FILE* graphviz, graph_t* graph_dump_set);
void make_node    (FILE* graphviz, int name, const char* fillcolor, size_t next, size_t prev, int value, const char* label);
void make_edge    (FILE* graphviz, int name_from, int name_to, const char* color, const char* style, const char* constraint);
void run_graphviz (FILE* graphviz);
