#include <stdio.h>
#include <math.h>
#define KAY 3

int main() {	
	int size = 4;
	char alphabet[] = {"ACGT"};
//	int KAY = 2;
	
	int i,
		x;
	char kmer[KAY+1];
	
	int total = pow(KAY, size);
	printf("total: %d\n\n", total);
	
	for(x=0; x<KAY; x++) {		
		dispLetter(alphabet, &size, x, kmer);
	}
		
	return 0;
}

void dispLetter(char alphabet[], int *size, int x, char kmer[]) {
	int i;
	for(i=0; i<*size; i++) {		
		if (KAY != x + 1) {
			kmer[x] = alphabet[i];
			dispLetter(alphabet, size, x+1, kmer);
		}
		else {
			kmer[x] = alphabet[i];
			kmer[x+1] = '\0';
			int y = 0;
//			for(; y<KAY; y++) {
//				switch (kmer[y]) {
//					case 'A': printf("1"); break;
//					case 'C': printf("2"); break;
//					case 'G': printf("3"); break;
//					case 'T': printf("4"); break;
//				}
////				printf("%c", kmer[y]);
//			}
//			printf("\t");
			printf("%s \n", kmer);
//			printf("%d \n", x);
		}
	}
}
