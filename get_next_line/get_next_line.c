#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

 char *get_next_line(int fd) 
 {
    long size = (BUFFER_SIZE - BUFFER_SIZE) + 1;
    char *str = malloc(10000), *buf = str; 
    while (fd >= 0 && BUFFER_SIZE > 0 && read(fd, buf, size) && *buf++ != 10); 
    return (buf > str) ? (*buf = 0, str) : (free(str), NULL); 
 }
