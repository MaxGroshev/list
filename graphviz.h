#pragma once
#include <stdio.h>

//---------------------------------------------------------------------------------------------------------

struct stat_t
{
    size_t  capacity;
    size_t  size;
    size_t  head;
    size_t  tail;
};

struct list_graph_t
{
    const char*   orientation = "LR";
    const char*   splines     = "ortho";
    const char*   shape       = "Mrecord";
    const char*   fillcolor   = "#FA8072";
    const char*   style       = "filled";
    const char*   fontcolor   = "white";
    const char*   fontname    = "Calibri";
    const char*   color       = "white";
    struct stat_t inform;
};

struct tree_graph_t
{
    const char*   orientation = "";
    const char*   splines     = "ortho";
    const char*   shape       = "record";
    const char*   fillcolor   = "grey";
    const char*   style       = "filled";
    const char*   fontcolor   = "white";
    const char*   fontname    = "Calibri";
    const char*   color       = "white";
    struct stat_t inform;
};

//--------------------------------------------------------------------------------------------------------------------------

void init_graph   (FILE* graphviz, list_graph_t* graph_dump_set);
void make_node    (FILE* graphviz, int name, const char* fillcolor, size_t next, size_t prev, int value, const char* label);
void make_edge    (FILE* graphviz, int name_from, int name_to, const char* color, const char* style, const char* constraint);
void run_graphviz (FILE* graphviz);
