#ifndef __DGRAPH_H
#define __DGRAPH_H

#include "dnode.h"
#include "dedge.h"
#include <stdbool.h>
#include <stdlib.h>

#define NO_PATH -1
#define INDEX_INVALID -1

typedef struct
{
    int state;

    dnode_t** dnodes;
    int num_dnodes;
    dedge_t** dedges;
    int num_dedges;

    // adjacency matrix is a [num_dnodes] x [num_dnodes] array of integers
    // each row corresponds to the start dnode of a dedge
    // each column corresponds to the end dnode of a dedge
    // each cell contains the index in dedges of the dedge with start and end dnode indexes
    int** adj_matrix;
} dgraph_t;

/**
 * Allocates space for a dgraph struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dgraph_t* dgraph_create();

/**
 * Destroys a dgraph struct, freeing its space in memory
 * 
 * @param dgraph the struct to be destroyed
 */
void dgraph_destroy(dgraph_t* dgraph);

/**
 * Adds a dnode to the nodes list
 * 
 * @param dgraph the graph to add a dnode to
 * @param dnode the dnode to add to the list
 */
void dgraph_add_dnode(dgraph_t* dgraph, dnode_t* dnode);

/**
 * Removes a dnode from the nodes list
 * 
 * @param dgraph the graph to remove a dnode from
 * @param dnode the dnode to remove from the list
 */
void dgraph_remove_dnode(dgraph_t* dgraph, dnode_t* dnode);

/**
 * Adds a dedge to the nodes list
 * 
 * @param dgraph the graph to add a dedge to
 * @param dedge the dedge to add to the list
 */
void dgraph_add_dedge(dgraph_t* dgraph, dedge_t* dedge);

/**
 * Removes a dedge from the nodes list
 * 
 * @param dgraph the graph to remove a dedge from
 * @param dedge the dedge to remove from the list
 */
void dgraph_remove_dedge(dgraph_t* dgraph, dedge_t* dedge);

/**
 * Updates the adjacency matrix to account for current nodes and edges
 * 
 * @param dgraph the graph whose adjacency matrix will be updated
 */
void dgraph_update_adj_matrix(dgraph_t* dgraph);

/**
 * Returns the text associated with the dnode at the specified index
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dnode the index of the dnode to get text from
 * @return a character string with text from the dnode
 */
char* dgraph_get_dnode_text(dgraph_t* dgraph, int index_dnode);

/**
 * Returns the text associated with the dedge at the specified index
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dedge the index of the dedge to get text from
 * @return a character string with text from the dedge
 */
char* dgraph_get_dedge_text(dgraph_t* dgraph, int index_dedge);

/**
 * Returns a list of the indexes of dedges available as options to the dnode at index_dnode
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dnode the index of the dnode to get a list of options from
 * @return a list of indexes corresponding to the options of the specified dnode, terminated with NO_PATH
 */
int* dgraph_get_dnode_options(dgraph_t* dgraph, int index_dnode);

/**
 * Returns the index of the dnode that is the endpoint of the dedge at index_dedge
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dedge the index of the dedge whose end dnode is desired
 * @return the index of the dnode that is the endpoint of the specified dedge
 */
int dgraph_get_dedge_end_dnode(dgraph_t* dgraph, int index_dedge);

/**
 * Prints info about a dgraph structure
 * 
 * @param dgraph the dgraph structure to print
 */
void dgraph_print_info(dgraph_t* dgraph);

/**
 * Prints a dgraph structure in tree representation
 * 
 * @param dgraph the graph structure to print
 */
void dgraph_print_tree(dgraph_t* dgraph);

#endif /* __DGRAPH_H */
