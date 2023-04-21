#ifndef LIST_H
#define LIST_H

#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphviz.h"
#include "list_check.h"
#include "my_ASSERT.h"

//--------------------------------------------------------------------------------------------------------------------------------------

#define CUR_POS_IN_PROG    __FILE__, __PRETTY_FUNCTION__, __LINE__

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef int list_type; // type of elem in list

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum list_side
{
    TAIL = 1,
    HEAD = 2,
};

enum code_of_errors
{
    LIST_IS_OKEY    =  0,
    CELL_NOT_FOUND  = -1,
    NO_FREE_CELL    = -2,
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct lst_node_t
{
    size_t next;
    size_t prev;
    list_type data;
};

struct list_t
{
    struct     lst_node_t* index;
    size_t     prev_push;
    size_t     head;
    size_t     tail;
    int        free ;
    size_t     capacity;
    size_t     size;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void      list_init   (list_t* box);

//------------------------------------------------------INSERT_FUNC--------------------------------------------------------------------------------------------------

void      list_insert     (list_t* box, list_type element, size_t position);
void      list_push_front (list_t* box, list_type element);
void      list_push_back  (list_t* box, list_type element);

//-------------------------------------------------------POP_FUNC------------------------------------------------------------------------------------------------------

list_type list_pop       (list_t* box, size_t position);
list_type list_pop_front (list_t* box);
list_type list_pop_back  (list_t* box);

//--------------------------------------------------------SEARCH_FUNC-----------------------------------------------------------------------------------------------------

int       find_first_free    (list_t* box);
int       find_phys_by_logic (list_t* box, int logic_pos);
int       find_logic_by_phys (list_t* box, int phys_pos);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void      list_resize (list_t* box);
void      list_linear (list_t* box);
void      clean_cell  (list_t* box, size_t num_cell);
void      list_delete (list_t* box);

void      list_print  (list_t* box);
void      list_graph  (list_t* box);
void      list_check  (list_t* box, const char* DUR_FILE, const char* FUNCTION, int LINE);

#endif //LIST_H
