#include "get_next_line.h"

int 	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	ft_strchr(char *rest)
{
	int	i = 0;
	while (rest && rest[i])
	{
		if (rest[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
char	*ft_strjoin(char *buffer, char *rest)
{
	char	*all;
	int		i = 0;
	int		y = 0;
	if (!buffer)
		return (NULL);
	all = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(rest)) + 1);
	if (!all)
		return (NULL);
	while (rest && rest[i])
	{
		all[i] = rest[i];
		i++;
	}
	while (buffer[y])
		all[i++] = buffer[y++];
	all[i] = '\0';
	free(rest);
	return (all);
}
char	*ft_strdup(char *str)
{
	char	*sstr;
	int		i = 0;
	sstr = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!sstr)
		return (NULL);
	while (str[i])
	{
		sstr[i] = str[i];
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}

char	*read_file(int fd, char *rest)
{
	char		*buffer;
	ssize_t		rread;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!rest)
		rest = ft_strdup("");
	rread = 1;
	while (!ft_strchr(rest) && rread != 0)
	{
		rread = read(fd, buffer, BUFFER_SIZE);
		if (rread == -1)
			return (free(buffer), free(rest), NULL);
		buffer[rread] = '\0';
		rest = ft_strjoin(buffer, rest);
	}
	return (free(buffer), rest);
}

char	*ft_getline(char *rest)
{
	char	*str;
	int		i = 0;
	while (rest[i] != '\n' && rest[i])
		i++;
	if (rest[i] == '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		str[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_getrest(char *rest, char *line)
{
	char	*rrest;
	int		i = ft_strlen(line);
	int		j = 0;
	while (rest[i++])
		j++;
	rrest = malloc(sizeof(char) * (j + 1));
	if (!rrest)
		return (NULL);
	i = ft_strlen(line);
	while (rest[i])
		rrest[j++] = rest[i++];
	rrest[j] = '\0';
	free(rest);
	return (rrest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_file(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_getline(rest);
	if (line[0] == '\0')
	{
		free(rest);
		rest = NULL;
		return (free(line), NULL);
	}
	rest = ft_getrest(rest, line);
	if (!rest)
		return (free(line), NULL);
	return (line);
}
