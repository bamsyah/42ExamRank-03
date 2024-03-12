#include "get_next_line.h"

int ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}

int ft_strchr(char *str)
{
	while (*str) {
		if (*str == '\n')
			return 1;
		str++;
	}
	return 0;
}

char *ft_strjoin(char *buffer, char *rest)
{
	char *all;
	int i = 0, j = 0;
	if (!buffer) return NULL;
	all = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(rest)) + 1);
	if (!all) return NULL;
	while (rest && rest[i]) all[i++] = rest[i++];
	while (buffer[j]) all[i++] = buffer[j++];
	all[i] = '\0';
	free(rest);
	return all;
}
