#include "main.h"

int main(int argc, char* argv[])
{
    // dnode_t* dnode_start = dnode_create();
    // strcpy(dnode_start->text, "dnode start text 1 is here");

    // dnode_print_info(dnode_start);
    // printf("\n");


    // dnode_t* dnode_end = dnode_create();
    // strcpy(dnode_end->text, "dnode end text 1 is here");

    // dnode_print_info(dnode_end);
    // printf("\n");


    // dedge_t* dedge1 = dedge_create();
    // strcpy(dedge1->text, "dedge text 1 is here");
    // dedge1->start = dnode_start;
    // dedge1->end = dnode_end;
    // dnode_add_option(dnode_start, dedge1);

    // dnode_print_info(dnode_start);
    // dedge_print_info(dedge1);
    // printf("\n");
    

    // dedge_t* dedge2 = dedge_create();
    // strcpy(dedge2->text, "dedge text 2 is here");
    // dedge2->start = dnode_start;
    // dedge2->end = dnode_end;
    // dnode_add_option(dnode_start, dedge2);

    // dnode_print_info(dnode_start);
    // dedge_print_info(dedge2);
    // printf("\n");


    // strcpy(dnode_start->text, "dnode start text 1 is changed");
    // strcpy(dedge1->text, "dedge text 1 is changed");
    // strcpy(dedge2->text, "dedge text 2 is changed");

    // dnode_print_info(dnode_start);
    // printf("\n");


    //dnode_remove_option(dnode_start, dedge1);

    // dnode_print_info(dnode_start);
    // dedge_print_info(dedge1);
    // dedge_print_info(dedge2);
    // printf("\n");


    dnode_t* dnode0 = dnode_create();
    dnode_t* dnode1 = dnode_create();
    dnode_t* dnode2 = dnode_create();
    dnode_t* dnode3 = dnode_create();
    dnode_t* dnode4 = dnode_create();

    dedge_t* dedge0 = dedge_create();
    dedge_t* dedge1 = dedge_create();
    dedge_t* dedge2 = dedge_create();
    dedge_t* dedge3 = dedge_create();
    dedge_t* dedge4 = dedge_create();

    strcpy(dnode0->text, "dnode0");
    strcpy(dnode1->text, "dnode1");
    strcpy(dnode2->text, "dnode2");
    strcpy(dnode3->text, "dnode3");
    strcpy(dnode4->text, "dnode4");

    dnode_add_option(dnode0, dedge0);
    dnode_add_option(dnode0, dedge1);
    dnode_add_option(dnode2, dedge2);
    dnode_add_option(dnode2, dedge3);
    dnode_add_option(dnode3, dedge4);

    strcpy(dedge0->text, "dedge0");
    strcpy(dedge1->text, "dedge1");
    strcpy(dedge2->text, "dedge2");
    strcpy(dedge3->text, "dedge3");
    strcpy(dedge4->text, "dedge4");

    dedge0->start = dnode0;
    dedge0->end = dnode1;
    dedge1->start = dnode0;
    dedge1->end = dnode2;
    dedge2->start = dnode2;
    dedge2->end = dnode3;
    dedge3->start = dnode2;
    dedge3->end = dnode4;
    dedge4->start = dnode3;
    dedge4->end = dnode1;

    dgraph_t* dgraph = dgraph_create();

    dgraph_add_dnode(dgraph, dnode4);
    dgraph_add_dnode(dgraph, dnode3);
    dgraph_add_dnode(dgraph, dnode2);
    dgraph_add_dnode(dgraph, dnode1);
    dgraph_add_dnode(dgraph, dnode0);
    
    dgraph_add_dedge(dgraph, dedge4);
    dgraph_add_dedge(dgraph, dedge3);
    dgraph_add_dedge(dgraph, dedge2);
    dgraph_add_dedge(dgraph, dedge1);
    dgraph_add_dedge(dgraph, dedge0);
    
    dgraph_update_adj_matrix(dgraph);

    dgraph_print_info(dgraph);
    printf("\n");

    // dgraph_print_tree(dgraph);

    // dgraph_destroy(dgraph);
    
    // int w = 60;
    // while(w > 0)
    // {
    //     clock_t end = animate_clock_val_after_ms(100);
    //     printf("%i\n", (int)clock());
    //     w--;
    //     while(clock() < end);
    // }

    // animate_print_string_delay_ms("Hello there it is me.", 50);
    // printf("\n");

    return 0;
}
