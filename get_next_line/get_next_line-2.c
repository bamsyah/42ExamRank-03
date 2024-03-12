#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 32

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
    while (rest && rest[i]) all[i++] = rest[j++];
    while (buffer[j]) all[i++] = buffer[j++];
    all[i] = '\0';
    free(rest);
    return all;
}

char *ft_strdup(char *str)
{
    char *copy;
    int i = 0;
    copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!copy) return NULL;

    while (str[i]) {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return copy;
}

char *read_file(int fd, char *rest)
{
    char *buffer;
    ssize_t read_size;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer) return NULL;
    if (!rest) rest = ft_strdup("");
    read_size = 1;
    while (!ft_strchr(rest) && read_size != 0) {
        read_size = read(fd, buffer, BUFFER_SIZE);
        if (read_size == -1) return NULL;
        buffer[read_size] = '\0';
        rest = ft_strjoin(buffer, rest);
    }
    free(buffer);
    return rest;
}

char *ft_getline(char *rest)
{
    char *line;
    int i = 0;
    while (rest[i] != '\n' && rest[i]) i++;
    if (rest[i] == '\n') i++;
    line = malloc(i + 2);
    if (!line) return NULL;
    i = 0;
    while (rest[i] && rest[i] != '\n') line[i] = rest[i++];
    if (rest[i] == '\n') line[i++] = '\n';
    line[i] = '\0';
    return line;
}

char *ft_getrest(char *rest, char *line)
{
    char *getrest;
    int i = ft_strlen(line), j = 0;
    while (rest[i++]) j++;
    getrest = malloc(sizeof(char) * (j + 1));
    if (!ft_getrest) return NULL;
    i = ft_strlen(line);
    j = 0;
    while (rest[i]) getrest[j++] = rest[i++];
    getrest[j] = '\0';
    free(rest);
    return getrest;
}

char *get_next_line(int fd)
{
    char *line;
    static char *rest;
    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;
    rest = read_file(fd, rest);
    if (!rest) return NULL;
    line = ft_getline(rest);
    if (line[0] == '\0') {
        free(rest);
        rest = NULL;
        return NULL;
    }
    rest = ft_getrest(rest, line);
    if (!rest) return NULL;
    return line;
}
