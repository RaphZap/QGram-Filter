#include <stdio.h>
#include <string.h>
#define KAY 2

int main() {	
	int size = 4;
	char s[] = {"GATATATGCATATACTT"};
	char t[KAY];
//	int KAY = 2;
	
	int i,
		x;
	char kmer[KAY];
//	printf("strlen: %d\n", strlen(s));
	
	for(i=0; i<strlen(s) - KAY; i++){
		int temp = i;
		for(x=0; x<KAY; x++) {
			t[x] = s[temp];
			temp++;
			// check for duplicates?	
//			if (strcmp(s,t)) {
//				
//			}	
		}
		for(x=0; x<KAY; x++) 
			printf("%c", t[x]);
		printf("\n");
	}
		
		
	return 0;
}
