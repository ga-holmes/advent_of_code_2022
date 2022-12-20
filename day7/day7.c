#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 1000

struct Directory;

typedef struct
{
    char *name;
    int size;

    struct Directory *parent;

} File;


typedef struct Directory{

    char *name;
    int size;

    File **files;
    struct Directory **children;

    struct Directory *parent;

} Directory;


Directory * initDirectory(char *name, Directory *parent){

    Directory *dir = malloc(sizeof(Directory *)+1);

    dir->name = name;
    dir->files = malloc(sizeof(File *) * MAX_DIRS);
    dir->children = malloc(sizeof(Directory *) * MAX_DIRS);
    dir->parent = parent;

    return dir;

}

int freeDir(Directory *dir){

    int i;

    for(i = 0; dir->files[i] != NULL; i++) {
        free(dir->files[i]);
    }

    for(i = 0; dir->children[i] != NULL; i++){
        freeDir(dir->children[i]);
    }

    free(dir);

    return 0;

}

Directory * findDir(char *name, Directory ** dirs){

    int i;
    for(i = 0; dirs[i] != NULL; i++){
        if(strcmp(name, dirs[i]->name) == 0){
            return dirs[i];
        }
    }

    return NULL;

}

// given a string, splits it by a delimiter and returns the split string at the given index
char *index_find(char *line, char *delim, int index){

    int i = 0;
    char *token = strtok(line, delim);
    char *prev;

    while (token != NULL) {
        // printf("STRTOK: %s\n", token);

        if(index > -1 && i == index){
            return token;
        }

        strcpy(prev, token);

        token = strtok(NULL, delim);
        
        if(token == NULL){ return prev; }
        i++;
    }
}

// advent of code Day 7 challenge - written in C because it made sense for this one
// to run: compile using 'gcc day7.c', then run with './a.out'

int main(int argc, char const *argv[]) {
    // open file and get size of file
    FILE *fp = fopen("day7in.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "file not found.");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);

    long int fsize = ftell(fp);

    printf("%ld bytes\n", fsize);

    /* reset file to start */
    fseek(fp, 0L, SEEK_SET);

    char line[512];
    int totalSize = 0;

    // create array - max size is max possible number of dirs based on file size
    int dirs_amt = 0;
    Directory **dirs = malloc(MAX_DIRS * sizeof(Directory *));

    Directory *root = initDirectory("/", NULL);
    dirs[dirs_amt] = root;
    dirs_amt++;

    Directory *currDir = NULL;
    
    int i = 0;
    while (feof(fp) == 0) {

        fgets(line, 256, fp);
        // remove newline
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }

        printf("%s\n", line);

        if(strcmp(line, "$ ls") != 0){

            if(line[0] == '$'){

                char *cd = index_find(line, " ", -1);

                printf("CD: %s\n", cd);
                if( strcmp(cd, "..") == 0 ){
                    currDir = currDir->parent;
                } else {
                    currDir = findDir(cd, dirs);
                }

            } else if (line[0] == 'd'){

                char *dir = index_find(line, " ", 1);
                printf("DIR: %s\n", dir);

            }else {

                char *size = index_find(line, " ", 0);
                char *fname = strtok(NULL, " "); // use base strtok to get the filename
                printf("SIZE: %s, NAME: %s\n", size, fname);

            }

        }
        
    }

    /* free the dirs */
    for(i = 0; dirs[i] != NULL; i++){
        freeDir(dirs[i]);
    }
    free(dirs);
    fclose(fp);

    return 0;
}
