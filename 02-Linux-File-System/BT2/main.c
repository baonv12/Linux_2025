#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    const char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    const char *mode = argv[3];
    const char *data = argv[4];

    if (num_bytes <= 0) {
        printf("num-bytes must be > 0\n");
        return 1;
    }

    int fd;

    if (strcmp(mode, "r") == 0) {
        fd = open(filename, O_RDONLY);
        if (-1 == fd) {
            perror("Open file for reading failed");
            return 1;
        }

        char *buffer = (char *)malloc(num_bytes + 1);

        ssize_t bytes_read = read(fd, buffer, num_bytes);
        if (bytes_read < 0) {
            printf("Error reading file");
            free(buffer);
            close(fd);
            return 1;
        }

        buffer[bytes_read] = '\0';
        printf("Read %ld bytes: %s\n", bytes_read, buffer);

        free(buffer);
        close(fd);

    } else if (strcmp(mode, "w") == 0) {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (-1 == fd) {
            printf("Open file for writing failed");
            return 1;
        }

        ssize_t num_write = (strlen(data) < num_bytes) ? strlen(data) : num_bytes;
        ssize_t bytes_written = write(fd, data, num_write);
        if (bytes_written < 0) {
            printf("Error writing to file");
            close(fd);
            return 1;
        }

        printf("Wrote %ld bytes to %s\n", bytes_written, filename);
        close(fd);

    } else {
        printf("Invalid mode, only accept 'r' for read or 'w' for write.\n");
        return 1;
    }

    return 0;
}