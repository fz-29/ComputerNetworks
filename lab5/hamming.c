#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MESS 100
#define BITS 7
#define CODEBITS 11
void hammingCodeword(const int *msg, int *codeword)
{
	//for 7 bit message generates 11 bit codeword
	int i,j;
	for(i = 0, j = 0; i < CODEBITS; i++)
	{
		if(i != 0 && i != 1 && i!= 3 && i != 7)
			codeword[i] = msg[j++];
	}
	// even parity
	//parity bits at position 0,1,3,7
	//P0 = XOR(0,2,4,8,10)
	codeword[0] = codeword[2] ^ codeword[4] ^ codeword[6] ^ codeword[8] ^ codeword[10];
	//P1 = XOR(1,2,5,6,9,10)
	codeword[1] = codeword[2] ^ codeword[5] ^ codeword[6] ^ codeword[9] ^ codeword[10];
	//P3 = XOR(3,4,5,6)
	codeword[3] = codeword[4] ^ codeword[5] ^ codeword[6];
	//P7 = XOR(7,8,9,10)
	codeword[7] = codeword[8] ^ codeword[9] ^ codeword[10];
}
void detectAndCorrect(int *codeword)
{
	int a,b,c,d;
	d = codeword[7] ^ codeword[8] ^ codeword[9] ^ codeword[10];
	c = codeword[3] ^ codeword[4] ^ codeword[5] ^ codeword[6];
	b = codeword[1] ^ codeword[2] ^ codeword[5] ^ codeword[6] ^ codeword[9] ^ codeword[10];
	a = codeword[0] ^ codeword[2] ^ codeword[4] ^ codeword[6] ^ codeword[8] ^ codeword[10];
	int bit = a + 2 * b + 4 * c + 8 * d;
	bit--; //indexing from 1 so --
	printf("\n Error detected at : %d",bit);
	//correcting the codeword
	codeword[bit] = !codeword[bit]; 
}
int main()
{
	//freopen("input.txt","r",stdin);
	int msg[MAX_MESS]={0}, c[MAX_MESS + 10]={0},i;
	printf("\nEnter message : ");
	for(i = 0; i < BITS; i++)	scanf("%d",&msg[i]);

	//Step 1 : Generate Codeword
	hammingCodeword(msg,c);
	printf("\n Codeword is : ");
	for(i = 0; i < CODEBITS; i++) printf("%d",c[i]);

	//Step 2 : introduce random error
	int e = rand()%CODEBITS;
	printf("\n Enter error bit position : "); scanf("%d",&e);
	c[e] = !c[e];
	printf("\n Codeword with error at %d : ",e);
	for(i = 0; i < CODEBITS; i++) printf("%d",c[i]);

	//Step 3 : Detect error and correction of codeword
	detectAndCorrect(c);

	//Step 4 : Corrected codeword
	printf("\n Codeword with error at %d : ",e);
	for(i = 0; i < CODEBITS; i++) printf("%d",c[i]);
	printf("\n");
	return 0;
}