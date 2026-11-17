#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096


int is_dir(const char *path) {
    struct stat stat_buffer;
    stat(path, &stat_buffer);

    return S_ISDIR(stat_buffer.st_mode);
}

int main(int argc, char *argv[]) {
    if (is_dir(argv[1])) {
        printf("Yes, a dir.");
    }
    else {
        printf("No, a file.");
    }
    return 0;
}
