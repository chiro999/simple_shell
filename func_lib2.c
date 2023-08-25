#include "shell.h"


/**
 * str_error - prints  to standard error
 * @str: string to be printed
 *
 * Return: void
 */
void str_error(char *string)
{
	ssize_t str_len;
       	ssize_t	output;

	str_len = _strlen(string);
	output = write(STDERR_FILENO, string, str_len);
	if (output != str_len)
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
