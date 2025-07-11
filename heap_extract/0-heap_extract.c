#include "binary_trees.h"

/**
 * get_last_node - Gets the last level-order node in the heap
 * @root: Pointer to the root of the heap
 * Return: Pointer to the last node, or NULL if heap is empty
 */
static heap_t *get_last_node(heap_t *root)
{
    heap_t *last = NULL;
    int height, i;

    if (!root)
        return (NULL);

    /* Find the height of the tree */
    height = 0;
    for (heap_t *temp = root; temp->left; temp = temp->left)
        height++;

    /* Find the last node using level-order traversal */
    last = root;
    for (i = 0; i < height; i++)
    {
        if (last->right)
            last = last->right;
        else if (last->left)
            last = last->left;
        else
            break;
    }

    /* If we didn't reach a leaf, find the rightmost node at this level */
    while (last->right)
        last = last->right;

    return (last);
}

/**
 * heapify_down - Rebuilds the heap after extracting the root
 * @root: Pointer to the root of the heap
 */
static void heapify_down(heap_t *root)
{
    heap_t *largest = root;
    heap_t *left = root->left;
    heap_t *right = root->right;
    int temp;

    /* Find the largest among root, left child, and right child */
    if (left && left->n > largest->n)
        largest = left;

    if (right && right->n > largest->n)
        largest = right;

    /* If the largest is not the root, swap and continue heapifying */
    if (largest != root)
    {
        temp = root->n;
        root->n = largest->n;
        largest->n = temp;
        heapify_down(largest);
    }
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * Return: The value stored in the root node, or 0 if function fails
 */
int heap_extract(heap_t **root)
{
    int value;
    heap_t *last_node, *parent;

    if (!root || !*root)
        return (0);

    /* Store the value to return */
    value = (*root)->n;

    /* If this is the only node in the heap */
    if (!(*root)->left && !(*root)->right)
    {
        free(*root);
        *root = NULL;
        return (value);
    }

    /* Find the last level-order node */
    last_node = get_last_node(*root);
    if (!last_node)
        return (0);

    /* Replace root value with last node value */
    (*root)->n = last_node->n;

    /* Remove the last node from the tree */
    parent = last_node->parent;
    if (parent)
    {
        if (parent->left == last_node)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    free(last_node);

    /* Rebuild the heap if necessary */
    heapify_down(*root);

    return (value);
}
