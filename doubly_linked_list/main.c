#include <stdio.h>
#include <string.h>
#include "doubly_linked_list.h"

// Integer List Functions
int int_cmp(void *, void *);
void int_print(void *, void *);
void int_delete(void *);

// String List Functions
int string_cmp(void *, void *);
void string_print(void *, void *);
void string_delete([[maybe_unused]] void *);

char *make_str(char const *);

int main(int const argc, char **argv)
{
    linked_list_t *list = CREATE_LINKED_LIST(int);

    for( int i = 0; i < 15; ++i )
    {
        int *number = malloc(sizeof(int));
        *number = (17 * (i + 1) + 3) % 12;
        printf("Inserting %d\n", *number);
        insert(list, number);
    }

    int seven = 7;
    int *ref_7 = &seven;

    int six = 6;
    int *ref_6 = &six;

    int hundred = 100;
    int *ref_100 = &hundred;

    printf("\nOriginal list:\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_at_head(list));

    printf("remove_at_head():\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_at_tail(list));

    printf("remove_at_tail():\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_by_value(list, ref_7));

    printf("remove_by_value(7):\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_at_index(list, 4));

    printf("remove_at_index(4):\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_at_index(list, 100);

    printf("remove_at_index(100):\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_by_value(list, ref_6));

    printf("remove_by_value(6):\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    free(remove_by_value(list, ref_6));

    printf("remove_by_value(6) - Again:\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_by_value(list, ref_100);

    printf("remove_by_value(100):\n");
    print_list(list, stdout);
    printf("Head: %d\n", *( int * )access_at_head(list));
    printf("Tail: %d\n", *( int * )access_at_tail(list));
    printf("Index 4: %d\n", *( int * )access_at_index(list, 4));
    printf("Contains 7: %s\n", contains(list, ref_7) ? "true" : "false");
    printf("Contains 6: %s\n", contains(list, ref_6) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    clear_list(list);

    printf("There should be no integer list output after this line.\n\n\n");
    print_list(list, stdout);

    delete_linked_list(&list);
    print_list(list, stdout);

    list = CREATE_LINKED_LIST(string);

    // Test argv = "this should be a test phrase with at least eleven words"
    for( int i = 1; i < argc; ++i )
    {
        printf("Inserting %s\n", argv[i]);
        insert(list, argv[i]);
    }
    char *word = make_str("should");

    printf("\nOriginal list:\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_at_head(list);

    printf("remove_at_head():\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_at_tail(list);

    printf("remove_at_tail():\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_by_value(list, word);

    printf("remove_by_value(\"should\"):\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_at_index(list, 4);

    printf("remove_at_index(4):\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    remove_at_index(list, 100);

    printf("remove_at_index(100):\n");
    print_list(list, stdout);
    printf("Head: %s\n", ( char * )access_at_head(list));
    printf("Tail: %s\n", ( char * )access_at_tail(list));
    printf("Index 4: %s\n", ( char * )access_at_index(list, 4));
    printf("Contains \"should\": %s\n",
           contains(list, word) ? "true" : "false");
    printf("Size: %zu\n\n", get_size(list));

    clear_list(list);

    printf("There should be no string list output after this line.\n\n\n");
    print_list(list, stdout);

    delete_linked_list(&list);
    free(word);

    print_list(list, stdout);
}

int int_cmp(void *data1, void *data2)
{
    return *( int * )data1 - *( int * )data2;
}

void int_print(void *data, void *fp)
{
    fprintf(( FILE * )fp, "%d", *( int * )data);
}

void int_delete(void *data)
{
    free(data);
}

int string_cmp(void *data1, void *data2)
{
    return strcmp(( char const * )data1, ( char const * )data2);
}

void string_print(void *str, void *fp)
{
    fprintf(( FILE * )fp, "%s", ( char * )str);
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
