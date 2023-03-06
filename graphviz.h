#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_ASSERT.h"

//---------------------------------------------------------------------------------------------------------

struct node_t
{
    const char* shape       = "Mrecord";
    const char* fillcolor   = "#FA8072";
    const char* style       = "filled";
    const char* fontcolor   = "white";
    const char* fontname    = "Calibri";
    const char* color       = "white";
    const char* margin      = "";
    const char* label       = "";
};

struct edge_t
{
    const char* constraint = "true";
    const char* fillcolor   = "\"\"";
    const char* style       = "";
    const char* fontcolor   = "";
    const char* fontname    = "Calibri";
    const char* color       = "black";
    const char* label       = "";
};

struct data_stat_t
{
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;
};

struct dump_graph_t
{
    const char*         orientation = "LR";
    const char*         splines     = "ortho";
    struct node_t*      nodes;
    struct edge_t*      edges;
    struct data_stat_t  info;
    size_t              node_size;
    size_t              node_capacity;
    size_t              edge_size;
    size_t              edge_capacity;
};

//--------------------------------------------------------------------------------------------------------------------------

void init_graph     (FILE* graphviz, dump_graph_t* graph_dump_set);
void make_node      (FILE* graphviz, dump_graph_t* graph_dump_set,int node_num, struct node_t nodes, size_t next, size_t prev, int value);
void make_edge      (FILE* graphviz, dump_graph_t* graph_dump_set,int num_from, int num_to, struct edge_t edges);
void resize_struct  (dump_graph_t* graph_dump_set);
void print_def_info (FILE* graphviz, dump_graph_t* graph_dump_set);
void run_graphviz   (FILE* graphviz, dump_graph_t* graph_dump_set);
