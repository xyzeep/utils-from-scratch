#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int is_dir(const char *path) {
    struct stat stat_buffer;
    stat(path, &stat_buffer);

    return S_ISDIR(stat_buffer.st_mode);
}


int catz(const char *path) {
    char buffer[BUFFER_SIZE];
    size_t n_read_bytes;

    FILE *fp= fopen(path, "r");

    if (fp == NULL) {
        perror(path);
        return 1;
    }

    printf("\n=========== %s ==========\n", path);
    printf("\n");

    while ((n_read_bytes = fread(buffer, 1, BUFFER_SIZE, fp))) {
        fwrite(buffer,1,  n_read_bytes, stdout);
    }

    fclose(fp);
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Usage: %s [filepath]", argv[0]);
        return 1;
    }

    char *current_path;

    // for each argument check if it's a file or a dir and run catz on it
    for (int i = 1; i < argc; i++) {

        current_path = argv[i];

        //check if it's a file or a dir
        if (is_dir(current_path)) {
            // TODO: run catz() on every file inside it.
            printf("TODO: run catz() on every file inside it");
        }
        
        // if it's a file
        else {
            catz(current_path);
        }

    }

    return 0;
}

