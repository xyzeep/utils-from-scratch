#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFFER_SIZE 4096

int is_dir(const char *path) {
    struct stat stat_buffer;
    stat(path, &stat_buffer);

    return S_ISDIR(stat_buffer.st_mode);
}


int is_ignore(const char *path) {
    if (path[0] == '.') {
        return 1;
    }
    return 0;
}

int is_regf(const char *path) {
    struct stat stat_buffer;
    stat(path, &stat_buffer);

    return S_ISREG(stat_buffer.st_mode);
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
        

        if (is_ignore(current_path)) {
            continue;
        }

        //check if it's a file or a dir
        else if (is_dir(current_path)) {

            // pointer for directory entry
            struct dirent *de;

            DIR *dp = opendir(current_path);

            if (dp == NULL) {
                printf("Couldn't open %s", current_path);
                return 1;
            }

            char *current_sub_path;
            size_t sub_path_len;
            while ((de = readdir(dp)) != NULL) {
                // if (strcmp(de->d_name, ".") == 0 ||
                //         strcmp(de->d_name, "..") == 0) {
                //     continue;
                //
                    if (is_ignore(de->d_name)) continue;
                
                
                sub_path_len = strlen(current_path) + strlen(de->d_name) + 2;
                snprintf(current_sub_path, sub_path_len, "%s/%s", current_path, de->d_name);

                if (!is_dir(current_sub_path)) {
                        catz(current_sub_path);
                }
            }

            closedir(dp);

        }

        // if it's a file
        else {
            catz(current_path);
        }

    }

    return 0;
}
