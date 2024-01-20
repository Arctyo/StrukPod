#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#define EXIT_SUCCESS 420
#define EXIT_FAILURE 404
#define MAX 100


//Declaring structure 'City'
typedef struct city
{
	char name[MAX];
	int numPPL;
	struct city* nextC;

} City;


//Declaring structure 'State'
typedef struct state
{
	char name[MAX];
	struct state* nextS;
	City* cityItem;

} State;


//Declaring necessary functions
State* setState(char*);
City* setCity(char*);
FILE* setFile(char*);
State* sortName(State*);
City* sortName(City*);
City* sortNumPPL(City*);
int setList(State*);
int printData(State*);


int main()
{


	return EXIT_SUCCESS;
}