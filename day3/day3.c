#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compares 2 int arrays, outputs the array containing all matching values in the compared arrays, returns the length of the outputed array - Assumes all arrays are initialized
int searchIntArr(int *arr1, int arr1Len, int *arr2, int arr2Len, int *outArr){
    int k = 0;
    int i = 0;
    int j = 0;
    // compare all values in score 1 to values in score 2
    for (i = 0; i < arr1Len; i++) {

        for (j = 0; j < arr2Len; j++) {

            // if there is a match, add to the array of matches in both of the first two groups
            if (arr1[i] == arr2[j]) {
                outArr[k] = arr1[i];
                k++;
            }
        }
    }

    return k;
}

// advent of code Day 3 challenge - written in C
// to run: compile using 'gcc day3.c', then run with './a.out'

int main(int argc, char const *argv[]) {
    // open file and get size of file
    FILE *fp = fopen("day3in.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "file not found.");
        exit(1);
    }

    char line[256];

    int matchScore = 0;

    // PART 2
    int groups[3][256];
    int groupsLen[3] = {0, 0, 0};
    int sumOfBadges = 0;

    int totalCount = 0;

    /* PART 1 */
    int c = 0;
    int i = 0;
    int d = 0;
    while (feof(fp) == 0) {

        int score1[128];
        int score2[128];

        fscanf(fp, "%s\n", line);

        d = strlen(line)/2;
        for(i = 0; i < strlen(line)/2; i++){
            
            // values split - ternary: if uppercase, subtract 38 (higher values), else subtract 96 (lower values) -> relying on ascii numbers
            score1[i] = line[i] > 91 ? line[i] - 96 : line[i] - 38;
            score2[i] = line[i+d] > 91 ? line[i+d] - 96 : line[i+d] - 38;

            // put entire line into the group location to keep track of the last 3 elves
            groups[c][i] = line[i] > 91 ? line[i] - 96 : line[i] - 38;
            groups[c][i+d] = line[i + d] > 91 ? line[i + d] - 96 : line[i + d] - 38;
            groupsLen[c] = d * 2;

        }

        int outArr[128];
        int out = searchIntArr(score1, d, score2, d, outArr);

        // should only be 1 match
        matchScore += out > 0 ? outArr[0] : 0;

        c++;

        // every 3 sacks, reset the count and the group array
        if(c != 0 && c%3 == 0){

            // compare the first 2 sacks in the group
            int outArr[256];
            int out = searchIntArr(groups[0], groupsLen[0], groups[1], groupsLen[1], outArr);

            // if there was only 1 match in the first 2 sacks, there can only be 1 in the third
            if(out == 1){
                sumOfBadges += out;
            } else { // search again
                
                int finalOut[256];
                out = searchIntArr(outArr, out, groups[2], groupsLen[2], finalOut);

                sumOfBadges += out > 0 ? finalOut[0] : 0; // in case output array finds nothing, add nothing

            }

            // reset groups arrays
            memset(groups[0], -1, 256 * sizeof(int));
            memset(groups[1], -1, 256 * sizeof(int));
            memset(groups[2], -1, 256 * sizeof(int));

            c = 0;
            totalCount++;
        }
    }

    // final:
    printf("Sum of all misplaced items: %d\n", matchScore);
    printf("Sum of all badges: %d\n", sumOfBadges);

    /* free the elves */
    fclose(fp);

    return 0;
}
