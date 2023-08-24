#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: first string
 * @src: second string
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *new_string;
	unsigned int l1, l2, combined_len, i, j;

	l1 = 0;
	l2 = 0;
	if (!dest)
		l1 = 0;
	else
	{
		for (l1 = 0; dest[l1]; l1++)
			;
	}
	if (!src)
		l2 = 0;
	else
	{
		for (l2 = 0; src[l2]; l2++)
			;
	}
	combined_len = l1 + l2 + 2;
	new_string = malloc(combined_len * sizeof(char));
	if (!new_string)
		return (NULL);
	/* copy the first string into the new array */
	for (i = 0; i < l1; i++)
		new_string[i] = dest[i];
	new_string[i] = '/';
	for (j = 0; j < l2; j++)
		new_string[i + 1 + j] = src[j];
	new_string[l1 + l2 + 1] = '\0';
	return (new_string);
}


/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: string length
 */
unsigned int _strlen(char *s)
{
	unsigned int i;

	i = 0;

	for (i = 0; s[i]; i++)
		;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 on success, any other output is an error
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strdup - creates a copy of a string
 * @duplicate: target string
 * Return: the replicated string
 */
char *_strdup(char *duplicate)
{
	char *new;
	int l = 0, i;

	if (duplicate == 0)
		return (NULL);

	for (; duplicate[l]; l++)
		;
	/* '+1' for the null terminator */
	new = malloc((l + 1) * sizeof(char));

	for (i = 0; i <= l; i++)
		new[i] = duplicate[i];

	return (new);
}

/**
 * str_out - writes to standard output
 * @s: string to be written
 *
 * Return: length of chars printed or -1 on failure
 */
ssize_t str_out(char *s)
{
	ssize_t num, len;

	num = _strlen(s);
	len = write(STDOUT_FILENO, s, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}
