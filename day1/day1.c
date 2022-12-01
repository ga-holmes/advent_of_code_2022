#include<stdio.h>
#include<stdlib.h>

// advent of code Day 1 challenge - written in C because I'm a masochist
// to run: compile using 'gcc day1.c', then run with './a.out'

int main(int argc, char const *argv[])
{
    // open file and get size of file
    FILE *fp = fopen("day1in.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "file not found.");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);

    long int fsize = ftell(fp);

    printf("%ld bytes\n", fsize);

    // create array - max size is max possible number of elves based on file size
    int *elves = malloc(fsize/sizeof(int));

    /* reset file to start */
    fseek(fp, 0L, SEEK_SET);

    char line[512];

    int highest = 0;
    int highest_index = -1;

    // where index 0 is 1st place
    int top3[3] = {0, 0, 0};
    int top3_index[3] = {0, 0, 0};

    int i = 0;
    int d = 0;
    while(feof(fp) == 0){

        fgets(line, 256, fp);

        int cal = atoi(line);

        if(cal == 0){

            // set highest (part 1)
            if (elves[i] > highest) {
                highest = elves[i];
                highest_index = i + 1;
            }

            for(d = 0; d < 3; d++){

                if( elves[i] >= top3[d] ){

                    // shift placement
                    int j = 0;
                    for(j = 2-d; j > 0; j--){
                        top3[d+j] = top3[(d+j)-1];
                    }
                    
                    // set new highest
                    top3[d] = elves[i];
                    top3_index[d] = i+1;
                    break;
                }
            } 

            i++;
        } else {
            elves[i] += cal;
        }

    }

    // print the top 3
    printf("top 3: "); 
    for (i = 0; i < 3; i++){
        printf("%d ", top3[i]);
    }
    printf("\n");

    printf("most calories: %d - elf #%d\n", highest, highest_index);
    printf("top 3 calories: %d - elves #%d, #%d, #%d\n", (top3[0] + top3[1] + top3[2]), top3_index[0], top3_index[1], top3_index[2]);

    /* free the elves */
    free(elves);
    fclose(fp);

    return 0;
}
