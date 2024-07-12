#include "binary_search_tree.h"

// Integer Functions
int int_cmp(void *, void *);
void int_print(void *);
void int_delete(void *);
void int_print_double(void *);

// String Functions
int string_cmp(void *, void *);
void string_print(void *);
void string_delete([[maybe_unused]] void *);

char *make_str(char const *);

int main(int argc, char **argv)
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

    int seven = 7;
    printf("\nContains 7? %s\n", contains(tree, &seven) ? "true" : "false");

    int eleven = 11;
    printf("Contains 11? %s\n", contains(tree, &eleven) ? "true" : "false");

    printf("\nPrinting 2 * data in order:\n");
    in_order_traverse(tree, int_print_double);

    printf("\nTesting removal of leaf (18).\n");
    int eighteen = 18;
    remove_node(tree, &eighteen);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("\nTesting removal of node with one child (1).\n");
    int one = 1;
    remove_node(tree, &one);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("\nTesting removal of node with two children (20).\n");
    int twenty = 20;
    remove_node(tree, &twenty);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("\nClearing tree. There should be no integers below this line.");
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

    delete_bst(&tree);

    printf("\n\nCreating string tree.\n");
    tree = CREATE_BST(string);

    // Test argv =
    // nonsense ahead: no zebras where we are going abra kadabra alakazam what
    for( int i = 1; i < argc; ++i )
    {
        printf("Inserting %s\n", argv[i]);
        insert_node(tree, argv[i]);
    }

    printf("\nPre-order traversal: ");
    pre_order_print(tree);
    printf("In-order traversal: ");
    in_order_print(tree);
    printf("Post-order traversal: ");
    post_order_print(tree);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    char *word = make_str("to");
    printf("\nContains \"to\"? %s\n", contains(tree, word) ? "true" : "false");
    free(word);

    word = make_str("where");
    printf("Contains \"where\"? %s\n", contains(tree, word) ? "true" : "false");
    free(word);

    printf("\nTesting removal of leaf (\"kadabra\").\n");
    word = make_str("kadabra");
    remove_node(tree, word);
    free(word);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("\nTesting removal of node with one child (\"no\").\n");
    word = make_str("no");
    remove_node(tree, word);
    free(word);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("\nTesting removal of node with two children (\"nonsense\").\n");
    word = make_str("nonsense");
    remove_node(tree, word);
    free(word);
    printf("Level-order traversal: ");
    level_order_print(tree);
    printf("Size: %zu\n", tree->size);

    printf("Clearing tree. There should be no strings below this line.");
    clear(tree);

    pre_order_print(tree);
    in_order_print(tree);
    post_order_print(tree);
    level_order_print(tree);

    delete_bst(&tree);
}

// VALGRIND:
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose \
--log-file=results.txt ./bst nonsense ahead: no zebras where we are going abra \
kadabra alakazam what
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

int string_cmp(void *data1, void *data2)
{
    return strcmp(( char const * )data1, ( char const * )data2);
}

void string_print(void *str)
{
    printf("%s ", ( char * )str);
}

void string_delete([[maybe_unused]] void *str)
{
    // Do nothing, since we're working with argv.
}

char *make_str(char const *str)
{
    char *ret = malloc(strlen(str) + 1);

    strcpy(ret, str);

    return ret;
}