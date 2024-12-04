#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void processFile(char *path, char *script, char *instruction) {
    char allPythonWay[1024];

    snprintf(allPythonWay, sizeof(allPythonWay), "%s %s %s" , instruction, script, path);

    system(allPythonWay);

    printf("I just executed %s\n", path);
}

void identifyDirectories(char *path, char *script, char *instruction) {
    struct dirent *entry;

    DIR *dir = opendir(path);

    if (dir == NULL) {
        return;
    }

    pid_t fork_result;

    printf("Starting process in %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0) {
            continue;
        }
        
        char newPath[1024];
        snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);

        if (entry->d_type == 4) {
            fork_result = fork();
            if (fork_result == 0) {
                identifyDirectories(newPath, script, instruction);
                return;
            }
        }
        else if (entry -> d_type == 8) {
            fork_result = fork();
            if (fork_result == 0) {
                processFile(newPath, script, instruction);
                return;
            }
        }
    }

    printf("Ending process in %s\n", path);
}

int main(int argc, char *argv[]) {
    char *path, *script, *instruction;

    if (argc > 3) {
        path = argv[3];
        script = argv[2];
        instruction = argv[1];
    } 
    else {
        printf("You need to type the instructioner, the path for the instruction and the path.\n");
        return EXIT_SUCCESS;
    }

    identifyDirectories(path, script, instruction);

    return EXIT_SUCCESS;
}

