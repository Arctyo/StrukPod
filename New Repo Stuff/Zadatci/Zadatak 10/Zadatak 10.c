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


//Declaring structure 'Country'
typedef struct country
{
	char name[MAX];
	struct country* nextCo;
	City* cityItem;

} Country;


//Declaring structure 'Tree'
typedef struct tree
{
	char name[MAX];
	City* cities;
	struct tree* left;
	struct tree* right;

} Tree;


//Declaring necessary functions
Country* setCountry(char*);
City* setCity(char*);
FILE* setFile(char*);
Country* sortNameCo(Country*);
Country* sortCi(Country*);
int printData(Country*);
int searchList(Country*);

Tree* setRoot(Country*);
Tree* makeKnot(Country*);
Tree* insertKnot(Tree*, Country*);
Tree* makeTree(Country*, Tree*);
int inorder(Tree* root);


int main()
{
	//Creating a country head to hold the list
	Country* countryHead = setCountry("List of countries");

	//Setting up the 'countries' part of the list
	countryHead = sortNameCo(countryHead);

	//Setting up the 'cities' part of the list
	countryHead = sortCi(countryHead);

	//Printing the list
	printData(countryHead);

	//Searching the list
	searchList(countryHead);



	//Setting the tree root up
	Tree* root = setRoot(countryHead);

	//Making the tree
	root = makeTree(countryHead->nextCo, root);

	//Printing the tree in inorder
	inorder(root);

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

//Defining a function for sorted input of countries
Country* sortNameCo(Country* header)
{
	//Defining a file variable for opening countries file
	//and an 'Entry' variable for storing new read country
	//as well as 'pos' variable for tracking position in list
	FILE* countries = setFile("drzave.txt");
	char buffer[MAX] = { 0 };
	Country* Entry = NULL;
	Country* pos = header;

	//Checking if countries failed to open
	if (countries == NULL)
	{
		printf("Failed to open file!");
		return header;
	}
	else
	{
		//Skipping first line of file, header
		//Then, reading the rest
		while (fgetc(countries) != '\n');
		while (!feof(countries))
		{
			fscanf(countries, "%s", buffer);
			if (buffer[strlen(buffer) - 4] != '.')
			{
				Entry = setCountry(buffer);

				//Case #1: List is empty
				if (header->nextCo == NULL)
					header->nextCo = Entry;

				//Case #2: List isn't empty
				if (header->nextCo != NULL)
				{
					//Moving Entry until proper place found
					for (pos; pos->nextCo != NULL && strcmp(Entry->name, pos->nextCo->name) == 1; pos = pos->nextCo);

					//Case #2-1: At end of list
					if (pos->nextCo == NULL && strcmp(Entry->name, pos->name) == 1)
						pos->nextCo = Entry;

					//Case #2-2: Next position's name is after Entry's
					if (pos->nextCo != NULL && strcmp(Entry->name, pos->nextCo->name) == -1)
					{
						Entry->nextCo = pos->nextCo;
						pos->nextCo = Entry;
					}

					//Update position
					pos = header;
				}
			}
		}
	}

	//Closing file and returning sorted list
	fclose(countries);
	return header;
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
	Country* posCo = header->nextCo;
	City* posCi = posCo->cityItem;


	while (posCo != NULL)
	{
		//Concatenating two strings to create filenames
		strcat(bufferCo, posCo->name);
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
			if (posCo->cityItem != NULL)
			{
				//Numbers criteria: #1-Add to beginning, #2-Add somewhere in between
				//Names criteria: #1-Add before, #2-Add after, #3-NULL

				//Case #Nu1: Add to beginning
				if (posCo->cityItem->numPPL < Entry->numPPL)
				{
					Entry->nextC = posCo->cityItem;
					posCo->cityItem = Entry;
				}

				//Case #Nu2: Add in between
				if (posCo->cityItem->numPPL > Entry->numPPL)
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
					Entry->nextC = posCi->nextC->nextC;
					posCi->nextC->nextC = Entry;
				}

				//Case #Na3: NULL
				if (posCi->nextC == NULL && strcmp(Entry->name, posCi) == 1)
					posCi->nextC = Entry;
			}

			//If the list is empty, add to beginning and update posCi pointer
			if (posCo->cityItem == NULL)
			{
				posCo->cityItem = Entry;
				posCi = posCo->cityItem;
			}

			//Reset pointer to start
			posCi = posCo->cityItem;
		}

		//Closing current file and updating positions of pointers, only if valid
		fclose(cities);
		posCo = posCo->nextCo;
		if (posCo != NULL)
			posCi = posCo->cityItem;
		memset(bufferCo, 0, sizeof(bufferCo));
	}

	return header;
}

//Defining a function for formatted printing
int printData(Country* country)
{
	//Declaring position variables for cities and countries
	Country* posCo = country->nextCo;
	City* posCi = posCo->cityItem;

	printf("%s\n", country->name);
	printf("------------------\n");

	//Printing the data structure
	for (posCo; posCo != NULL; posCo = posCo->nextCo)
	{
		//First, the name of the country
		printf("%s\n", posCo->name);
		printf("------------------\n");

		//Then, the cities and their data
		for (posCi; posCi != NULL; posCi = posCi->nextC)
			printf("City name: %s\nNumber of inhabitants: %d\n\n", posCi->name, posCi->numPPL);

		//Lastly, moving on and resetting pointers if valid
		//printf("---------------------\n");
		if (posCo->nextCo != NULL)
			posCi = posCo->nextCo->cityItem;

	}
	return EXIT_SUCCESS;
}

//Defining a function for searching the list
int searchList(Country* country)
{
	//Defining a buffer for country name, variable for number of people and position variables
	//for cities and states. Then, initializing all of them 
	char buffer[MAX] = { 0 };
	int n = 0;
	Country* posCo = country->nextCo;
	City* posCi = posCo->cityItem;

	printf("Which country do you want to search in? ");
	scanf("%s", buffer);
	printf("Which number of people is the lower limit to print by? ");
	scanf("%d", &n);

	//Searching by country
	for(posCo; posCo != NULL && strcmp(buffer, posCo->name) != 0; posCo = posCo->nextCo);

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



//Defining a function for setting up the root
Tree* setRoot(Country* headList)
{
	//Allocating space for root and checking if it was successful
	Tree* root = (Tree*)malloc(sizeof(Tree));

	if (root == NULL)
	{
		printf("Failed to make root of tree!");
		return NULL;
	}

	//If it was successful, set root up
	else
	{
		strcpy_s(root->name, sizeof(root->name), headList->nextCo->name);
		root->cities = headList->nextCo->cityItem;
		root->left = NULL;
		root->right = NULL;

		return root;
	}
}

//Defining a function for setting up a knot of the tree
Tree* makeKnot(Country* Entry)
{
	//Allocating space for root and checking if it was successful
	Tree* Knot = (Tree*)malloc(sizeof(Tree));

	if (Knot == NULL)
	{
		printf("Failed to make root of tree!");
		return NULL;
	}

	//If it was successful, set root up
	else
	{
		strcpy_s(Knot->name, sizeof(Knot->name), Entry->name);
		Knot->cities = Entry->cityItem;
		Knot->left = NULL;
		Knot->right = NULL;

		return Knot;
	}
}

//Defining a function for inserting knot
Tree* insertKnot(Tree* root, Country* entry)
{
	//Checking if root is NULL
	(root == NULL) ? root = makeKnot(entry) : 1;

	//Checking position of entry in regards to root->name
	(strcmp(entry->name, root->name) == -1) ? root->right = insertKnot(root->right, entry) : 1;
	(strcmp(entry->name, root->name) == 1) ? root->left = insertKnot(root->left, entry) : 1;

	return root;
}

//Defining a function for making the tree
Tree* makeTree(Country* headList, Tree* root)
{
	//Declaring a position variable to cycle the list with
	Country* posCo = headList->nextCo;

	for (posCo; posCo != NULL; posCo = posCo->nextCo)
		insertKnot(root, posCo);

	return root;
}

//Defining a function for printing in 'inorder' mode
int inorder(Tree* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%s\n", root->name);
		inorder(root->right);
	}

	return EXIT_SUCCESS;
}