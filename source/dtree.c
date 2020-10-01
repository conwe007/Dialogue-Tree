#include "dtree.h"

/**
 * Allocates memory for a dtree struct
 * 
 * @return a pointer to memory for a dtree struct
 */
dtree_t* dtree_create()
{
    dtree_t* dtree = (dtree_t*)malloc(sizeof(dtree_t));

    dtree->floating_dnodes = NULL;
    dtree->num_floating_dnodes = 0;
    dtree->floating_dedges = NULL;
    dtree->num_floating_dedges = 0;
    dtree->dgraph = dgraph_create();

    return dtree;
}

/**
 * Frees a dtree struct's memory
 * 
 * @param dtree the dtree struct to destroy
 */
void dtree_destroy(dtree_t* dtree)
{
    for(int index_floating_dnodes = 0; index_floating_dnodes < dtree->num_floating_dnodes; index_floating_dnodes++)
    {
        dnode_destroy(dtree->floating_dnodes[index_floating_dnodes]);
    }

    for(int index_floating_dedges = 0; index_floating_dedges < dtree->num_floating_dnodes; index_floating_dedges++)
    {
        dedge_destroy(dtree->floating_dedges[index_floating_dedges]);
    }

    dgraph_destroy(dtree->dgraph);

    free(dtree);
}

/**
 * Adds a dnode with "text" to the floating dnodes list
 * 
 * @param dtree the dtree to add the floating node to
 * @param text the text to add to the floating node
 */
void dtree_add_dnode(dtree_t* dtree, char* text)
{
    dnode_t* dnode_new = dnode_create();
    strcpy(dnode_new->text, text);

    dtree->num_floating_dnodes++;
    dnode_t** floating_dnodes_new = (dnode_t**)malloc(sizeof(dnode_t*) * dtree->num_floating_dnodes);

    // copy over existing floating dnodes to new array
    for(int index_floating_dnodes = 0; index_floating_dnodes < dtree->num_floating_dnodes - 1; index_floating_dnodes++)
    {
        floating_dnodes_new[index_floating_dnodes] = dtree->floating_dnodes[index_floating_dnodes];
    }

    // add new dnode to the end of new array
    floating_dnodes_new[dtree->num_floating_dnodes - 1] = dnode_new;

    // point floating_dnodes to the new array
    free(dtree->floating_dnodes);
    dtree->floating_dnodes = floating_dnodes_new;
}

/**
 * Adds a dedge with "text" to the floating dedges list
 * 
 * @param dedge the dtree to add the floating dedge to
 * @param text the text to add to the floating dedge
 */
void dtree_add_dedge(dtree_t* dtree, char* text)
{
    dedge_t* dedge_new = dedge_create();
    strcpy(dedge_new->text, text);

    dtree->num_floating_dedges++;
    dedge_t** floating_dedges_new = (dedge_t**)malloc(sizeof(dedge_t*) * dtree->num_floating_dedges);

    // copy over existing floating dedges to new array
    for(int index_floating_dedges = 0; index_floating_dedges < dtree->num_floating_dedges - 1; index_floating_dedges++)
    {
        floating_dedges_new[index_floating_dedges] = dtree->floating_dedges[index_floating_dedges];
    }

    // add new dedge to the end of new array
    floating_dedges_new[dtree->num_floating_dedges - 1] = dedge_new;

    // point floating_dedges to the new array
    free(dtree->floating_dedges);
    dtree->floating_dedges = floating_dedges_new;
}

/**
 * Removes the dnode at index from floating dnodes list
 * 
 * @param dtree the dtree to remove the dnode from
 * @param index_dnode the index of the dnode to remove
 */
void dtree_remove_dnode(dtree_t* dtree, int index_dnode)
{
    dtree->num_floating_dnodes--;
    dnode_t** floating_dnodes_new = (dnode_t**)malloc(sizeof(dnode_t*) * dtree->num_floating_dnodes);

    // copy over existing array to temporary array, skipping the entry to delete
    int index_floating_dnodes_new = 0;
    for(int index_floating_dnodes = 0; index_floating_dnodes < dtree->num_floating_dnodes + 1; index_floating_dnodes++)
    {
        if(index_floating_dnodes != index_dnode)
        {
            floating_dnodes_new[index_floating_dnodes_new] = dtree->floating_dnodes[index_floating_dnodes];
            index_floating_dnodes_new++;
        }
    }

    dnode_destroy(dtree->floating_dnodes[index_dnode]);
    free(dtree->floating_dnodes);
    dtree->floating_dnodes = floating_dnodes_new;
}

/**
 * Removes the dedge at index from floating dedges list
 * 
 * @param dtree the dtree to remove the dedge from
 * @param index_dnode the index of the dedge to remove
 */
void dtree_remove_dedge(dtree_t* dtree, int index_dedge)
{
    dtree->num_floating_dedges--;
    dedge_t** floating_dedges_new = (dedge_t**)malloc(sizeof(dedge_t*) * dtree->num_floating_dedges);

    // copy over existing array to temporary array, skipping the entry to delete
    int index_floating_dedges_new = 0;
    for(int index_floating_dedges = 0; index_floating_dedges < dtree->num_floating_dedges + 1; index_floating_dedges++)
    {
        if(index_floating_dedges != index_dedge)
        {
            floating_dedges_new[index_floating_dedges_new] = dtree->floating_dedges[index_floating_dedges];
            index_floating_dedges_new++;
        }
    }

    dedge_destroy(dtree->floating_dedges[index_dedge]);
    free(dtree->floating_dedges);
    dtree->floating_dedges = floating_dedges_new;
}

/**
 * Sets the dnode at index to be the root of the dtree (dgraph index 0)
 * 
 * @param dtree the dtree to set the root of
 * @param index_dnode the index of the dnode in floating dnodes
 */
void dtree_set_root_dnode(dtree_t* dtree, int index_dnode)
{
    if(dtree->dgraph->num_dnodes > 0)
    {
        dtree->dgraph->dnodes[0] = dnode_copy(dtree->floating_dnodes[index_dnode]);
    } 
    else
    {
        dgraph_add_dnode(dtree->dgraph, dnode_copy(dtree->floating_dnodes[index_dnode]));
    }

    dtree_remove_dnode(dtree, index_dnode);
}

/**
 * Adds a dedge from floating dedges and attaches it as an option to a dnode in dgraph
 * 
 * @param dtree the dtree to access members from
 * @param index_dnode the index of the dnode in dgraph
 * @param index_dedge the index of the dedge in floating dedges
 */
void dtree_add_dnode_option(dtree_t* dtree, int index_dnode, int index_dedge)
{
    if(index_dnode < 0 || index_dnode >= dtree->dgraph->num_dnodes)
    {
        fprintf(stderr, "error: index_dnode is out of range in dtree_add_dnode_option()\n");
        return;
    }

    if(index_dedge < 0 || index_dedge >= dtree->num_floating_dedges)
    {
        fprintf(stderr, "error: index_dedge is out of range in dtree_add_dnode_option\n");
        return;
    }

    dgraph_add_dedge(dtree->dgraph, dedge_copy(dtree->floating_dedges[index_dedge]));
    dnode_add_option(dtree->dgraph->dnodes[index_dnode], dtree->dgraph->dedges[dtree->dgraph->num_dedges - 1]);
    dtree_remove_dedge(dtree, index_dedge);
}

/**
 * Adds a dnode from floating dnodes and attaches it as the end point of a dedge in dgraph
 * 
 * @param dtree the dtree to access members from
 * @param index_dedge the index of the dedge in dgraph
 * @param index_dnode the index of the dnode in floating dnodes
 */
void dtree_add_dedge_end(dtree_t* dtree, int index_dedge, int index_dnode)
{

}

/**
 * Returns a list of strings representing the text fields of the floating dnodes
 * 
 * @param dtree the dtree to pull the floating node text from
 * @return a list of dnode texts
 */
char** dtree_get_floating_dnodes(dtree_t* dtree)
{
    

    return NULL;
}

/**
 * Returns a list of strings representing the text fields of the floating dedges
 * 
 * @param dtree the dtree to pull the floating node text from
 * @return a list of dedge texts
 */
char** dtree_get_floating_dedges(dtree_t* dtree)
{


    return NULL;
}

/**
 * Returns a list of strings representing the text fields of the dnodes in dgraph
 * 
 * @param dtree the dtree to access dgraph from
 * @return a list of dnode texts
 */
char** dtree_get_dgraph_dnodes(dtree_t* dtree)
{


    return NULL;
}

/**
 * Returns a list of strings representing the text fields of the dedges in dgraph
 * 
 * @param dtree the dtree to access dgraph from
 * @return a list of dedge texts
 */
char** dtree_get_dgraph_dedges(dtree_t* dtree)
{


    return NULL;
}


