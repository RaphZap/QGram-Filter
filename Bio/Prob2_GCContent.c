#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
	clock_t begin = clock();
	
	FILE *fp;
	char letter;
	
	fp = fopen("ndna_255.fa", "r");
	if (fp == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    
    int countA = 0,
		countC = 0,
		countG = 0,
		countT = 0,
		countLength = 0,
		countNotACGT = 0;
    int isLabel = 0; // boolean
    
    while (fscanf(fp, "%c", &letter) == 1 ) {
    	if (letter == '>') {
    		isLabel = 1;
		}
		
		if (isLabel == 1) {
    		if (letter == '\n') { // end of label
    			isLabel = 0;
    		}    		
		} else { // isn't part of the label
			if (letter != '\n') {
				countLength++;
				if (letter == 'A')
					countA++;
				else if (letter == 'C')
					countC++;
				else if (letter == 'G')
					countG++;
				else if (letter == 'T')
					countT++;
				else 
					countNotACGT++;				
			}				
		}
    }
    
//    printf("Count A: %d\n", countA);
    printf("Count C: %d\n", countC);
    printf("Count G: %d\n", countG);
//    printf("Count T: %d\n", countT);
//    printf("Count non-ACGT: %d\n", countNotACGT);
    printf("DNA Length: %d\n", countLength);
    
    printf("GC-content: %2.2lf%%\n", (double)(countC+countG)/(double)countLength * 100);
	fclose(fp);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;	
	printf("\n time = %lf ms", time_spent);
	
	
	return 0;
}
