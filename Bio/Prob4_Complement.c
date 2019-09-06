#include <stdio.h>
#include <stdlib.h>

// typedef char String[29];

int main() {
	
	// String input;
	FILE *fp;
	char word[256];
	char letter;
	
	fp = fopen("ndna_255.fa", "r");
	if (fp == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    
//	while (fscanf(fp, "%s", word) == 1 ) {
//	    printf("%s ", word);		
//    }
    
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
//				printf("%c",letter);
				countLength++;
				if (letter == 'A')
					printf("T");
				else if (letter == 'C')
					printf("G");
				else if (letter == 'G')
					printf("C");
				else if (letter == 'T')
					printf("A");
				else 
					printf("%c",letter);			
			}				
		}
    }
    
    
	fclose(fp);
	
	return 0;
}
