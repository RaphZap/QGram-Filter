#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SIZE 100

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


int main() {
	char alphabet[] = {"ACGT"};
	char s[] = {"-TCCGAAAC---"};
	char t[] = {"ATGC-ATGCCGG"};	
	int s_size = 12,
		t_size = 12;
//	int s_size, t_size;
	int i = 0;
	char letter;
//	for (letter=s[i] ; letter!='\0'; i++) {
//		letter = s[i];
//	}
//	s_size = i + 1;
//	i = 0;
//	for (letter=t[i] ; letter!='\0'; i++) {
//		letter = t[i];
//	}
//	t_size = i + 1;

	
//	char s[SIZE];
//	char t[SIZE];
	
//	printf("Input s: ");
//	scanf("%s",s);		
//	printf("Input t: ");
//	scanf("%s",t);	
	printf("s = %s\n", s);
	printf("t = %s\n", t);
	
//	printf("s_size = %d\n", s_size);
//	printf("t_size = %d\n", t_size);
	
	
	// assume insert/delete/mismatch	
	// insert: recur for m and n-1
	// delete: recur for m-1 and n
	// modify: recur for m-1 and n-1
	int dp[s_size+1][t_size+1];
	int j;
	for(i=0; i<=s_size; i++) {
		for(j=0; j<=t_size; j++) {
			if (i == 0) {
				dp[i][j] = j;
			}
			else if (j == 0) {
				dp[i][j] = i;
			}
			else if (s[i-1] == t[j-1]) { 
				dp[i][j] = dp[i-1][j-1];
			}
			else {
				dp[i][j] = 1 + min(dp[i][j-1], 
									min(dp[i-1][j], dp[i-1][j-1]));
			}
		}
	}	
	// return dp[m][n]		
	printf("\ndp[m][n]: %d \n", dp[s_size][t_size]);
	
	// DEBUGGING Matsrix
//
//	printf("| @ | - ");
//	for(i=0; i<s_size; i++) 
//		printf("| %c ",s[i]);
//	printf("\n");
//	for(i=0; i<=s_size; i++) {
//		for(j=0; j<=t_size; j++) {	
//			if (j==0)
//				printf("| %c ",t[i-1]);		
//			printf("| %d ",dp[i][j]);
//		}
//			printf("\n");
//	}
	
	return 0;
}
