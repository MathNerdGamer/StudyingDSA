#include "doubly_linked_list.h"

// Node creation and deletion.
node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if( !node )
    {
        return NULL;
    }

    node->data = data;
    node->next = node->prev = NULL;

    return node;
}

// List creation and deletion.
linked_list_t *create_linked_list(int (*compare)(void *, void *),
                                  void (*print)(void *, void *),
                                  void (*delete)(void *))
{
    linked_list_t *list = malloc(sizeof(linked_list_t));

    if( !list )
    {
        return NULL;
    }

    list->comparator = compare;
    list->printer = print;
    list->deleter = delete;
    list->size = 0;
    list->head = list->tail = NULL;

    return list;
}

void delete_linked_list(linked_list_t **list)
{
    if( !list || !*list )
    {
        return;
    }

    clear_list(*list);
    free(*list);
    *list = NULL;
}

// Insertion function
void insert(linked_list_t *list, void *data)
{
    if( !list || !data )
    {
        return;
    }

    node_t *new_node = create_node(data);

    if( !new_node )
    {
        return;
    }

    ++list->size;

    if( !list->head )
    {
        list->head = list->tail = new_node;
        return;
    }

    node_t *node = list->head;
    while( node && list->comparator(node->data, data) < 0 )
    {
        node = node->next;
    }

    if( !node )
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    else
    {
        if( node == list->head )
        {
            list->head = new_node;
        }
        else
        {
            node->prev->next = new_node;
        }

        new_node->next = node;
        new_node->prev = node->prev;
        node->prev = new_node;
    }
}

// Access functions
void *access_at_head(linked_list_t const *const list)
{
    return (list->head) ? list->head->data : NULL;
}

void *access_at_tail(linked_list_t const *const list)
{
    return (list->tail) ? list->tail->data : NULL;
}

void *access_at_index(linked_list_t const *const list, size_t const index)
{
    if( !list || index >= list->size )
    {
        return NULL;
    }

    size_t back_index = list->size - index;
    node_t *node = (back_index > index) ? list->head : list->tail;

    if( back_index > index )
    {
        for( size_t i = 0; i < index; ++i )
        {
            node = node->next;
        }
    }
    else
    {
        for( size_t i = 0; i < back_index; ++i )
        {
            node = node->prev;
        }
    }

    return node->data;
}

void *access_by_value(linked_list_t const *const list, void *data)
{
    if( !list || !data )
    {
        return NULL;
    }

    node_t *node = list->head;
    int cmp_result;

    while( node && (cmp_result = list->comparator(node->data, data)) < 0 )
    {
        node = node->next;
    }

    if( !node || cmp_result != 0 )
    {
        return NULL;
    }

    return node->data;
}

// Removal functions
void *remove_at_head(linked_list_t *list)
{
    if( !list || !list->head )
    {
        return NULL;
    }

    node_t *node = list->head;
    void *data = node->data;

    if( list->head == list->tail )
    {
        list->head = list->tail = NULL;
    }
    else
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(node);
    --list->size;

    return data;
}

void *remove_at_tail(linked_list_t *list)
{
    if( !list || !list->tail )
    {
        return NULL;
    }

    node_t *node = list->tail;
    void *data = node->data;

    if( list->head == list->tail )
    {
        list->head = list->tail = NULL;
    }
    else
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(node);
    --list->size;

    return data;
}

void *remove_at_index(linked_list_t *list, size_t const index)
{
    if( !list || index >= list->size )
    {
        return NULL;
    }

    if( index == 0 )
    {
        return remove_at_head(list);
    }
    else if( index == list->size - 1 )
    {
        return remove_at_tail(list);
    }

    size_t back_index = list->size - index;
    node_t *node = (back_index > index) ? list->head : list->tail;

    if( back_index > index )
    {
        for( size_t i = 0; i < index; ++i )
        {
            node = node->next;
        }
    }
    else
    {
        for( size_t i = 0; i < back_index; ++i )
        {
            node = node->prev;
        }
    }

    void *data = node->data;

    node->next->prev = node->prev;
    node->prev->next = node->next;

    free(node);
    --list->size;

    return data;
}

void *remove_by_value(linked_list_t *list, void *data)
{
    if( !list || !data )
    {
        return NULL;
    }

    node_t *node = list->head;
    int cmp_result;

    while( node && (cmp_result = list->comparator(node->data, data)) < 0 )
    {
        node = node->next;
    }

    if( !node || cmp_result != 0 )
    {
        return NULL;
    }

    if( node == list->head )
    {
        return remove_at_head(list);
    }
    else if( node == list->tail )
    {
        return remove_at_tail(list);
    }

    void *result = node->data;
    node->prev->next = node->next;
    node->next->prev = node->prev;

    free(node);
    --list->size;

    return result;
}

void clear_list(linked_list_t *list)
{
    if( !list )
    {
        return;
    }

    node_t *node = list->head;

    while( node )
    {
        node_t *next = node->next;

        list->deleter(node->data);
        free(node);
        node = next;
    }

    list->head = list->tail = NULL;
    list->size = 0;
}

// Utility functions
void print_list(linked_list_t const *const list, FILE *fp)
{
    if( !list || !list->head || !fp )
    {
        return;
    }

    node_t *node = list->head;

    while( true )
    {
        list->printer(node->data, fp);

        if( node->next )
        {
            fprintf(fp, " <-> ");
        }
        else
        {
            fprintf(fp, "\n");
            break;
        }

        node = node->next;
    }
}

bool contains(linked_list_t const *const list, void *data)
{
    return access_by_value(list, data);
}

size_t get_size(linked_list_t const *const list)
{
    return (list) ? list->size : 0;
}