#ifndef __DNODE_H
#define __DNODE_H

#include "dedge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LENGTH 2048

typedef struct dnode_t
{
    char* text; // the dialogue body of the node
    struct dedge_t** options; // a list of possible responses to the body
    int num_options; // the number of responses available
} dnode_t;

/**
 * Allocates space for a dnode struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dnode_t* dnode_create();

/**
 * Destroys a dnode struct, freeing its space in memory
 * 
 * @param dnode the struct to be destroyed
 */
void dnode_destroy(dnode_t* dnode);

/**
 * Adds an option (dedge) to dnode's list of available responses
 * 
 * @param dnode the dnode whose list to add to
 * @param dedge the option to add to the list
 */
void dnode_add_option(dnode_t* dnode, struct dedge_t* dedge);

/**
 * Removes an option (dedge) to the list of available responses
 * 
 * @param dnode the dnode whose list to remove from
 * @param dedge the option to remove from the list
 */
void dnode_remove_option(dnode_t* dnode, struct dedge_t* dedge);

/**
 * Copies the contents of the structure at source into a new dnode structure
 * 
 * @param source the location in memory to copy dnode from
 * @return a location in memory with identical contents to source
 */
dnode_t* dnode_copy(dnode_t* source);

/**
 * Prints info about a dnode to stdout
 * 
 * @param dnode the dnode structure to print info about
 */
void dnode_print_info(dnode_t* dnode);

/**
 * Prints a dnode structure in tree representation
 * 
 * @param dnode the graph structure to print
 * @param depth current depth of the tree, affects how much white space is printed
 */
void dnode_print_tree(dnode_t* dnode, int depth);

#endif /* __DNODE_H */
