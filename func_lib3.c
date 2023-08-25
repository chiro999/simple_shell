#include "shell.h"

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	/* custom atoi function with layered error checks */
	unsigned int i, digits;
	int num = 0, max;

	max = INT_MAX;
	/* find the number of digits in max */
	for (digits = 0; max != 0; digits++)
		max /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		/* check for overflow in last digit position */
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		/* check for overflow in last - 1 digit position */
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	/* check for excess characters */
	if (i > digits)
		return (-1);
	return (num);
}
