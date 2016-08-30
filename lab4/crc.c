#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_GEN 20
#define MAX_MESS 100

void rem(const char *i, const char *g, char *r) // r = (i<<redundant) % g
{
	int k,j;
	int r_len = strlen(g) - 1; //redundant bits
	int i_len = strlen(i);
	strcpy(r,i);

	//left shift message by redundant bit amount
	//redundant bit amount = highest power of g = no. of bits in g - 1

	for(k = i_len; k < i_len + r_len; k++) r[k] = '0';
	r[k] = '\0'; //terminate string with NULL char

	//remainder with padding length + message length
	int rem_len = strlen(r);
	//subtraction
	for(k = 0; k < rem_len - r_len; k++)
	{
		if(r[k] != '0')
		{
			for(j = 0; j <= r_len; j++)
				r[k+j] = (r[k+j]-'0')^(g[j]-'0') + '0';
		}
	}
}
void subtract(char *c, char *r) // c = c - r
{
	if(strlen(c) != strlen(r))
	{
		printf("ERROR - length mismatch in subtract func.\n");
		exit(0);
	}
	int k = 0;
	int l = strlen(c);
	for(k = 0; k < l; k++)
		c[k] = ((c[k] - '0')^(r[k] - '0'))+'0';
}

int main()
{
	//freopen("input.txt","r",stdin);
	char g[MAX_GEN], i[MAX_MESS], c[MAX_MESS], r[MAX_MESS];
	printf("\nEnter generator : ");
	scanf("%s",g);
	
	printf("\nEnter message : ");
	scanf("%s",i);

	int k,j;
	int r_len = strlen(g) - 1;
	int i_len = strlen(i);

	//1.find i % g
	rem(i,g,r);
	printf("\nCRC remainder : %s",r);

	//2.remove remainder from message to obtain CRC
	
	//copy i into c and pad 0
	strcpy(c,i); for(k = i_len; k < i_len + r_len; k++) c[k] = '0'; c[k] = '\0';
	// CRC = c - r;
	subtract(c,r);
	
	printf("\nCRC message : %s",c);
	//c is the CRC message for transmission and is a valid codeword

	//3. show that the CRC leaves remainder of 0 with g
	rem(c,g,r);
	printf("\nCRC remainder :%s\n",r);
	return 0;
}