#include "binary_search_tree.h"

// Integer Functions
int int_cmp(void *, void *);
void int_print(void *);
void int_delete(void *);
void int_print_double(void *);

int main()
{
    printf("Creating integer tree.\n");
    bst_t *tree = CREATE_BST(int);

    for( int i = 0; i < 15; ++i )
    {
        int *number = malloc(sizeof(int));
        *number = (17 * (i + 1) + 3) % 31;
        printf("Inserting %d\n", *number);
        insert_node(tree, number);
    }

    printf("Pre-order traversal: ");
    pre_order_print(tree);
    printf("In-order traversal: ");
    in_order_print(tree);
    printf("Post-order traversal: ");
    post_order_print(tree);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);
    printf("Empty? %s", is_empty(tree) ? "true" : "false");

    int seven = 7;
    printf("\nContains 7? %s\n", contains(tree, &seven) ? "true" : "false");

    int eleven = 11;
    printf("Contains 11? %s\n", contains(tree, &eleven) ? "true" : "false");

    printf("\nPrinting 2 * data in order:\n");
    in_order_traverse(tree, int_print_double);

    printf("\nTesting removal of leaf (18).\n");
    int eighteen = 18;
    free(remove_node(tree, &eighteen));
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);
    printf("Empty? %s\n", is_empty(tree) ? "true" : "false");

    printf("\nTesting removal of node with one child (1).\n");
    int one = 1;
    free(remove_node(tree, &one));
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);
    printf("Empty? %s", is_empty(tree) ? "true" : "false");

    printf("\nTesting removal of node with two children (20).\n");
    int twenty = 20;
    free(remove_node(tree, &twenty));
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);
    printf("Empty? %s\n", is_empty(tree) ? "true" : "false");

    printf("\nClearing tree. The traversals should be blank below this line.");
    clear(tree);

    printf("\nPre-order traversal: ");
    pre_order_print(tree);
    printf("In-order traversal: ");
    in_order_print(tree);
    printf("Post-order traversal: ");
    post_order_print(tree);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);
    printf("Empty? %s\n", is_empty(tree) ? "true" : "false");

    delete_bst(&tree);
}

// VALGRIND:
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose \
--log-file=bin/results.txt ./bin/bst
*/

int int_cmp(void *data1, void *data2)
{
    return *( int * )data1 - *( int * )data2;
}

void int_print(void *data)
{
    printf("%d ", *( int * )data);
}

void int_delete(void *data)
{
    free(data);
}

void int_print_double(void *data)
{
    printf("2 * %d = %d\n", *( int * )data, *( int * )data * 2);
}
