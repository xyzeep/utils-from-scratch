#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Usage: %s [filepath]", argv[0]);
        return 1;
    }


    char buffer[BUFFER_SIZE];
    size_t n_read_bytes;

    for (int i = 1; i < argc; i++) {

        FILE *fp= fopen(argv[i], "r");

        if (fp == NULL) {
            perror(argv[i]);
            return 1;
        }

        printf("\n=========== %s ==========\n", argv[i]);
        printf("\n");

        while ((n_read_bytes = fread(buffer, 1, BUFFER_SIZE, fp))) {
            fwrite(buffer,1,  n_read_bytes, stdout);
        }

        fclose(fp);
    }

    return 0;
}

