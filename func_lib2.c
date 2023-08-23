#include "shell.h"

/**
 * _printer - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void _printer(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}


/**
 * _int_str - converts an unsigned int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_int_str(unsigned int count)
{
	char *str;
	unsigned int temp, digit;

	temp = count;
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	str = malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
	{
		perror("Abandon Ship!!");
		exit(127);
	}
	str[digit] = '\0';
	for (--digit; count; --digit)
	{
		str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (str);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, max;

	max = INT_MAX;
	for (digits = 0; max != 0; digits++)
		max /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);
}
