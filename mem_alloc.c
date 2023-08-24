#include "shell.h"

/**
 * more_mem - doubles or increases the memory space
 * @old_arr: old array
 * @n: number of elements in old_array
 *
 * Return: pointer to the new array
 */
char **more_mem(char **old_arr, size_t *n)
{
	char **new_arr;
	size_t i = 0;

	/* new array with increased memory */
	new_arr = malloc(sizeof(char *) * ((*n) + 10));
	if (!new_arr)
	{
		free(old_arr);
		return (NULL);
	}
	/* transfer elements from old arr to new arr iteratively */
	for (; i < (*n); i++)
	{
		new_arr[i] = old_arr[i];
	}
	*n = *n + 10;
	free(old_arr);
	return (new_arr);
}
