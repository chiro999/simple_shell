#include "shell.h"

/**
 * more_mem - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **more_mem(char **old_arr, size_t *size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(old_arr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = old_arr[i];
	}
	*size += 10;
	free(old_arr);
	return (new);
}
