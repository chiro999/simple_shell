#include "shell.h"

/**
 * more_mem - doubles or increases the memory space
 * @old_arr: old array
 * @size: number of elements in old_array
 *
 * Return: pointer to the new array
 */
char **more_mem(char **old_arr, size_t *size)
{
	char **new_arr;
	size_t i;

	new_arr = malloc(sizeof(char *) * ((*size) + 10));
	if (new_arr == NULL)
	{
		free(old_arr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new_arr[i] = old_arr[i];
	}
	*size += 10;
	free(old_arr);
	return (new_arr);
}
