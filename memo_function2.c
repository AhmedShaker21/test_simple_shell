#include "shell.h"
/**
 * free_ptr - deallocates a pointer and sets it to NULL
 * @pointer_address: address of the pointer to deallocate
 *
 * Return: 1 if deallocated, otherwise 0.
 */

int free_ptr(void **pointer_address)
{
        if ((pointer_address != NULL) && (*pointer_address != NULL))
        {
                free(*pointer_address);
                *pointer_address = NULL;
                return (1);
        }
        return (0);
}
/**
 * resize_memory - changes the size of a memory block
 * @old_ptr: pointer to the old memory block
 * @old_bytes: byte size of the old memory block
 * @new_bytes: byte size of the new memory block
 * Return: pointer to the new memory block, or NULL if allocation fails
 */

void *resize_memory(void *old_ptr, unsigned int old_bytes,
                unsigned int new_bytes)
{
        char *new_ptr;
        unsigned int i;

        if (old_ptr == NULL)
                return (malloc(new_bytes));
        if (new_bytes == 0)
                return (free(old_ptr), NULL);
        if (new_bytes == old_bytes)
                return (old_ptr);
        new_ptr = malloc(new_bytes);
        if (new_ptr == NULL)
                return (NULL);
        old_bytes = old_bytes < new_bytes ? old_bytes : new_bytes;
        for (i = 0; i < old_bytes; i++)
                new_ptr[i] = ((char *)old_ptr)[i];
        free(old_ptr);
        return (new_ptr);
}
