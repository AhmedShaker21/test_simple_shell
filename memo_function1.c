#include "shell.h"
/**
 *fill_memory - assigns a constant byte to a memory area
 *@mem: the pointer to the destination memory area
 *@byte: the byte to assign to *dest
 *@size: the number of bytes to be assigned
 *Return: (dest) a pointer to the destination memory area
 */
char *fill_memory(char *mem, char byte, unsigned int size)
{
	unsigned int i = 0;

	if (mem == NULL)
		return (NULL);
	while (i < size)
	{
		mem[i] = byte;
		i++;
	}
	return (mem);
}

/**
*free_2d_array - frees the memory allocated for
a two-dimensional array of characters
*@array: pointer to the array
*/
void free_2d_array(char **array)
{
	int i;

	if (!array)
		return;
	for (i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}
