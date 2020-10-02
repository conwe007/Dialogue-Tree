#include "test.h"

int main(int argc, char* argv[])
{
    test_dnode();
    test_dedge();
    test_dgraph();
    test_dtree();

    return 0;
}

/**
 * Unit test for dnode functions
 */
void test_dnode()
{
    /* dnode tests */
    fprintf(stderr, "*** dnode tests ***\n");

    // dnode_create test
    bool dnode_create_pass = true;
    dnode_t* dnode0 = dnode_create();
    dnode_create_pass &= (strcmp(dnode0->text, "\0") == 0);
    dnode_create_pass &= (dnode0->num_options == 0);
    dnode_create_pass &= (dnode0->options == NULL);
    fprintf(stderr, "test dnode_create: %s\n", (dnode_create_pass ? "pass" : "fail"));

    // dnode_destroy test
    bool dnode_destroy_pass = true;
    dnode_destroy(dnode0);
    dnode0 = NULL;
    dnode_destroy_pass &= (dnode0 == NULL);
    fprintf(stderr, "test dnode_destroy: %s\n", (dnode_destroy_pass ? "pass" : "fail"));
    
    // dnode_add_option test
    bool dnode_add_option_pass = true;
    dnode0 = dnode_create();
    dedge_t* option0 = dedge_create();
    dedge_t* option1 = dedge_create();
    dnode_add_option(dnode0, option0);
    dnode_add_option_pass &= (dnode0->options[0] == option0);
    dnode_add_option_pass &= (dnode0->num_options == 1);
    dnode_add_option(dnode0, option1);
    dnode_add_option_pass &= (dnode0->options[0] == option0);
    dnode_add_option_pass &= (dnode0->options[1] == option1);
    dnode_add_option_pass &= (dnode0->num_options == 2);
    fprintf(stderr, "test dnode_add_option: %s\n", (dnode_add_option_pass ? "pass" : "fail"));

    // dnode_remove_option test
    bool dnode_remove_option_pass = true;
    dnode_remove_option(dnode0, option0);
    dnode_remove_option_pass &= (dnode0->options[0] == option1);
    dnode_remove_option_pass &= (dnode0->num_options == 1);
    dnode_remove_option(dnode0, option1);
    dnode_remove_option_pass &= (dnode0->num_options == 0);
    fprintf(stderr, "test dnode_remove_option: %s\n", (dnode_remove_option_pass ? "pass" : "fail"));

    // dnode_copy test
    bool dnode_copy_pass = true;
    strcpy(dnode0->text, "dnode0 text");
    dnode_add_option(dnode0, option0);
    dnode_add_option(dnode0, option1);
    dnode_t* dnode1 = dnode_copy(dnode0);
    dnode_copy_pass &= (strcmp(dnode1->text, dnode0->text) == 0);
    dnode_copy_pass &= (dnode0->num_options == dnode1->num_options);
    dnode_copy_pass &= (dnode0->options[0] == dnode1->options[0]);
    dnode_copy_pass &= (dnode0->options[1] == dnode1->options[1]);
    fprintf(stderr, "test dnode_copy: %s\n", (dnode_copy_pass ? "pass" : "fail"));

    dnode_destroy(dnode0);
    dnode_destroy(dnode1);
    dedge_destroy(option0);
    dedge_destroy(option1);

    fprintf(stderr, "\n");
    /* end dnode tests */
}

/**
 * Unit test for dedge functions
 */
void test_dedge()
{
    /* dedge tests */
    fprintf(stderr, "*** dedge tests ***\n");

    // dedge_create test
    bool dedge_create_pass = true;
    dedge_t* dedge0 = dedge_create();
    dedge_create_pass &= (strcmp(dedge0->text, "\0") == 0);
    dedge_create_pass &= (dedge0->start == NULL);
    dedge_create_pass &= (dedge0->end == NULL);
    fprintf(stderr, "test dedge_create: %s\n", (dedge_create_pass ? "pass" : "fail"));
    
    // dedge_destroy test
    bool dedge_destroy_pass = true;
    dedge_destroy(dedge0);
    dedge0 = NULL;
    dedge_destroy_pass &= (dedge0 == NULL);
    fprintf(stderr, "test dedge_destroy: %s\n", (dedge_destroy_pass ? "pass" : "fail"));
    
    // dnode_copy test
    bool dedge_copy_pass = true;
    dedge0 = dedge_create();
    strcpy(dedge0->text, "dedge0 text");
    dnode_t* dnode_start = dnode_create();
    dnode_t* dnode_end = dnode_create();
    dedge0->start = dnode_start;
    dedge0->end = dnode_end;
    dedge_t* dedge1 = dedge_copy(dedge0);
    dedge_copy_pass &= (strcmp(dedge0->text, dedge1->text) == 0);
    dedge_copy_pass &= (dedge0->start == dedge1->start);
    dedge_copy_pass &= (dedge0->end == dedge1->end);
    fprintf(stderr, "test dedge_copy: %s\n", (dedge_copy_pass ? "pass" : "fail"));

    dnode_destroy(dnode_start);
    dnode_destroy(dnode_end);
    dedge_destroy(dedge0);
    dedge_destroy(dedge1);

    fprintf(stderr, "\n");
    /* end dedge tests */
}

/**
 * Unit test for dgraph functions
 */
void test_dgraph()
{
    /* dgraph tests */
    fprintf(stderr, "*** dgraph tests ***\n");

    // dgraph_create test
    bool dgraph_create_pass = true;
    dgraph_t* dgraph0 = dgraph_create();
    dgraph_create_pass &= (dgraph0->dnodes == NULL);
    dgraph_create_pass &= (dgraph0->num_dnodes == 0);
    dgraph_create_pass &= (dgraph0->dedges == NULL);
    dgraph_create_pass &= (dgraph0->num_dedges == 0);
    dgraph_create_pass &= (dgraph0->adj_matrix == NULL);
    fprintf(stderr, "test dgraph_create: %s\n", (dgraph_create_pass ? "pass" : "fail"));
    
    // dgraph_destroy test
    bool dgraph_destory_pass = true;
    dgraph_destroy(dgraph0);
    dgraph0 = NULL;
    dgraph_destory_pass &= (dgraph0 == NULL);
    fprintf(stderr, "test dgraph_destory: %s\n", (dgraph_destory_pass ? "pass" : "fail"));

    // dgraph_add_node test
    bool dgraph_add_dnode_pass = true;
    dgraph0 = dgraph_create();
    dnode_t* dnode0 = dnode_create();
    dnode_t* dnode1 = dnode_create();
    dnode_t* dnode2 = dnode_create();
    dnode_t* dnode3 = dnode_create();
    dnode_t* dnode4 = dnode_create();
    strcpy(dnode0->text, "dnode0");
    strcpy(dnode1->text, "dnode1");
    strcpy(dnode2->text, "dnode2");
    strcpy(dnode3->text, "dnode3");
    strcpy(dnode4->text, "dnode4");
    dgraph_add_dnode(dgraph0, dnode0);
    dgraph_add_dnode_pass &= (dgraph0->dnodes[0] == dnode0);
    dgraph_add_dnode_pass &= (dgraph0->num_dnodes == 1);
    dgraph_add_dnode(dgraph0, dnode1);
    dgraph_add_dnode_pass &= (dgraph0->dnodes[1] == dnode1);
    dgraph_add_dnode_pass &= (dgraph0->num_dnodes == 2);
    dgraph_add_dnode(dgraph0, dnode2);
    dgraph_add_dnode_pass &= (dgraph0->dnodes[2] == dnode2);
    dgraph_add_dnode_pass &= (dgraph0->num_dnodes == 3);
    dgraph_add_dnode(dgraph0, dnode3);
    dgraph_add_dnode_pass &= (dgraph0->dnodes[3] == dnode3);
    dgraph_add_dnode_pass &= (dgraph0->num_dnodes == 4);
    dgraph_add_dnode(dgraph0, dnode4);
    dgraph_add_dnode_pass &= (dgraph0->dnodes[4] == dnode4);
    dgraph_add_dnode_pass &= (dgraph0->num_dnodes == 5);
    fprintf(stderr, "test dgraph_add_dnode: %s\n", (dgraph_add_dnode_pass ? "pass" : "fail"));

    // dgraph_remove_dnode test
    bool dgraph_remove_dnode_pass = true;
    dgraph_remove_dnode(dgraph0, dnode3);
    dgraph_remove_dnode_pass &= (dgraph0->dnodes[3] == dnode4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dnodes == 4);
    dgraph_remove_dnode(dgraph0, dnode0);
    dgraph_remove_dnode_pass &= (dgraph0->dnodes[0] == dnode1);
    dgraph_remove_dnode_pass &= (dgraph0->num_dnodes == 3);
    dgraph_remove_dnode(dgraph0, dnode2);
    dgraph_remove_dnode_pass &= (dgraph0->dnodes[1] == dnode4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dnodes == 2);
    dgraph_remove_dnode(dgraph0, dnode1);
    dgraph_remove_dnode_pass &= (dgraph0->dnodes[0] == dnode4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dnodes == 1);
    dgraph_remove_dnode(dgraph0, dnode4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dnodes == 0);
    fprintf(stderr, "test dgraph_remove_dnode: %s\n", (dgraph_remove_dnode_pass ? "pass" : "fail"));

    // dgraph_add_dedge test
    bool dgraph_add_dedge_pass = true;
    dedge_t* dedge0 = dedge_create();
    dedge_t* dedge1 = dedge_create();
    dedge_t* dedge2 = dedge_create();
    dedge_t* dedge3 = dedge_create();
    dedge_t* dedge4 = dedge_create();
    strcpy(dedge0->text, "dedge0");
    strcpy(dedge1->text, "dedge1");
    strcpy(dedge2->text, "dedge2");
    strcpy(dedge3->text, "dedge3");
    strcpy(dedge4->text, "dedge4");
    dgraph_add_dedge(dgraph0, dedge0);
    dgraph_add_dedge_pass &= (dgraph0->dedges[0] == dedge0);
    dgraph_add_dedge_pass &= (dgraph0->num_dedges == 1);
    dgraph_add_dedge(dgraph0, dedge1);
    dgraph_add_dedge_pass &= (dgraph0->dedges[1] == dedge1);
    dgraph_add_dedge_pass &= (dgraph0->num_dedges == 2);
    dgraph_add_dedge(dgraph0, dedge2);
    dgraph_add_dedge_pass &= (dgraph0->dedges[2] == dedge2);
    dgraph_add_dedge_pass &= (dgraph0->num_dedges == 3);
    dgraph_add_dedge(dgraph0, dedge3);
    dgraph_add_dedge_pass &= (dgraph0->dedges[3] == dedge3);
    dgraph_add_dedge_pass &= (dgraph0->num_dedges == 4);
    dgraph_add_dedge(dgraph0, dedge4);
    dgraph_add_dedge_pass &= (dgraph0->dedges[4] == dedge4);
    dgraph_add_dedge_pass &= (dgraph0->num_dedges == 5);
    fprintf(stderr, "test dgraph_add_dedge: %s\n", (dgraph_add_dedge_pass ? "pass" : "fail"));

    // dgraph_remove_dedge test
    bool dgraph_remove_dedge_pass = true;
    dgraph_remove_dedge(dgraph0, dedge3);
    dgraph_remove_dnode_pass &= (dgraph0->dedges[3] == dedge4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dedges == 4);
    dgraph_remove_dedge(dgraph0, dedge0);
    dgraph_remove_dnode_pass &= (dgraph0->dedges[0] == dedge1);
    dgraph_remove_dnode_pass &= (dgraph0->num_dedges == 3);
    dgraph_remove_dedge(dgraph0, dedge2);
    dgraph_remove_dnode_pass &= (dgraph0->dedges[1] == dedge4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dedges == 2);
    dgraph_remove_dedge(dgraph0, dedge1);
    dgraph_remove_dnode_pass &= (dgraph0->dedges[0] == dedge4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dedges == 1);
    dgraph_remove_dedge(dgraph0, dedge4);
    dgraph_remove_dnode_pass &= (dgraph0->num_dedges == 0);
    fprintf(stderr, "test dgraph_remove_dedge: %s\n", (dgraph_remove_dedge_pass ? "pass" : "fail"));

    // dgraph_update_adj_matrix test
    bool dgraph_update_adj_matrix_pass = true;
    dnode_add_option(dnode0, dedge0);
    dnode_add_option(dnode0, dedge1);
    dnode_add_option(dnode2, dedge2);
    dnode_add_option(dnode2, dedge3);
    dnode_add_option(dnode3, dedge4);
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
    dgraph_add_dnode(dgraph0, dnode0);
    dgraph_add_dnode(dgraph0, dnode1);
    dgraph_add_dnode(dgraph0, dnode2);
    dgraph_add_dnode(dgraph0, dnode3);
    dgraph_add_dnode(dgraph0, dnode4);
    dgraph_add_dedge(dgraph0, dedge0);
    dgraph_add_dedge(dgraph0, dedge1);
    dgraph_add_dedge(dgraph0, dedge2);
    dgraph_add_dedge(dgraph0, dedge3);
    dgraph_add_dedge(dgraph0, dedge4);
    dgraph_update_adj_matrix(dgraph0);
    dgraph_update_adj_matrix_pass &= (dgraph0->adj_matrix[0][1] == 0);
    dgraph_update_adj_matrix_pass &= (dgraph0->adj_matrix[0][2] == 1);
    dgraph_update_adj_matrix_pass &= (dgraph0->adj_matrix[2][3] == 2);
    dgraph_update_adj_matrix_pass &= (dgraph0->adj_matrix[2][4] == 3);
    dgraph_update_adj_matrix_pass &= (dgraph0->adj_matrix[3][1] == 4);
    fprintf(stderr, "test dgraph_update_adj_matrix: %s\n", (dgraph_update_adj_matrix_pass ? "pass" : "fail"));

    // dgraph_get_dnode_text test
    bool dgraph_get_dnode_text_pass = true;
    char* text = NULL;
    text = dgraph_get_dnode_text(dgraph0, 0);
    dgraph_get_dnode_text_pass &= (text == dnode0->text);
    text = dgraph_get_dnode_text(dgraph0, 1);
    dgraph_get_dnode_text_pass &= (text == dnode1->text);
    text = dgraph_get_dnode_text(dgraph0, 2);
    dgraph_get_dnode_text_pass &= (text == dnode2->text);
    text = dgraph_get_dnode_text(dgraph0, 3);
    dgraph_get_dnode_text_pass &= (text == dnode3->text);
    text = dgraph_get_dnode_text(dgraph0, 4);
    dgraph_get_dnode_text_pass &= (text == dnode4->text);
    fprintf(stderr, "test dgraph_get_dnode_text: %s\n", (dgraph_get_dnode_text_pass ? "pass" : "fail"));

    // dgraph_get_dedge_text test
    bool dgraph_get_dedge_text_pass = true;
    text = dgraph_get_dedge_text(dgraph0, 0);
    dgraph_get_dedge_text_pass &= (text == dedge0->text);
    text = dgraph_get_dedge_text(dgraph0, 1);
    dgraph_get_dedge_text_pass &= (text == dedge1->text);
    text = dgraph_get_dedge_text(dgraph0, 2);
    dgraph_get_dedge_text_pass &= (text == dedge2->text);
    text = dgraph_get_dedge_text(dgraph0, 3);
    dgraph_get_dedge_text_pass &= (text == dedge3->text);
    text = dgraph_get_dedge_text(dgraph0, 4);
    dgraph_get_dedge_text_pass &= (text == dedge4->text);
    fprintf(stderr, "test dgraph_get_dedge_text: %s\n", (dgraph_get_dedge_text_pass ? "pass" : "fail"));

    // dgraph_get_dnode_options test
    bool dgraph_get_dnode_options_pass = true;
    int* options = NULL;
    options = dgraph_get_dnode_options(dgraph0, 0);
    dgraph_get_dnode_options_pass &= (dgraph0->dedges[options[0]] == dedge0);
    dgraph_get_dnode_options_pass &= (dgraph0->dedges[options[1]] == dedge1);
    dgraph_get_dnode_options_pass &= (options[2] == NO_PATH);
    free(options);
    options = dgraph_get_dnode_options(dgraph0, 1);
    dgraph_get_dnode_options_pass &= (options[0] == NO_PATH);
    free(options);
    options = dgraph_get_dnode_options(dgraph0, 2);
    dgraph_get_dnode_options_pass &= (dgraph0->dedges[options[0]] == dedge2);
    dgraph_get_dnode_options_pass &= (dgraph0->dedges[options[1]] == dedge3);
    dgraph_get_dnode_options_pass &= (options[2] == NO_PATH);
    free(options);
    options = dgraph_get_dnode_options(dgraph0, 3);
    dgraph_get_dnode_options_pass &= (dgraph0->dedges[options[0]] == dedge4);
    dgraph_get_dnode_options_pass &= (options[1] == NO_PATH);
    free(options);
    options = dgraph_get_dnode_options(dgraph0, 4);
    dgraph_get_dnode_options_pass &= (options[0] == NO_PATH);
    free(options);
    fprintf(stderr, "test dgraph_get_dnode_options: %s\n", (dgraph_get_dnode_options_pass ? "pass" : "fail"));

    // dgraph_get_dedge_end_dnode test
    bool dgraph_get_dedge_end_dnode_pass = true;
    int index_dnode_end = NO_PATH;
    index_dnode_end = dgraph_get_dedge_end_dnode(dgraph0, 0);
    dgraph_get_dedge_end_dnode_pass &= (dgraph0->dnodes[index_dnode_end] == dnode1);
    index_dnode_end = dgraph_get_dedge_end_dnode(dgraph0, 1);
    dgraph_get_dedge_end_dnode_pass &= (dgraph0->dnodes[index_dnode_end] == dnode2);
    index_dnode_end = dgraph_get_dedge_end_dnode(dgraph0, 2);
    dgraph_get_dedge_end_dnode_pass &= (dgraph0->dnodes[index_dnode_end] == dnode3);
    index_dnode_end = dgraph_get_dedge_end_dnode(dgraph0, 3);
    dgraph_get_dedge_end_dnode_pass &= (dgraph0->dnodes[index_dnode_end] == dnode4);
    index_dnode_end = dgraph_get_dedge_end_dnode(dgraph0, 4);
    dgraph_get_dedge_end_dnode_pass &= (dgraph0->dnodes[index_dnode_end] == dnode1);
    fprintf(stderr, "test dgraph_get_dedge_end_dnode: %s\n", (dgraph_get_dedge_end_dnode_pass ? "pass" : "fail"));

    dgraph_destroy(dgraph0);

    fprintf(stderr, "\n");
    /* end dgraph tests */
}

/**
 * Unit test for dtree functions
 */
void test_dtree()
{
    /* dtree tests */
    fprintf(stderr, "*** dtree tests ***\n");

    // dtree_create test
    bool dtree_create_pass = true;
    dtree_t* dtree0 = dtree_create();
    dtree_create_pass &= (dtree0->floating_dnodes == NULL);
    dtree_create_pass &= (dtree0->num_floating_dnodes == 0);
    dtree_create_pass &= (dtree0->floating_dedges == NULL);
    dtree_create_pass &= (dtree0->num_floating_dedges == 0);
    dtree_create_pass &= (dtree0->dgraph->dnodes == NULL);
    dtree_create_pass &= (dtree0->dgraph->num_dnodes == 0);
    dtree_create_pass &= (dtree0->dgraph->dedges == NULL);
    dtree_create_pass &= (dtree0->dgraph->num_dedges == 0);
    dtree_create_pass &= (dtree0->dgraph->adj_matrix == NULL);
    fprintf(stderr, "test dtree_create: %s\n", dtree_create_pass ? "pass" : "fail");

    // dtree_destroy test
    bool dtree_destroy_pass = true;
    dtree_destroy(dtree0);
    dtree0 = NULL;
    dtree_destroy_pass &= (dtree0 == NULL);
    fprintf(stderr, "test dtree_destroy: %s\n", dtree_destroy_pass ? "pass" : "fail");

    // dtree_add_dnode test
    bool dtree_add_dnode_pass = true;
    dtree0 = dtree_create();
    dtree_add_dnode(dtree0, "dnode0");
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[0]->text, "dnode0") == 0);
    dtree_add_dnode_pass &= (dtree0->num_floating_dnodes == 1);
    dtree_add_dnode(dtree0, "dnode1");
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[0]->text, "dnode0") == 0);
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[1]->text, "dnode1") == 0);
    dtree_add_dnode_pass &= (dtree0->num_floating_dnodes == 2);
    dtree_add_dnode(dtree0, "dnode2");
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[0]->text, "dnode0") == 0);
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[1]->text, "dnode1") == 0);
    dtree_add_dnode_pass &= (strcmp(dtree0->floating_dnodes[2]->text, "dnode2") == 0);
    dtree_add_dnode_pass &= (dtree0->num_floating_dnodes == 3);
    fprintf(stderr, "test dtree_add_dnode: %s\n", dtree_add_dnode_pass ? "pass" : "fail");

    // dtree_add_dedge test
    bool dtree_add_dedge_pass = true;
    dtree_add_dedge(dtree0, "dedge0");
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[0]->text, "dedge0") == 0);
    dtree_add_dedge_pass &= (dtree0->num_floating_dedges == 1);
    dtree_add_dedge(dtree0, "dedge1");
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[0]->text, "dedge0") == 0);
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[1]->text, "dedge1") == 0);
    dtree_add_dedge_pass &= (dtree0->num_floating_dedges == 2);
    dtree_add_dedge(dtree0, "dedge2");
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[0]->text, "dedge0") == 0);
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[1]->text, "dedge1") == 0);
    dtree_add_dedge_pass &= (strcmp(dtree0->floating_dedges[2]->text, "dedge2") == 0);
    dtree_add_dedge_pass &= (dtree0->num_floating_dedges == 3);
    fprintf(stderr, "test dtree_add_dedge: %s\n", dtree_add_dedge_pass ? "pass" : "fail");

    // dtree_remove_dnode test
    bool dtree_remove_dnode_pass = true;
    dtree_remove_dnode(dtree0, 1);
    dtree_remove_dnode_pass &= (strcmp(dtree0->floating_dnodes[0]->text, "dnode0") == 0);
    dtree_remove_dnode_pass &= (strcmp(dtree0->floating_dnodes[1]->text, "dnode2") == 0);
    dtree_remove_dnode_pass &= (dtree0->num_floating_dnodes == 2);
    dtree_remove_dnode(dtree0, 0);
    dtree_remove_dnode_pass &= (strcmp(dtree0->floating_dnodes[0]->text, "dnode2") == 0);
    dtree_remove_dnode_pass &= (dtree0->num_floating_dnodes == 1);
    dtree_remove_dnode(dtree0, 0);
    dtree_remove_dnode_pass &= (dtree0->num_floating_dnodes == 0);
    fprintf(stderr, "test dtree_remove_dnode: %s\n", dtree_remove_dnode_pass ? "pass" : "fail");

    // dtree_remove_dedge test
    bool dtree_remove_dedge_pass = true;
    dtree_remove_dedge(dtree0, 1);
    dtree_remove_dedge_pass &= (strcmp(dtree0->floating_dedges[0]->text, "dedge0") == 0);
    dtree_remove_dedge_pass &= (strcmp(dtree0->floating_dedges[1]->text, "dedge2") == 0);
    dtree_remove_dedge_pass &= (dtree0->num_floating_dedges == 2);
    dtree_remove_dedge(dtree0, 0);
    dtree_remove_dedge_pass &= (strcmp(dtree0->floating_dedges[0]->text, "dedge2") == 0);
    dtree_remove_dedge_pass &= (dtree0->num_floating_dedges == 1);
    dtree_remove_dedge(dtree0, 0);
    dtree_remove_dedge_pass &= (dtree0->num_floating_dedges == 0);
    fprintf(stderr, "test dtree_remove_dedge: %s\n", dtree_remove_dedge_pass ? "pass" : "fail");

    // dtree_set_root_dnode test
    bool dtree_set_root_dnode_pass = true;
    dtree_add_dnode(dtree0, "dnode0");
    dtree_add_dnode(dtree0, "dnode1");
    dtree_set_root_dnode(dtree0, 0);
    dtree_set_root_dnode_pass &= (strcmp(dtree0->dgraph->dnodes[0]->text, "dnode0") == 0);
    dtree_set_root_dnode_pass &= (dtree0->num_floating_dnodes == 1);
    dtree_set_root_dnode(dtree0, 0);
    dtree_set_root_dnode_pass &= (strcmp(dtree0->dgraph->dnodes[0]->text, "dnode1") == 0);
    dtree_set_root_dnode_pass &= (dtree0->num_floating_dnodes == 0);
    fprintf(stderr, "test dtree_set_root_dnode: %s\n", dtree_set_root_dnode_pass ? "pass" : "fail");

    // dtree_add_dnode_option test
    bool dtree_add_dnode_option_pass = true;
    dtree_add_dedge(dtree0, "dedge0");
    dtree_add_dedge(dtree0, "dedge1");
    dtree_add_dnode_option(dtree0, 0, 0);
    dtree_add_dnode_option_pass &= (strcmp(dtree0->dgraph->dnodes[0]->options[0]->text, "dedge0") == 0);
    dtree_set_root_dnode_pass &= (dtree0->num_floating_dedges == 1);
    dtree_set_root_dnode_pass &= (dtree0->dgraph->num_dedges == 1);
    dtree_add_dnode_option(dtree0, 0, 0);
    dtree_add_dnode_option_pass &= (strcmp(dtree0->dgraph->dnodes[0]->options[0]->text, "dedge0") == 0);
    dtree_add_dnode_option_pass &= (strcmp(dtree0->dgraph->dnodes[0]->options[1]->text, "dedge1") == 0);
    dtree_set_root_dnode_pass &= (dtree0->num_floating_dedges == 0);
    dtree_set_root_dnode_pass &= (dtree0->dgraph->num_dedges == 2);
    fprintf(stderr, "test dtree_add_dnode_option: %s\n", dtree_add_dnode_option_pass ? "pass" : "fail");

    // dtree_add_dedge_end test
    bool dtree_add_dedge_end_pass = true;
    dtree_add_dnode(dtree0, "dnode2");
    dtree_add_dnode(dtree0, "dnode3");
    dtree_add_dedge_end(dtree0, 0, 0);
    dtree_add_dedge_end_pass &= (strcmp(dtree0->dgraph->dedges[0]->end->text, "dnode2") == 0);
    dtree_add_dedge_end_pass &= (dtree0->num_floating_dnodes == 1);
    dtree_add_dedge_end_pass &= (dtree0->dgraph->num_dnodes == 2);
    dtree_add_dedge_end(dtree0, 1, 0);
    dtree_add_dedge_end_pass &= (strcmp(dtree0->dgraph->dedges[0]->end->text, "dnode2") == 0);
    dtree_add_dedge_end_pass &= (strcmp(dtree0->dgraph->dedges[1]->end->text, "dnode3") == 0);
    dtree_add_dedge_end_pass &= (dtree0->num_floating_dnodes == 0);
    dtree_add_dedge_end_pass &= (dtree0->dgraph->num_dnodes == 3);
    fprintf(stderr, "test dtree_add_dedge_end: %s\n", dtree_add_dedge_end_pass ? "pass" : "fail");

    // dtree_get_floating_dnodes test
    bool dtree_get_floating_dnodes_pass = true;
    dtree_add_dnode(dtree0, "dnode4");
    dtree_add_dnode(dtree0, "dnode5");
    dtree_add_dnode(dtree0, "dnode6");
    tlist_t* floating_dnodes_text = dtree_get_floating_dnodes(dtree0);
    dtree_get_floating_dnodes_pass &= (strcmp(floating_dnodes_text->text[0], "dnode4") == 0);
    dtree_get_floating_dnodes_pass &= (strcmp(floating_dnodes_text->text[1], "dnode5") == 0);
    dtree_get_floating_dnodes_pass &= (strcmp(floating_dnodes_text->text[2], "dnode6") == 0);
    dtree_get_floating_dnodes_pass &= (floating_dnodes_text->length == 3);
    dtree_char_array_destroy(floating_dnodes_text);
    fprintf(stderr, "test dtree_get_floating_dnodes: %s\n", dtree_get_floating_dnodes_pass ? "pass" : "fail");

    // dtree_get_floating_dedges test
    bool dtree_get_floating_dedges_pass = true;
    dtree_add_dedge(dtree0, "dedge4");
    dtree_add_dedge(dtree0, "dedge5");
    dtree_add_dedge(dtree0, "dedge6");
    tlist_t* floating_dedges_text = dtree_get_floating_dedges(dtree0);
    dtree_get_floating_dedges_pass &= (strcmp(floating_dedges_text->text[0], "dedge4") == 0);
    dtree_get_floating_dedges_pass &= (strcmp(floating_dedges_text->text[1], "dedge5") == 0);
    dtree_get_floating_dedges_pass &= (strcmp(floating_dedges_text->text[2], "dedge6") == 0);
    dtree_get_floating_dedges_pass &= (floating_dedges_text->length == 3);
    dtree_char_array_destroy(floating_dedges_text);
    fprintf(stderr, "test dtree_get_floating_dedges: %s\n", dtree_get_floating_dedges_pass ? "pass" : "fail");

    // dtree_get_dgraph_dnodes test
    bool dtree_get_dgraph_dnodes_pass = true;
    tlist_t* dgraph_dnodes_text = dtree_get_dgraph_dnodes(dtree0);
    dtree_get_dgraph_dnodes_pass &= (strcmp(dgraph_dnodes_text->text[0], "dnode1") == 0);
    dtree_get_dgraph_dnodes_pass &= (strcmp(dgraph_dnodes_text->text[1], "dnode2") == 0);
    dtree_get_dgraph_dnodes_pass &= (strcmp(dgraph_dnodes_text->text[2], "dnode3") == 0);
    dtree_get_dgraph_dnodes_pass &= (dgraph_dnodes_text->length == 3);
    dtree_char_array_destroy(dgraph_dnodes_text);
    fprintf(stderr, "test dtree_get_dgraph_dnodes: %s\n", dtree_get_dgraph_dnodes_pass ? "pass" : "fail");

    // dtree_get_dgraph_dedges test
    bool dtree_get_dgraph_dedges_pass = true;
    tlist_t* dgraph_dedges_text = dtree_get_dgraph_dedges(dtree0);
    dtree_get_dgraph_dedges_pass &= (strcmp(dgraph_dedges_text->text[0], "dedge0") == 0);
    dtree_get_dgraph_dedges_pass &= (strcmp(dgraph_dedges_text->text[1], "dedge1") == 0);
    dtree_get_dgraph_dedges_pass &= (dgraph_dedges_text->length == 2);
    dtree_char_array_destroy(dgraph_dedges_text);
    fprintf(stderr, "test dtree_get_dgraph_dedges: %s\n", dtree_get_dgraph_dedges_pass ? "pass" : "fail");

    fprintf(stderr, "\n");
    /* end dtree tests */
}