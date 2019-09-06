#include <stdio.h>
#include <stdlib.h>
#define length 910

typedef char String[length];

int main() {
	FILE *fp;
	char letter;
	String s;
	String t;
	
	int j;
	for(j=0; j<length; j++) {
		s[j] = t[j] = '\0';
	}
	
	fp = fopen("rosalind_subs.txt", "r");
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
		}				
    }
    
	int i;
	printf("s: ");
	for(i=0; i<index1; i++) {		
		printf("%c", s[i]);
	}
	printf("\n\nt: ");	
	for(i=0; i<index2; i++) {		
		printf("%c", t[i]);
	}
	
	// checking
	int locations[index1-index2+1];
	for(i=0; i<index1-index2+1; i++) {
		locations[i] = 0;
	}
	
	int num = 0;
	int k;
	for (i=0; i<index1-index2+1; i++) {
		int x = i;
		int good = 0;
		for(k=0; k<index2; k++) {
			if (s[x] == t[k]) {
				if (k==index2-1) {
					locations[num] = x-index2+2;
					num++;
				}
				x++;
			} else { 
				break; // stop checking
			}			
		}
	}
	
	printf("\nnum: %d",index1);
	printf("\n\n locations: ");
	for(i=0; i<num; i++) {
		printf("%d, ",locations[i]);
	}
	
	fclose(fp);
	
	return 0;
}
