#include "avl_tree.h"

avl_t *create_avl(int (*comparator)(void *, void *),
                  void (*printer)(void *),
                  void (*deleter)(void *))
{
    avl_t *tree = malloc(sizeof(avl_t));

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

node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if( !node )
    {
        return nullptr;
    }

    node->data = data;
    node->parent = node->left = node->right = nullptr;
    node->height = 0;

    return node;
}

node_t *find_node(avl_t *tree, void *data)
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

int node_height(node_t *node)
{
    return (node) ? node->height : -1;
}

void update_height(node_t *node)
{
    if( !node )
    {
        return;
    }

    node->height = 1 + MAX(node_height(node->left), node_height(node->right));
}

int balance_factor(node_t *node)
{
    if( !node )
    {
        return 0;
    }

    return node_height(node->left) - node_height(node->right);
}

node_t *left_rotate(node_t *node)
{
    if( !node->right )
    {
        return nullptr;
    }

    node_t *right = node->right;
    node->right = right->left;

    right->left = node;
    right->parent = node->parent;

    if( right->parent )
    {
        if( node->parent->left == node )
        {
            node->parent->left = right;
        }
        else
        {
            node->parent->right = right;
        }
    }

    node->parent = right;

    update_height(node);
    update_height(right);

    return right;
}

node_t *right_rotate(node_t *node)
{
    if( !node->left )
    {
        return nullptr;
    }

    node_t *left = node->left;
    node->left = left->right;

    left->right = node;
    left->parent = node->parent;

    if( left->parent )
    {
        if( node->parent->left == node )
        {
            node->parent->left = left;
        }
        else
        {
            node->parent->right = left;
        }
    }

    node->parent = left;

    update_height(node);
    update_height(left);

    return left;
}

node_t *rebalance_node(node_t *node)
{
    if( balance_factor(node) > 1 )
    {
        if( balance_factor(node->left) < 0 )
        {
            node->left = left_rotate(node->left);
        }

        node = right_rotate(node);
    }

    if( balance_factor(node) < -1 )
    {
        if( balance_factor(node->right) > 0 )
        {
            node->right = right_rotate(node->right);
        }

        node = left_rotate(node);
    }

    return node;
}

void insert_node(avl_t *tree, void *data)
{
    tree->root = insert_recursive(tree, tree->root, data);
}

node_t *insert_recursive(avl_t *tree, node_t *node, void *data)
{
    if( !node )
    {
        ++tree->size;
        return create_node(data);
    }

    int comparison = tree->comparator(data, node->data);

    if( comparison < 0 )
    {
        node->left = insert_recursive(tree, node->left, data);
        node->left->parent = node;
    }
    else if( comparison > 0 )
    {
        node->right = insert_recursive(tree, node->right, data);
        node->right->parent = node;
    }
    else
    {
        return node;
    }

    update_height(node);

    return rebalance_node(node);
}

bool contains(avl_t *tree, void *data)
{
    return find_node(tree, data);
}

void *remove_node(avl_t *tree, void *data)
{
    if( !tree || !data )
    {
        return nullptr;
    }

    node_t *removed_node = nullptr;
    tree->root = remove_recursive(tree, tree->root, &removed_node, data);

    if( !removed_node )
    {
        return nullptr;
    }

    data = removed_node->data;
    free(removed_node);

    return data;
}

node_t *
remove_recursive(avl_t *tree, node_t *node, node_t **removed_node, void *data)
{
    if( !tree || !node || !data )
    {
        return nullptr;
    }

    int comparison = tree->comparator(data, node->data);

    if( comparison < 0 )
    {
        node->left = remove_recursive(tree, node->left, removed_node, data);
    }
    else if( comparison > 0 )
    {
        node->right = remove_recursive(tree, node->right, removed_node, data);
    }
    else
    {
        --tree->size;

        node_t *parent = node->parent;
        bool was_left = (parent && parent->left == node) ? true : false;
        bool was_leaf = false;

        if( node->left && node->right )
        {
            node = remove_two_child(tree, node, removed_node);
        }
        else if( node->left || node->right )
        {
            node = remove_one_child(tree, node, removed_node);
        }
        else
        {
            node = remove_leaf(tree, node, removed_node);
            was_leaf = true;
        }

        node->parent = parent;

        if( parent )
        {
            if( was_left )
            {
                parent->left = node;
            }
            else
            {
                parent->right = node;
            }
        }

        if( was_leaf )
        {
            update_height(parent);
            rebalance_node(parent);
            return nullptr;
        }
    }

    update_height(node);

    return rebalance_node(node);
}

node_t *remove_leaf(avl_t *tree, node_t *node, node_t **removed_node)
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

    *removed_node = node;

    return node;
}

node_t *remove_one_child(avl_t *tree, node_t *node, node_t **removed_node)
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

    *removed_node = node;

    node = *relink_node = (node->left) ? node->left : node->right;

    if( node->parent->parent )
    {
        node->parent = node->parent->parent;
    }
    else
    {
        node->parent = nullptr;
    }

    return node;
}

node_t *remove_two_child(avl_t *tree, node_t *node, node_t **removed_node)
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

    if( predecessor->left || predecessor->right )
    {
        remove_one_child(tree, predecessor, removed_node);
    }
    else
    {
        remove_leaf(tree, predecessor, removed_node);
    }

    (*removed_node)->data = data;

    return node;
}

void clear(avl_t *tree)
{
    if( !tree )
    {
        return;
    }

    clear_recursive(tree->root, tree->deleter);
    tree->root = nullptr;
    tree->size = 0;
}

void clear_recursive(node_t *node, void (*deleter)(void *))
{
    if( !node )
    {
        return;
    }

    clear_recursive(node->left, deleter);
    clear_recursive(node->right, deleter);

    deleter(node->data);
    free(node);
}

void pre_order_print(avl_t *tree)
{
    if( !tree )
    {
        return;
    }

    pre_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void pre_order_traverse(avl_t *tree, void (*func)(void *))
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

void in_order_print(avl_t *tree)
{
    if( !tree )
    {
        return;
    }

    in_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void in_order_traverse(avl_t *tree, void (*func)(void *))
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

void post_order_print(avl_t *tree)
{
    if( !tree )
    {
        return;
    }

    post_order_recurse(tree->root, tree->printer);
    printf("\n\n");
}

void post_order_traverse(avl_t *tree, void (*func)(void *))
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

void level_order_print(avl_t *tree)
{
    if( !tree )
    {
        return;
    }

    level_order_traverse(tree, tree->printer);
    printf("\n\n");
}

void level_order_traverse(avl_t *tree, void (*func)(void *))
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

bool is_empty(avl_t *tree)
{
    return !tree || tree->size == 0;
}

void delete_avl(avl_t **tree)
{
    if( !tree || !*tree )
    {
        return;
    }

    clear(*tree);
    free(*tree);
    *tree = nullptr;
}
