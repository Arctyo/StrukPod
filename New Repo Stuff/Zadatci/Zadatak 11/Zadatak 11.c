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


//TODO: Fix file reading yet again REEEEEEEEEEEEEE


//Declaring structure 'City'
typedef struct city
{
	char name[MAX];
	int numPPL;
	struct city* nextC;

} City;


//Declaring structure 'Country'
typedef struct country
{
	char name[MAX];
	struct country* nextCo;
	City* cityItem;

} Country;


//Declaring necessary functions
Country* setHash(void);
int getHash(char*);
Country* setHashList(Country*);
Country* setCountry(char*);
City* setCity(char*);
FILE* setFile(char*);
Country* sortCi(Country*);
int printData(Country*);
int searchList(Country*);


int main()
{
	//Creating hash table
	Country* Hash = setHash();

	//Setting up the hash table
	Hash = setHashList(Hash);

	//Printing the hash table
	printData(Hash);

	//Searching the hash table
	searchList(Hash);

	return EXIT_SUCCESS;
}



//Defining a function for setting 'country' entry
Country* setCountry(char* str)
{
	//Allocating memory for country and checking if it was successful
	Country* Entry = (Country*)malloc(sizeof(Country));

	//If it didn't return NULL
	if (Entry == NULL)
	{
		printf("Failed to allocate country!");
		return NULL;
	}
	//Else, set up the country
	else
	{
		strcpy_s(Entry->name, MAX, str);
		Entry->cityItem = NULL;
		Entry->nextCo = NULL;

		return Entry;
	}
}

//Defining a function for setting 'City' entry
City* setCity(char* str)
{
	//Allocating memory for country and checking if it was successful
	City* Entry = (City*)malloc(sizeof(City));

	//If it didn't return NULL
	if (Entry == NULL)
	{
		printf("Failed to allocate country!");
		return NULL;
	}
	//Else, set up the country
	else
	{
		sscanf(str, "%s %d", Entry->name, &Entry->numPPL);
		Entry->nextC = NULL;
		return Entry;
	}
}

//Defining a function for readying a file
FILE* setFile(char* name)
{
	//Opening file and checking if successful
	FILE* file = fopen(name, "r");

	if (!file)
	{
		printf("Failed to open file!");
		return NULL;
	}
	else
		return file;
}

//Defining a function for sorted input of cities
Country* sortCi(Country* header)
{
	//Defining file variable for cities files.
	//Defining an 'Entry' variable for storing new read city
	//as well as position variables for tracking position in list, both for cities and countries
	FILE* cities = NULL;
	char bufferCo[MAX] = { 0 };
	char bufferCi[MAX] = { 0 };
	City* Entry = NULL;
	City* posCi = header->cityItem;

	//Concatenating two strings to create filenames
	strcat(bufferCo, header->name);
	strcat(bufferCo, "C.txt");

	//Opening corresponding country file and reading it with sorted input
	//Skipping first line of file, header
	cities = setFile(bufferCo);
	while (fgetc(cities) != '\n');
	while (!feof(cities))
	{
		//Get data for cities and create an entry
		fgets(bufferCi, sizeof(bufferCi), cities);
		Entry = setCity(bufferCi);

		//If the list isn't empty, check which criteria applies
		if (header->cityItem != NULL)
		{
			//Numbers criteria: #1-Add to beginning, #2-Add somewhere in between
			//Names criteria: #1-Add before, #2-Add after, #3-NULL

			//Case #Nu1: Add to beginning
			if (header->cityItem->numPPL < Entry->numPPL)
			{
				Entry->nextC = header->cityItem;
				header->cityItem = Entry;
			}

			//Case #Nu2: Add in between
			if (header->cityItem->numPPL > Entry->numPPL)
			{
				//Finding where to insert
				for (posCi; posCi->nextC != NULL && posCi->nextC->numPPL > Entry->numPPL; posCi = posCi->nextC);

				//Ideally, adding in between
				if (posCi->nextC != NULL && posCi->nextC->numPPL < Entry->numPPL)
				{
					Entry->nextC = posCi->nextC;
					posCi->nextC = Entry;
				}

				//If posCi->nextC is NULL
				if (posCi->nextC == NULL && posCi->numPPL > Entry)
					posCi->nextC = Entry;
			}

			//Case #Na1: Add before
			if (posCi->nextC != NULL && posCi->nextC->numPPL == Entry->numPPL && strcmp(Entry->name, posCi->nextC->name) == -1)
			{
				Entry->nextC = posCi->nextC;
				posCi->nextC = Entry;
			}

			//Case #Na2: Add after
			if (posCi->nextC != NULL && posCi->nextC->numPPL == Entry->numPPL && strcmp(Entry->name, posCi->nextC->name) == 1)
			{
				//Finding position to insert by name
				for (posCi; posCi->nextC != NULL && posCi->nextC->numPPL == Entry->numPPL && strcmp(Entry->name, posCi->nextC->name) == 1; posCi = posCi->nextC);
				
				//Entry->name before posCi->nextC->name
				if (posCi->nextC != NULL && posCi->nextC->numPPL == Entry->numPPL && strcmp(Entry->name, posCi->nextC->name) == -1)
				{
					Entry->nextC = posCi->nextC;
					posCi->nextC = Entry;
				}

				//posCi->nextC is NULL
				if (posCi->nextC != NULL && posCi->nextC->numPPL == Entry->numPPL && strcmp(Entry->name, posCi->name) == 1)
					posCi->nextC = Entry;
			}

			//Case #Na3: NULL
			if (posCi->nextC == NULL && strcmp(Entry->name, posCi) == 1)
				posCi->nextC = Entry;
		}

		//If the list is empty, add to beginning and update posCi pointer
		if (header->cityItem == NULL)
		{
			header->cityItem = Entry;
			posCi = header->cityItem;
		}

		//Reset pointer to start
		posCi = header->cityItem;
	}

	//Closing current file and updating positions of pointers, only if valid
	fclose(cities);

	return header;
}

//Defining a function for setting up the hash table
Country* setHash()
{
	//Making hash table and checking if allocation was successful
	Country* Hash = (Country*)malloc(11 * sizeof(Country));
	int i = 0;

	if (Hash == NULL)
	{
		printf("Allocation of hash failed!");
		return NULL;
	}
	//Else, setting table up
	else
	{
		for (i; i < 11; i++)
			Hash[i].nextCo = NULL;

		return Hash;
	}
}

//Defining a function for calculating the hash function
int getHash(char* name)
{
	int sum = 0, i;

	for (i = 0; i < 5; i++)
		sum += name[i];

	return sum % 11;
}

//Defining a function for setting up the hash list
Country* setHashList(Country* list)
{
	//Defining a variable for the hash function, a pointer for the read country
	//and a pointer for cycling the hash-position list, a file pointer to open countries file
	//and lastly a buffer for reading lines
	int i = 0;
	Country* Entry = NULL;
	Country* posCo = NULL;
	FILE* countries = setFile("drzave.txt");
	char buffer[MAX] = { 0 };

	//Skipping first line, header
	while (fgetc(countries) != '\n');
	while (!feof(countries))
	{
		//Reading line from file only if it isn't a filename
		fscanf(countries, "%s", buffer);
		if (buffer[strlen(buffer) - 4] != '.')
		{
			//Creating entry with country name, currently in buffer and getting hash value
			Entry = setCountry(buffer);
			Entry = sortCi(Entry);
			i = getHash(Entry->name);

			//Check if list isn't empty on the hash key position
			if (list[i].nextCo != NULL)
			{
				//Cycle through the list to find position for Entry
				for (posCo = list+i; posCo->nextCo != NULL && strcmp(Entry->name, posCo->nextCo->name) == 1; posCo = posCo->nextCo);

				//Case #1: Entry name is before posCo->nextCo->name
				if (posCo->nextCo != NULL && strcmp(Entry->name, posCo->nextCo->name) == -1)
				{
					Entry->nextCo = posCo->nextCo;
					posCo->nextCo = Entry;
				}

				//Case #2: posCo->nextCo is NULL and Entry->name is later than posCo->name
				if (posCo->nextCo == NULL && strcmp(Entry->name, posCo->name) == 1)
					posCo->nextCo = Entry;
			}

			//If list is empty on hash key position, add to start
			if (list[i].nextCo == NULL)
				list[i].nextCo = Entry;

		}
	}

	//Closing file
	fclose(countries);
	
	return list;
}

//Defining a function for formatted printing
int printData(Country* HashList)
{
	//Making a position variable for the list of countries and int variable for HashList
	Country* posCo = NULL;
	int i = 0;

	//Cycling through HasList and printing in formatted way
	for (i = 0; i < 11; i++)
	{
		printf("[  ]");
		if (HashList[i].nextCo != NULL)
			for (posCo = HashList[i].nextCo; posCo != NULL; posCo = posCo->nextCo)
				printf("->%s", posCo->name);
		printf("\n");
	}
	return EXIT_SUCCESS;
}

//Defining a function for searching the list
int searchList(Country* HashList)
{
	//Defining a buffer for country name, variable for number of people and position variables
	//for cities and states, along with an int to cycle HashList by. Then, initializing all of them 
	char buffer[MAX] = { 0 };
	int n = 0, i = 0;
	Country* posCo = NULL;
	City* posCi = NULL;

	printf("Which country do you want to search in? ");
	scanf("%s", buffer);
	printf("Which number of people is the lower limit to print by? ");
	scanf("%d", &n);

	//Searching the HashList for the name
	i = getHash(buffer);
	posCo = HashList[i].nextCo;
	if (posCo->nextCo != NULL)
		posCi = posCo->cityItem;

	for (posCo; posCo != NULL && strcmp(buffer, posCo->name) != 0; posCo = posCo->nextCo);

	//Check if country is found
	if (posCo == NULL)
		printf("Country doesn't exist in list!");
	//If found, print data
	else
	{
		printf("\nChosen country is: %s\n", buffer);
		printf("--------------------------------\n");
		printf("Cities which satisfy the criteria of minimum %d inhabitants are:\n", n);
		for (posCi; posCi != NULL && posCi->numPPL >= n; posCi = posCi->nextC)
			printf("City : %s\nNumber of inhabitants : %d\n\n", posCi->name, posCi->numPPL);
	}

	return EXIT_SUCCESS;
}