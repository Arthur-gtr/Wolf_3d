/*
** EPITECH PROJECT, 2024
** cat
** File description:
** open and write what's in the file
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_cat(char *file)
{
    int fd = 0;
    char buffer[30000];
    int size = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        write(2, "Error with open\n", 17);
        return 1;
    }
    size = read(fd, buffer, 29999);
    write(1, buffer, size);
    write(1, "\n", 1);
    close(fd);
    return 1;
}
