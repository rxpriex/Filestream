#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int fd;

void writeToFile(char* target, char* buffer)
{
    fd = open(target, O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("r1\n");
        exit(1);
    }

    size_t bytes = write(fd, buffer, strlen(buffer));
    if (bytes <= 0) {
        printf("Writing failed");
    }
    else {
        printf("Success");
    }
}

char* readFromFile(char* target, int bufferSize)
{
    if (bufferSize <= 0) {
        printf("Buffersize:%d is invalid", bufferSize);
        exit(1);
    }
    fd = open(target, O_RDONLY);
    if (fd < 0) {
        perror("r1\n");
        exit(1);
    }

    char* buffer = (char*)calloc(bufferSize, sizeof(char));

    int sz = read(fd, buffer, bufferSize);
    buffer[sz] = '\0';

    return buffer;
}

int isPath(char* p)
{
    return (strlen(p) > 0 && p[0] >= 'A' && p[0] <= 'Z') ? 1 : 0;
}

int main(int argc, char* argv[])
{
    if (!isPath(argv[1]) || argc < 4) {
        printf("Error: argv containts invalid arguments");
        return -1;
    }

    if (!strcmp(argv[2], "READ")) {
        printf(readFromFile(argv[1], atoi(argv[3])));
    }
    else if (!strcmp(argv[2], "WRITE")) {
        writeToFile(argv[1], argv[3]);
    }
    else {
        printf("Error: argv containts invalid arguments");
        return -2;
    }

    return 0;
}
