#include "binary_search_tree.h"

bst_t *create_bst(int (*comparator)(void *, void *),
                  void (*printer)(void *),
                  void (*deleter)(void *))
{
    bst_t *tree = malloc(sizeof(bst_t));

    if( !tree )
    {
        return nullptr;
    }

    tree->root = nullptr;
    tree->size = 0;
    tree->comparator = comparator;
    tree->printer = printer;
    tree->deleter = deleter;

    return tree;
}

node_t *create_node(void *data, node_t *parent)
{
    node_t *node = malloc(sizeof(node_t));

    if( !node )
    {
        return nullptr;
    }

    node->data = data;
    node->left = node->right = nullptr;
    node->parent = parent;

    return node;
}

node_t *find_previous_node(bst_t *tree, void *data)
{
    if( !tree )
    {
        return nullptr;
    }

    node_t *previous_node = nullptr;
    node_t *current_node = tree->root;

    int comparison;

    while( current_node )
    {
        previous_node = current_node;

        comparison = tree->comparator(data, current_node->data);

        if( comparison < 0 )
        {
            current_node = current_node->left;
        }
        else if( comparison > 0 )
        {
            current_node = current_node->right;
        }
        else
        {
            return nullptr;
        }
    }

    return previous_node;
}

node_t *find_node(bst_t *tree, void *data)
{
    if( !tree )
    {
        return nullptr;
    }

    node_t *current_node = tree->root;

    while( current_node )
    {
        int comparison = tree->comparator(data, current_node->data);

        if( comparison < 0 )
        {
            current_node = current_node->left;
        }
        else if( comparison > 0 )
        {
            current_node = current_node->right;
        }
        else
        {
            return current_node;
        }
    }

    return nullptr;
}

void insert_node(bst_t *tree, void *data)
{
    if( is_empty(tree) )
    {
        tree->root = create_node(data, nullptr);
        ++tree->size;
        return;
    }

    node_t *previous_node = find_previous_node(tree, data);

    node_t *node = create_node(data, previous_node);

    if( tree->comparator(data, previous_node->data) < 0 )
    {
        previous_node->left = node;
    }
    else
    {
        previous_node->right = node;
    }

    ++tree->size;
}

bool contains(bst_t *tree, void *data)
{
    return find_node(tree, data);
}

void *remove_node(bst_t *tree, void *data)
{
    if( is_empty(tree) )
    {
        return nullptr;
    }

    node_t *current_node = find_node(tree, data);

    if( !current_node )
    {
        return nullptr;
    }

    --tree->size;

    if( current_node->left && current_node->right )
    {
        return remove_two_child(tree, current_node);
    }
    else if( current_node->left || current_node->right )
    {
        return remove_one_child(tree, current_node);
    }

    return remove_leaf(tree, current_node);
}

void *remove_leaf(bst_t *tree, node_t *node)
{
    if( is_empty(tree) || !node )
    {
        return nullptr;
    }

    if( node == tree->root )
    {
        tree->root = nullptr;
    }
    else if( node->parent->left == node )
    {
        node->parent->left = nullptr;
    }
    else
    {
        node->parent->right = nullptr;
    }

    void *data = node->data;
    free(node);
    return data;
}

void *remove_one_child(bst_t *tree, node_t *node)
{
    if( is_empty(tree) || !node || (node->left && node->right) )
    {
        return nullptr;
    }

    node_t **relink_node;
    if( node == tree->root )
    {
        relink_node = &tree->root;
    }
    else
    {
        relink_node = (node == node->parent->left) ? &node->parent->left
                                                   : &node->parent->right;
    }

    *relink_node = (node->left) ? node->left : node->right;

    void *data = node->data;
    free(node);
    return data;
}

void *remove_two_child(bst_t *tree, node_t *node)
{
    if( is_empty(tree) || !node )
    {
        return nullptr;
    }

    node_t *predecessor = node->left;

    while( predecessor->right )
    {
        predecessor = predecessor->right;
    }

    void *data = node->data;
    node->data = predecessor->data;

    if( !predecessor->left && !predecessor->right )
    {
        remove_leaf(tree, predecessor);
    }
    else
    {
        remove_one_child(tree, predecessor);
    }

    return data;
}

void clear(bst_t *tree)
{
    if( !tree )
    {
        return;
    }

    remove_recursive(tree->root, tree->deleter);
    tree->root = nullptr;
    tree->size = 0;
}

void remove_recursive(node_t *node, void (*deleter)(void *))
{
    if( !node )
    {
        return;
    }

    remove_recursive(node->left, deleter);
    remove_recursive(node->right, deleter);

    deleter(node->data);
    free(node);
}

void pre_order_print(bst_t *tree)
{
    if( !tree )
    {
        return;
    }

    pre_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void pre_order_traverse(bst_t *tree, void (*func)(void *))
{
    if( !tree )
    {
        return;
    }

    pre_order_recurse(tree->root, func);
}

void pre_order_recurse(node_t *node, void (*func)(void *))
{
    if( !node )
    {
        return;
    }

    func(node->data);
    pre_order_recurse(node->left, func);
    pre_order_recurse(node->right, func);
}

void in_order_print(bst_t *tree)
{
    if( !tree )
    {
        return;
    }

    in_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void in_order_traverse(bst_t *tree, void (*func)(void *))
{
    if( !tree )
    {
        return;
    }

    in_order_recurse(tree->root, func);
}

void in_order_recurse(node_t *node, void (*func)(void *))
{
    if( !node )
    {
        return;
    }

    in_order_recurse(node->left, func);
    func(node->data);
    in_order_recurse(node->right, func);
}

void post_order_print(bst_t *tree)
{
    if( !tree )
    {
        return;
    }

    post_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void post_order_traverse(bst_t *tree, void (*func)(void *))
{
    if( !tree )
    {
        return;
    }

    post_order_recurse(tree->root, func);
}

void post_order_recurse(node_t *node, void (*func)(void *))
{
    if( !node )
    {
        return;
    }

    post_order_recurse(node->left, func);
    post_order_recurse(node->right, func);
    func(node->data);
}

void level_order_print(bst_t *tree)
{
    if( !tree )
    {
        return;
    }

    level_order_traverse(tree, tree->printer);
    printf("\n\n");
}

void level_order_traverse(bst_t *tree, void (*func)(void *))
{
    if( !tree || !tree->root )
    {
        return;
    }

    deque_t *queue = CREATE_DEQUE(node_t *);

    push_back(queue, &tree->root);

    while( queue->size > 0 )
    {
        node_t *node;
        pop_front(queue, &node);

        if( !node )
        {
            continue;
        }

        func(node->data);

        if( node->left )
        {
            push_back(queue, &(node->left));
        }

        if( node->right )
        {
            push_back(queue, &node->right);
        }
    }

    delete_deque(&queue);
}

bool is_empty(bst_t *tree)
{
    return !tree || tree->size == 0;
}

void delete_bst(bst_t **tree)
{
    if( !tree || !*tree )
    {
        return;
    }

    clear(*tree);
    free(*tree);
    *tree = nullptr;
}
