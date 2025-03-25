#include "../includes/header.h"


// // garbage collector here;

void *gc_malloc(t_gc *gc, size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;

    t_gc_node *node = (t_gc_node *)malloc(sizeof(t_gc_node));
    if (!node)
    {
        free(ptr);
        return NULL;
    }
    node->ptr = ptr;
    node->next = gc->allocations;
    gc->allocations = node;
    return ptr;
}

void gc_free_all(t_gc *gc)
{
    t_gc_node *current = gc->allocations;
    t_gc_node *next;

    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    gc->allocations = NULL;
}

void gc_destroy(t_gc *gc)
{
    if (!gc)
        return;
    gc_free_all(gc);
    free(gc);
}

