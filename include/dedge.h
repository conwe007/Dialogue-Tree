#ifndef __DEDGE_H
#define __DEDGE_H

#include "dnode.h"
#include <stdlib.h>

#define STR_LENGTH 2048

typedef struct dedge_t
{
    char* text;
    struct dnode_t* start;
    struct dnode_t* end;
} dedge_t;

/**
 * Allocates space for a dedge struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dedge_t* dedge_create();

/**
 * Destroys a dedge struct, freeing its space in memory
 * 
 * @param dedge the struct to be destroyed
 */
void dedge_destroy(dedge_t* dedge);

/**
 * Copies the contents of the structure at source into a new dedge structure
 * 
 * @param source the location in memory to copy dedge from
 * @return a location in memory with identical contents to source
 */
dedge_t* dedge_copy(dedge_t* source);

/**
 * Prints info about a dedge to stdout
 * 
 * @param dedge the dedge structure to print info about
 */
void dedge_print_info(dedge_t* dedge);

/**
 * Prints a dedge structure in tree representation
 * 
 * @param dedge the graph structure to print
 * @param depth current depth of the tree, affects how much white space is printed
 */
void dedge_print_tree(dedge_t* dedge, int depth);

#endif /* __DEDGE_H */
