//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int g;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	g = strlen(str);
	i->n=g-1;
	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s, g + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		g++; //one extra for the + sign
	 	i->s = realloc(i->s, g + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b)
{
	int i=a->n;
	int j=b->n;
	int h=(i>=j)?(i+1):(j+1);
	int *a1=(int *)malloc(sizeof(int)*h);
	int *b1=(int *)malloc(sizeof(int)*h);
	int l;
	i=i-1;
	j=j-1;
	for(l=h-1;i>=0;i--,l--)
	{
		a1[l]=a->s[i+1]-'0';
	}
	for(l=h-1;j>=0;j--,l--)
	{
		b1[l]=b->s[j+1]-'0';
	}
	int *r=(int *)malloc(sizeof(int)*h);
	for(l=h-1;l>0;l--)
	{
		r[l]+=a1[l]+b1[l];
		if(r[l]>9)
		{
			r[l-1]+=r[l]/10;
			r[l]=r[l]%10;
		}
	}
	char ch[h+1];
	if(a->s[0]==b->s[0])
	{
		ch[0]=a->s[0];
	}
	for(l=1;l<=h;l++)
	{
		ch[l]=r[l-1]+'0';
	}
	ch[l]='\0';
	intal *res=create_intal();
	read_intal(res,ch);
	return res;
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b)
{
	int i=a->n;
	int j=b->n;
	int h=(i>=j)?(i):(j);
	int *a1=(int *)malloc(sizeof(int)*h);
	int *b1=(int *)malloc(sizeof(int)*h);
	int l;
	i=i-1;
	j=j-1;
	for(l=h-1;i>=0;i--,l--)
	{
		a1[l]=a->s[i+1]-'0';
	}
	for(l=h-1;j>=0;j--,l--)
	{
		b1[l]=b->s[j+1]-'0';
	}
	int *r=(int *)malloc(sizeof(int)*h);
	if(strcmp(a->s,b->s)<0)
		return subtract_intal(b,a);
	else
	{
		for(l=h-1;l>0;l--)
		{
			int d=a1[l]-b1[l];
			if(d<0)
			{
				r[l-1]-=1;
				r[l]+=(r[l]+10)-d;
			}
			else
			{
				r[l]+=d;
			}
		}
		r[0]=a1[0]-b1[0];
	}
	char ch[h+1];
	if(a->s[0]==b->s[0])
	{
		ch[0]=a->s[0];
	}
	else
	{
		ch[0]=(strcmp(a->s,b->s)<0)?(b->s[0]):(a->s[0]);
	}
	for(l=1;l<=h;l++)
	{
		ch[l]=r[l-1]+'0';
	}
	ch[l]='\0';
	intal *res=create_intal();
	read_intal(res,ch);
	return res;
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b)
{
	int i=a->n;
	int j=b->n;
	int h=i+j;
	int *a1=(int *)malloc(sizeof(int)*i);
	int *b1=(int *)malloc(sizeof(int)*j);
	int *r=(int *)malloc(sizeof(int)*h);
	int l,k;
	for(l=0;l<i;l++)
	{
		a1[l]=a->s[l+1]-'0';
	}
	for(l=0;l<j;l++)
	{
		b1[l]=b->s[l+1]-'0';
	}
	for(k=i;k>0;k--)
	{
		for(l=j;l>0;l--)
		{
			r[k+l-1]+=a1[k-1]*b1[l-1];
			if(r[k+l-1]>9)
				{	
					r[k+l-2]+=r[k+l-1]/10;
					r[k+l-1]=r[k+l-1]%10;
				}	
		}	
	}
	char ch[h+1];
	if(a->s[0]==b->s[0])
	{
		ch[0]='+';
	}
	else
	{
		ch[0]='-';
	}
	for(l=1;l<=h;l++)
	{
		ch[l]=r[l-1]+'0';
	}
	ch[l]='\0';
	intal *res=create_intal();
	read_intal(res,ch);
	return res;
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b)
{
	int a1=atoi(a->s);
	int b1=atoi(b->s);
	int i=a->n;
	if(a1<0)
	{
		a1=a1-(2*a1);
	}
	if(b1<0)
	{
		b1=b1-(2*b1);
	}
	char ch[i+1];
	if(a->s[0]==b->s[0])
	{
		ch[0]=a->s[0];
	}
	else
	{
		ch[0]='-';
	}
	int a3=a1/b1;
	for(i=a->n;i>1;i--)
	{
		ch[i-1]=(a3%10)+'0';
		a3=a3/10;
	}
	ch[a->n]='\0';
	intal *res=create_intal();
	read_intal(res,ch);
	return res;
	
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) 
{
	if(b->s[0]=='-')
		return NULL;
	else
	{
		intal *a1=create_intal();
		int k;
		int j=atoi(b->s);
		if(j==0)
		{	
			char c[2]={'+','1'};
			read_intal(a1,c);
		}
		else if(j==1)
			return a;
		else
		{	
			a1=multiply_intal(a,a);
			for(k=3;k<=j;k++)
			{
				a1=multiply_intal(a,a1);
			}
		}
		return a1;
	}
}
