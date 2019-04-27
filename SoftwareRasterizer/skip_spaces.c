#include <stdio.h>

char* skip_spaces(char* str)
{
	int i;

	if (str == NULL)
		return NULL;

	for (i = 0; str[i] == ' ' || str[i] == '\t'; i++)
		;

	if (str[i] == 0)
		return NULL;

	return str + i;
}

char* skip_non_spaces(char* str)
{
	int i;

	if (str == NULL)
		return NULL;

	for (i = 0; str[i] != ' ' && str[i] != '\t' && str[i] != 0; i++)
		;

	if (str[i] == 0)
		return NULL;

	return str + i;
}
