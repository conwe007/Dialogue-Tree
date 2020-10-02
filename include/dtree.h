#ifndef __DTREE_H
#define __DTREE_H

#include "dgraph.h"

#define LIST_END ""

typedef struct
{
    // a list of dnodes not associated with a dgraph
    dnode_t** floating_dnodes;
    int num_floating_dnodes;

    // a list of dedges not associated with a dgraph
    dedge_t** floating_dedges;
    int num_floating_dedges;

    dgraph_t* dgraph;
} dtree_t;

typedef struct
{
    char** text;
    int length;
} tlist_t;


/**
 * Allocates memory for a dtree struct
 * 
 * @return a pointer to memory for a dtree struct
 */
dtree_t* dtree_create();

/**
 * Frees a dtree struct's memory
 * 
 * @param dtree the dtree struct to destroy
 */
void dtree_destroy(dtree_t* dtree);

/**
 * Adds a dnode with "text" to the floating dnodes list
 * 
 * @param dtree the dtree to add the floating node to
 * @param text the text to add to the floating node
 */
void dtree_add_dnode(dtree_t* dtree, char* text);

/**
 * Adds a dedge with "text" to the floating dedges list
 * 
 * @param dedge the dtree to add the floating dedge to
 * @param text the text to add to the floating dedge
 */
void dtree_add_dedge(dtree_t* dtree, char* text);

/**
 * Removes the dnode at index from floating dnodes list
 * 
 * @param dtree the dtree to remove the dnode from
 * @param index_dnode the index of the dnode to remove
 */
void dtree_remove_dnode(dtree_t* dtree, int index_dnode);

/**
 * Removes the dedge at index from floating dedges list
 * 
 * @param dtree the dtree to remove the dedge from
 * @param index_dnode the index of the dedge to remove
 */
void dtree_remove_dedge(dtree_t* dtree, int index_dedge);

/**
 * Sets the dnode at index to be the root of the dtree (dgraph index 0)
 * 
 * @param dtree the dtree to set the root of
 * @param index_dnode the index of the dnode in floating dnodes
 */
void dtree_set_root_dnode(dtree_t* dtree, int index_dnode);

/**
 * Adds a dedge from floating dedges and attaches it as an option to a dnode in dgraph
 * 
 * @param dtree the dtree to access members from
 * @param index_dnode the index of the dnode in dgraph
 * @param index_dedge the index of the dedge in floating dedges
 */
void dtree_add_dnode_option(dtree_t* dtree, int index_dnode, int index_dedge);

/**
 * Adds a dnode from floating dnodes and attaches it as the end point of a dedge in dgraph
 * 
 * @param dtree the dtree to access members from
 * @param index_dedge the index of the dedge in dgraph
 * @param index_dnode the index of the dnode in floating dnodes
 */
void dtree_add_dedge_end(dtree_t* dtree, int index_dedge, int index_dnode);

/**
 * Returns a list of strings representing the text fields of the floating dnodes
 * 
 * @param dtree the dtree to pull the floating node text from
 * @return a list of dnode texts
 */
tlist_t* dtree_get_floating_dnodes(dtree_t* dtree);

/**
 * Returns a list of strings representing the text fields of the floating dedges
 * 
 * @param dtree the dtree to pull the floating node text from
 * @return a list of dedge texts
 */
tlist_t* dtree_get_floating_dedges(dtree_t* dtree);

/**
 * Returns a list of strings representing the text fields of the dnodes in dgraph
 * 
 * @param dtree the dtree to access dgraph from
 * @return a list of dnode textsnated by LIST_END
 */
tlist_t* dtree_get_dgraph_dnodes(dtree_t* dtree);

/**
 * Returns a list of strings representing the text fields of the dedges in dgraph
 * 
 * @param dtree the dtree to access dgraph from
 * @return a list of dedge texts
 */
tlist_t* dtree_get_dgraph_dedges(dtree_t* dtree);

/**
 * Destroys a character array such as those returned by the dtree_get_ functions
 * 
 * @param array the array to destroy
 */
void dtree_char_array_destroy(tlist_t* tlist);

#endif /* __DTREE_H */
