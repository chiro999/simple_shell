#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: first string
 * @src: second string
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *new;
	unsigned int len1, len2, len, i, j;

	len1 = 0;
	len2 = 0;
	if (dest == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; dest[len1]; len1++)
			;
	}
	if (src == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; src[len2]; len2++)
			;
	}
	len = len1 + len2 + 2;
	new = malloc(len * sizeof(char));
	if (new == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		new[i] = dest[i];
	new[i] = '/';
	for (j = 0; j < len2; j++)
		new[i + 1 + j] = src[j];
	new[len1 + len2 + 1] = '\0';
	return (new);
}


/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: length of string
 */
unsigned int _strlen(char *s)
{
	unsigned int len;

	len = 0;

	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
 * _strncmp - compares two strings
 * @s1: first string, of two, to be compared in length
 * @s2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _strncmp(char *s1, char *s2)
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
 * _strdup - returns pointer to new mem alloc space which contains copy
 * @duplicate: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *_strdup(char *duplicate)
{
	char *copy;
	int len, i;

	if (duplicate == 0)
		return (NULL);

	for (len = 0; duplicate[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		copy[i] = duplicate[i];

	return (copy);
}

/**
 * _puts - writes a string to standard output
 * @s: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _puts(char *s)
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
