#include "dedge.h"

/**
 * Allocates space for a dedge struct in memory
 * 
 * @return a pointer to a newly created memory block
 */
dedge_t* dedge_create()
{
    dedge_t* dedge = (dedge_t*)malloc(sizeof(dedge_t));
    dedge->text = (char*)malloc(sizeof(char) * STR_LENGTH);
    strcpy(dedge->text, "\0");
    dedge->start = NULL;
    dedge->end = NULL;

    return dedge;
}

/**
 * Destroys a dedge struct, freeing its space in memory
 * 
 * @param dedge the struct to be destroyed
 */
void dedge_destroy(dedge_t* dedge)
{
    free(dedge->text);

    free(dedge);
}

/**
 * Copies the contents of the structure at source into a new dedge structure
 * 
 * @param source the location in memory to copy dedge from
 * @return a location in memory with identical contents to source
 */
dedge_t* dedge_copy(dedge_t* source)
{
    dedge_t* destination = (dedge_t*)malloc(sizeof(dedge_t));
    destination->text = (char*)malloc(sizeof(char) * STR_LENGTH);

    strcpy(destination->text, source->text);
    destination->start = source->start;
    destination->end = source->end;

    return destination;
}

/**
 * Prints info about a dedge to stdout
 * 
 * @param dedge the dedge structure to print info about
 */
void dedge_print_info(dedge_t* dedge)
{
    printf("dedge text: %s\n", dedge->text);
    printf("start text: %s\n", dedge->start->text);
    printf("end text: %s\n", dedge->end->text);
}

/**
 * Prints a dedge structure in tree representation
 * 
 * @param dedge the graph structure to print
 * @param depth current depth of the tree, affects how much white space is printed
 */
void dedge_print_tree(dedge_t* dedge, int depth)
{
    if(dedge == NULL)
    {
        return;
    }

    for(int tab_count = 0; tab_count < depth; tab_count++)
    {
        printf("    ");
    }

    printf("%s\n", dedge->text);

    dnode_print_tree(dedge->end, depth + 1);
}
