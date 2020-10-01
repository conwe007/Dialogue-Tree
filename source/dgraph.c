#include "dgraph.h"

/**
 * Allocates space for a dgraph struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dgraph_t* dgraph_create()
{
    dgraph_t* dgraph = (dgraph_t*)malloc(sizeof(dgraph_t));

    dgraph->dnodes = NULL;
    dgraph->num_dnodes = 0;
    dgraph->dedges = NULL;
    dgraph->num_dedges = 0;

    dgraph->adj_matrix = NULL;

    return dgraph;
}

/**
 * Destroys a dgraph struct, freeing its space in memory
 * 
 * @param dgraph the struct to be destroyed
 */
void dgraph_destroy(dgraph_t* dgraph)
{
    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
    {
        dnode_destroy(dgraph->dnodes[index_dnode]);
    }

    free(dgraph->dnodes);

    for(int index_dedge = 0; index_dedge < dgraph->num_dedges; index_dedge++)
    {
        dedge_destroy(dgraph->dedges[index_dedge]);
    }

    free(dgraph->dedges);

    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
    {
        free(dgraph->adj_matrix[index_dnode]);
    }

    free(dgraph->adj_matrix);

    free(dgraph);
}

/**
 * Adds a dnode to the nodes list
 * 
 * @param dgraph the graph to add a dnode to
 * @param dnode the dnode to add to the list
 */
void dgraph_add_dnode(dgraph_t* dgraph, dnode_t* dnode)
{
    dgraph->num_dnodes++;

    dnode_t** new_dnodes = (dnode_t**)malloc(sizeof(dnode_t*) * dgraph->num_dnodes);
    
    // copy existing dnode list into new dnode list
    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes - 1; index_dnode++)
    {
        new_dnodes[index_dnode] = dgraph->dnodes[index_dnode];
    }

    // add new dnode to the end of the new dnode list
    new_dnodes[dgraph->num_dnodes - 1] = dnode;

    free(dgraph->dnodes);
    dgraph->dnodes = new_dnodes;
}

/**
 * Removes a dnode from the nodes list
 * 
 * @param dgraph the graph to remove a dnode from
 * @param dnode the dnode to remove from the list
 */
void dgraph_remove_dnode(dgraph_t* dgraph, dnode_t* dnode)
{
    dgraph->num_dnodes--;

    dnode_t** new_dnodes = (dnode_t**)malloc(sizeof(dnode_t*) * dgraph->num_dnodes);

    // copy all but the dnode to remove into new dnode list
    int index_new_dnode = 0;
    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes + 1; index_dnode++)
    {
        if(dgraph->dnodes[index_dnode] != dnode)
        {
            new_dnodes[index_new_dnode] = dgraph->dnodes[index_dnode];
            index_new_dnode++;
        }
    }

    free(dgraph->dnodes);
    dgraph->dnodes = new_dnodes;
}

/**
 * Adds a dedge to the nodes list
 * 
 * @param dgraph the graph to add a dedge to
 * @param dedge the dedge to add to the list
 */
void dgraph_add_dedge(dgraph_t* dgraph, dedge_t* dedge)
{
    dgraph->num_dedges++;

    dedge_t** new_dedges = (dedge_t**)malloc(sizeof(dedge_t*) * dgraph->num_dedges);
    
    // copy existing dedge list into new dnode list
    for(int index_dedge = 0; index_dedge < dgraph->num_dedges - 1; index_dedge++)
    {
        new_dedges[index_dedge] = dgraph->dedges[index_dedge];
    }

    // add new dedge to the end of the new dnode list
    new_dedges[dgraph->num_dedges - 1] = dedge;

    free(dgraph->dedges);
    dgraph->dedges = new_dedges;
}

/**
 * Removes a dedge from the nodes list
 * 
 * @param dgraph the graph to remove a dedge from
 * @param dedge the dedge to remove from the list
 */
void dgraph_remove_dedge(dgraph_t* dgraph, dedge_t* dedge)
{
    dgraph->num_dedges--;

    dedge_t** new_dedges = (dedge_t**)malloc(sizeof(dedge_t*) * dgraph->num_dedges);

    // copy all but the dedge to remove into new dnode list
    int index_new_dedge = 0;
    for(int index_dedge = 0; index_dedge < dgraph->num_dedges + 1; index_dedge++)
    {
        if(dgraph->dedges[index_dedge] != dedge)
        {
            new_dedges[index_new_dedge] = dgraph->dedges[index_dedge];
            index_new_dedge++;
        }
    }

    free(dgraph->dedges);
    dgraph->dedges = new_dedges;
}

/**
 * Updates the adjacency matrix to account for current nodes and edges
 * 
 * @param dgraph the graph whose adjacency matrix will be updated
 */
void dgraph_update_adj_matrix(dgraph_t* dgraph)
{
    // free previous adjacency matrix since a new one will be created
    free(dgraph->adj_matrix);
    
    // allocate space for adjacency matrix
    // adjacency matrix is a [num_dnodes] x [num_dnodes] array of integers
    // each row corresponds to the start dnode of a dedge
    // each column corresponds to the end dnode of a dedge
    // each cell contains the index in dedges list of the dedge with start and end dnode indexes
    dgraph->adj_matrix = (int**)malloc(sizeof(int*) * dgraph->num_dnodes);
    for(int index_dnode_start = 0; index_dnode_start < dgraph->num_dnodes; index_dnode_start++)
    {
        dgraph->adj_matrix[index_dnode_start] = (int*)malloc(sizeof(int) * dgraph->num_dnodes);
    
        for(int index_dnode_end = 0; index_dnode_end < dgraph->num_dnodes; index_dnode_end++)
        {
            // initalize to NO_PATH to indicate there is no dedge between the dnodes
            dgraph->adj_matrix[index_dnode_start][index_dnode_end] = NO_PATH;
        }
    }

    int adj_matrix_row = INDEX_INVALID; // adj_matrix_row corresponds to a start node
    int adj_matrix_col = INDEX_INVALID; // adj_matrix_col corresponds to an end node

    // loop through each dedge of the dgraph to populate adjacency matrix
    for(int index_dedge = 0; index_dedge < dgraph->num_dedges; index_dedge++)
    {
        // check each dnode of the dgraph against the dedge's start and end nodes
        for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
        {
            if(dgraph->dedges[index_dedge]->start == dgraph->dnodes[index_dnode])
            {
                adj_matrix_row = index_dnode;
            }

            if(dgraph->dedges[index_dedge]->end == dgraph->dnodes[index_dnode])
            {
                adj_matrix_col = index_dnode;
            }
        }

        dgraph->adj_matrix[adj_matrix_row][adj_matrix_col] = index_dedge;

        // reset to invalid index so a crash occurs if something went wrong
        adj_matrix_row = INDEX_INVALID;
        adj_matrix_col = INDEX_INVALID;
    }
}

/**
 * Returns the text associated with the dnode at the specified index
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dnode the index of the dnode to get text from
 * @return a character string with text from the dnode
 */
char* dgraph_get_dnode_text(dgraph_t* dgraph, int index_dnode)
{
    return dgraph->dnodes[index_dnode]->text;
}

/**
 * Returns the text associated with the dedge at the specified index
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dedge the index of the dedge to get text from
 * @return a character string with text from the dedge
 */
char* dgraph_get_dedge_text(dgraph_t* dgraph, int index_dedge)
{
    return dgraph->dedges[index_dedge]->text;
}

/**
 * Returns a list of the indexes of dedges available as options to the dnode at index_dnode
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dnode the index of the dnode to get a list of options from
 * @return a list of indexes corresponding to the options of the specified dnode, terminated with NO_PATH
 */
int* dgraph_get_dnode_options(dgraph_t* dgraph, int index_dnode)
{
    // size is num_options + 1 to allow space for terminating NO_PATH
    int* list_options = (int*)malloc(sizeof(int) * (dgraph->dnodes[index_dnode]->num_options + 1));
    int index_list_options = 0;
    
    for(int index_adj_matrix = 0; index_adj_matrix < dgraph->num_dnodes; index_adj_matrix++)
    {
        if(dgraph->adj_matrix[index_dnode][index_adj_matrix] != NO_PATH)
        {
            list_options[index_list_options] = dgraph->adj_matrix[index_dnode][index_adj_matrix];
            index_list_options++;
        }
    }

    list_options[index_list_options] = NO_PATH;

    return list_options;
}

/**
 * Returns the index of the dnode that is the endpoint of the dedge at index_dedge
 * 
 * @param dgraph the dgraph struct to search in
 * @param index_dedge the index of the dedge whose end dnode is desired
 * @return the index of the dnode that is the endpoint of the specified dedge
 */
int dgraph_get_dedge_end_dnode(dgraph_t* dgraph, int index_dedge)
{
    int index_end = -1;

    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
    {
        if(dgraph->dnodes[index_dnode] == dgraph->dedges[index_dedge]->end)
        {
            index_end = index_dnode;
        }
    }

    return index_end;
}

/**
 * Prints info about a dgraph structure
 * 
 * @param dgraph the dgraph structure to print
 */
void dgraph_print_info(dgraph_t* dgraph)
{
    printf("dgraph:\n\n");

    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
    {
        printf("dnode %i: %s\n", index_dnode, dgraph->dnodes[index_dnode]->text);
    }
    printf("\n");

    for(int index_dedge = 0; index_dedge < dgraph->num_dedges; index_dedge++)
    {
        printf("dedge %i: %s\n", index_dedge, dgraph->dedges[index_dedge]->text);
    }
    printf("\n");

    printf("adj_matrix:\n");
    for(int index_dnode = 0; index_dnode < dgraph->num_dnodes; index_dnode++)
    {
        for(int index_dedge = 0; index_dedge < dgraph->num_dedges; index_dedge++)
        {
            printf("%3i", dgraph->adj_matrix[index_dnode][index_dedge]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Prints a dgraph structure in tree representation
 * 
 * @param dgraph the graph structure to print
 */
void dgraph_print_tree(dgraph_t* dgraph)
{
    dnode_print_tree(dgraph->dnodes[0], 0);
}
