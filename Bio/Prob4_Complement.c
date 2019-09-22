#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	char letter;
	
	fp = fopen("ndna_255.fa", "r");
	if (fp == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    
    int countLength = 0,
		countNotACGT = 0;
    int isLabel = 0; // boolean
    char input[256];
    
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
				input[countLength] = letter;
				countLength++;				
			}						
		}
    }
    
    printf("Length = %d \n",countLength);
    countLength--;
    
    printf("Reverse Complement: ");
    while (countLength >= 0) {    	
		if (input[countLength] == 'A')
			printf("T");
		else if (input[countLength] == 'C')
			printf("G");
		else if (input[countLength] == 'G')
			printf("C");
		else if (input[countLength] == 'T')
			printf("A");
		else 
			printf("%c",input[countLength]);			
		countLength--;
	}
    
	fclose(fp);
	
	return 0;
}









