#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


int main() {
	clock_t begin = clock();
	
//	FILE *fp;
	char letter;
	char s[] = "TTATCTCTTA";
	char alphabet[] = "ACGT";	
    
    int q = 2;
//    printf("Input q: ");
//    scanf("%d",&q);
//    int range = pow(q, 4) + 1; // 4 = length of alphabet
    int s_length = strlen(s);
    
    // for Open Addressing
    double alpha = 0.8;
    int C_size = (int) floor(pow(alpha, -1) * s_length);
    int C[C_size];
    int j;
    for (j=0; j<C_size; j++) {
    	C[j] = -1;
	}    
	int range = C_size+1;
    int dir[range];	
    for(j=0; j<range; j++) {				// initialization    
    	dir[j] = 0;
	}
	int c;
	char word[q];
	for(j=0; j<strlen(s) - q + 1 ; j++) {	// count q-grams
		strncpy(word, s+j, q);
		word[q] = '\0';
		c = code(word, q);
		c = reqBkt(c, C, C_size);		// ADDED 
		dir[c+1] = dir[c+1]+1;	
	}	
	int sum = max(0,strlen(s)-q+1);
	for (j=range-1; j>=0; j-- ) {			// cumaltive sum
		sum = sum - dir[j];
		dir[j] = sum;
	}
	int pos[strlen(s)-q+1];	
	for (j=0; j<strlen(s) - q + 1; j++) {	// fill position table	
		strncpy(word, s+j, q);
		word[q] = '\0';
		c = code(word, q);
		c = getBkt(c, C, C_size); 		// ADDED 
		pos[dir[c+1]] = j;
		dir[c+1] = dir[c+1] + 1;		
	}
	
    // return/output dir, pos, code table
    printf("C: \t");
    for(j=0; j<C_size ; j++) {
		printf("|%d",C[j]);
	}
    printf("\ndir: \t");
    for(j=0; j<range ; j++) {
		printf("|%d",dir[j]);
	}
	printf("\npos: \t");
    for(j=0; j<strlen(s)-q+1 ; j++) {
    	printf("|%d",pos[j]);
    }
    printf("\ntext: %s", s);
    // return dir, pos;
    
    // input q-gram
    char query[] = "TC";
    printf("\n\nWhere's %s?\n", query);
    int codevalue = code(query, q);
    int dirIndex = getBkt(codevalue, C, C_size);
    int numGrams = dir[dirIndex+1] - dir[dirIndex];
    int posIndex = dir[dirIndex];
    // output location
    printf("Locations: ");
    while (numGrams > 0) {
    	printf("%d, ", pos[posIndex]);
    	posIndex++;
    	numGrams--;
	}
    
    
    
//	fclose(fp);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;	
	printf("\n time = %lf ms", time_spent);
	
	return 0;
}


int code(char str[], int q) {
	int i = 0;
	int sum = 0;
	while (i < strlen(str) ) {
//		printf("%c ", str[i]);
		switch (str[i]) {
			case 'A': sum += 0 * (int) pow(4, q - 1 - i); 
				break;
			case 'C': sum += 1 * (int) pow(4, q - 1 - i);
				break;
			case 'G': sum += 2 * (int) pow(4, q - 1 - i); 
				break;
			case 'T': sum += 3 * (int) pow(4, q - 1 - i); 
				break;
//			default:
		}
//		printf("%d \t", sum);
		i++;
	}
	
	return sum;
}

int getBkt(int c, int C[], int size) {
//	int size = (int)( sizeof(C) / sizeof(C[0]));
	if ( size == 0 )
		return c;
	int i = c % size;
	int d = 0;
	while ( (C[i] != c) && (C[i] != -1) ) {
		i = (int) ( (i + 2*d + 1) % size );
		d++;
	}
	
	return i;
}


int reqBkt(int c, int C[], int size) {
//	int size = (int)( sizeof(C) / sizeof(C[0]));
	if ( size == 0 )
		return c;
	int i = getBkt(c, C, size);
	int d = 0;
	
	// occupy bucket and return its position
	C[i] = c;
	return i;
}





