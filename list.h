#pragma once
#define DEBUG
#define CHECK_QUEUE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_check.h"
#include "my_ASSERT.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef int list_type; // type of elem in queue

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

struct access
{
    size_t next;
    size_t prev;
};

struct list_t
{
    list_type* data;
    struct     access* index;
    size_t     prev_push;
    size_t     head;
    size_t     tail;
    size_t     free;
    size_t     capacity;
    size_t     size;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void      list_init   (list_t* box);
void      list_push   (list_t* box, list_type element, size_t position);
list_type list_pop    (list_t* box, size_t position);
void      bad_search  (list_t* box);
void      list_resize (list_t* box);
void      clean_cell  (list_t* box, size_t num_cell);
void      list_delete (list_t* box);

void      list_print  (list_t* box);
void       list_check  (list_t* box, const char* DUR_FILE, const char* FUNCTION, int LINE);
