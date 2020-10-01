#include "dnode.h"

/**
 * Allocates space for a dnode struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dnode_t* dnode_create()
{
    dnode_t* dnode = (dnode_t*)malloc(sizeof(dnode_t));
    dnode->text = (char*)malloc(sizeof(char) * STR_LENGTH);
    strcpy(dnode->text, "\0");
    dnode->options = NULL;
    dnode->num_options = 0;

    return dnode;
}

/**
 * Destroys a dnode struct, freeing its space in memory
 * 
 * @param dnode the struct to be destroyed
 */
void dnode_destroy(dnode_t* dnode)
{
    free(dnode->text);
    free(dnode->options);

    free(dnode);
}

/**
 * Adds an option (dedge) to dnode's list of available responses
 * 
 * @param dnode the dnode whose list to add to
 * @param dedge the option to add to the list
 */
void dnode_add_option(dnode_t* dnode, dedge_t* dedge)
{
    dnode->num_options++;
    dedge_t** temp = (dedge_t**)malloc(sizeof(dedge_t*) * dnode->num_options);

    // copy over existing options to temporary array
    for(int index_option = 0; index_option < dnode->num_options - 1; index_option++)
    {
        temp[index_option] = dnode->options[index_option];
    }

    // add new entry to the end of the temporary array
    temp[dnode->num_options - 1] = dedge;

    // free the existing pointer and redirect it to the new array
    free(dnode->options);
    dnode->options = temp;
}

/**
 * Removes an option (dedge) to the list of available responses
 * 
 * @param dnode the dnode whose list to remove from
 * @param dedge the option to remove from the list
 */
void dnode_remove_option(dnode_t* dnode, dedge_t* dedge)
{
    dnode->num_options--;
    dedge_t** temp = (dedge_t**)malloc(sizeof(dedge_t*) * dnode->num_options);

    // copy over existing options to temporary array
    int index_temp = 0;
    for(int index_option = 0; index_option < dnode->num_options + 1; index_option++)
    {
        if(dnode->options[index_option] != dedge)
        {
            temp[index_temp] = dnode->options[index_option];
            index_temp++;
        }
    }

    free(dnode->options);
    dnode->options = temp;
}

/**
 * Copies the contents of the structure at source into a new dnode structure
 * 
 * @param source the location in memory to copy dnode from
 * @return a location in memory with identical contents to source
 */
dnode_t* dnode_copy(dnode_t* source)
{
    dnode_t* destination = (dnode_t*)malloc(sizeof(dnode_t));
    destination->text = (char*)malloc(sizeof(char) * STR_LENGTH);

    strcpy(destination->text, source->text);
    destination->num_options = source->num_options;
    destination->options = (dedge_t**)malloc(sizeof(dedge_t*) * destination->num_options);

    for(int index_option = 0; index_option < destination->num_options; index_option++)
    {
        destination->options[index_option] = source->options[index_option];
    }

    return destination;
}

/**
 * Prints info about a dnode to stdout
 * 
 * @param dnode the dnode structure to print info about
 */
void dnode_print_info(dnode_t* dnode)
{
    printf("dnode text: %s\n", dnode->text);
    printf("num options: %i\n", dnode->num_options);
    
    for(int index_option = 0; index_option < dnode->num_options; index_option++)
    {
        printf("option %i text: %s\n", index_option, dnode->options[index_option]->text);
    }
}

/**
 * Prints a dnode structure in tree representation
 * 
 * @param dnode the graph structure to print
 * @param depth current depth of the tree, affects how much white space is printed
 */
void dnode_print_tree(dnode_t* dnode, int depth)
{
    if(dnode == NULL)
    {
        return;
    }

    for(int tab_count = 0; tab_count < depth; tab_count++)
    {
        printf("    ");
    }

    printf("%s\n", dnode->text);

    for(int index_option = 0; index_option < dnode->num_options; index_option++)
    {
        dedge_print_tree(dnode->options[index_option], depth + 1);
    }
}
