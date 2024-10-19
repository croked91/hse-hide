#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const char *darkDirectory = "./.dark_directory";

void hideFile(const char *fileName) {
    struct stat st;

    if (stat(fileName, &st) != 0) {
        printf("File %s does not exist.\n", fileName);
        return;
    }

    if (stat(darkDirectory, &st) != 0) {
        if (mkdir(darkDirectory, 0755) != 0) {
            perror("Failed to create dark directory");
            return;
        }
    }

    char newFilePath[1024];
    snprintf(newFilePath, sizeof(newFilePath), "%s/%s", darkDirectory, fileName);

    if (rename(fileName, newFilePath) != 0) {
        perror("Failed to move file");
        return;
    }

    if (chmod(darkDirectory, 0111) != 0) {
        perror("Failed to set permissions for dark directory");
        return;
    }

    printf("File %s has been hidden in %s\n", fileName, newFilePath);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Path to file not found. Usage: hide <filename>\n");
        return 1;
    }

    hideFile(argv[1]);
    return 0;
}