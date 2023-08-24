#include "shell.h"


/**
 * str_error - prints  to standard error
 * @str: string to be printed
 *
 * Return: void
 */
void str_error(char *str)
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
 * int_to_str - converts an unsigned int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *int_to_string(unsigned int count)
{
	char *str;
	unsigned int temp, digit;

	temp = count;
	/* obtain int in reverse */
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	/* store the reversed int in an array */
	str = malloc(sizeof(char) * (digit + 1));
	if (!str)
	{
		perror("Abandon Ship!!");
		exit(127);
	}
	str[digit] = '\0';
	/* reverse the array */
	for (--digit; count; --digit)
	{
		str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (str);
}
