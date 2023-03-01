#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    int fd = open(argv[1], O_RDONLY);
    off_t fsize = lseek(fd, 0, SEEK_END);

    char* map = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    char* copy = malloc(fsize);

    memcpy(copy, map, fsize);
    mprotect(map, fsize, PROT_READ | PROT_WRITE);

    memset(map, 'A', fsize);
    munmap(map, fsize);

    write(fd, copy, fsize);
    close(fd);

    return 0;
}
