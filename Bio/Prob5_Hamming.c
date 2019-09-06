#include <stdio.h>
#include <stdlib.h>
#define length 910

typedef char String[length];

int main() {
	FILE *fp;
	char letter;
	String s;
	String t;
	
	fp = fopen("rosalind_hamm.txt", "r");
	if (fp == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    
    int isNewLine = 0; // boolean
    int count = 0;
    int index1 = 0,
    	index2 = 0;
    
    while (fscanf(fp, "%c", &letter) == 1 ) {
    	if (isNewLine == 1) {
//    		printf("\n\n");
    		isNewLine = 2; // reset
//    		break;
		}
		
    	if (letter == '\n') { // end of label
    		isNewLine = 1;    		
		} else {
			if (isNewLine == 0) {
				s[index1] = letter;
				index1++;
			}
			else if (isNewLine == 2) {
				t[index2] = letter;
				index2++;	
			}
//			printf("%c", letter);
//			count++;
		}				
    }
    
//    printf("\nCount: %d", count);

	// DEBUGGING
	int i;
//	printf("\n\ns: ");
//	for(i=0; i<length; i++) {		
//		printf("%c", s[i]);
//	}
//	printf("\n\nt: ");	
//	for(i=0; i<length; i++) {		
//		printf("%c", t[i]);
//	}
//	
	// checking
	int hamCount = 0;
	for(i=0; i<length; i++) {		
		if (s[i] != t[i]) {
			hamCount++;
		}
	}
//	printf("\n\n");
	printf("hamming distance: %d", hamCount);
	
	fclose(fp);
	
	return 0;
}
