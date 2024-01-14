#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#define EXIT_SUCCESS 69420
#define EXIT_FAILURE 404
#define MAX 1024


//Defining structure for items within bills
typedef struct item
{
	char name[MAX];
	int quant;
	int price;
	char currency[3];
	struct item* next;

} Item;


//Defining structure for bills
typedef struct bill
{
	char dateName[50];
	struct item* billItems;
	struct bill* billNext;

} Bill;


//Defining necessary functions
Bill* setHead(Bill*);
Bill* setList(Bill*);
Bill* makeBill(void);
Item* makeItem(char*);
FILE* setFile(char*);
int readBillFile(Bill*);
int readBill(Bill*);
int searchList(Bill*, char*, char*, char*);
int inquiry(Bill*);
int menu(Bill*);


int main()
{
	//Creating bill list
	Bill* Bills = NULL;
	Bills = setList(Bills);

	//Cycle menu as long as user wants to make inquiries
	while (menu(Bills));

	return EXIT_SUCCESS;
}


//Defining a function for setting up bill head
Bill* setHead(Bill* billHead)
{
	//Allocating space for the bill head
	billHead = (Bill*)malloc(sizeof(Bill));

	//Checking if allocation was successful
	if (billHead == NULL)
	{
		printf("Memory allocation failed!");
		return NULL;
	}
	//If it was successful, set up 'bills' entry
	else
	{
		billHead->billNext = NULL;
		billHead->billItems = NULL;
		strcpy_s(billHead->dateName, 50, "List of bills");
		return billHead;
	}
}

//Defining a function for making a bill
Bill* makeBill(void)
{
	//Allocating space for entry
	Bill* newEntry = (Bill*)malloc(sizeof(Bill));

	//Checking if allocation failed
	if (newEntry == NULL)
	{
		printf("Memory allocation failed!");
		return NULL;
	}
	//If it succeeded, set up entry
	else
	{
		newEntry->billItems = NULL;
		newEntry->billNext = NULL;
		return newEntry;
	}
}

//Defining a function for making an item
Item* makeItem(char* string)
{
	//Allocating space for entry
	Item* newEntry = (Item*)malloc(sizeof(Item));

	//Checking if allocation failed
	if (newEntry == NULL)
	{
		printf("Memory allocation failed!");
		return NULL;
	}
	//If it succeeded, set up entry
	else
	{
		sscanf(string, "%s %d %d %s", newEntry->name, &newEntry->quant, &newEntry->price, newEntry->currency);
		newEntry->next = NULL;
		return newEntry;
	}
}

//Defining a function for opening and checking a file
FILE* setFile(char* string)
{
	//Opening file with filename 'string'
	FILE* file = fopen(string, "r");

	//Checking if opening failed
	if (file == NULL)
	{
		printf("Failed to open file!");
		return NULL;
	}
	//If it didn't, return file pointer
	//NOTE: File will be closed later in the function which called this one.
	//Done so there aren't tedious file-opening-checks repeating all over functions
	else
		return file;
}

//Defining a function for reading the bill list file and creating a list
int readBillFile(Bill* List)
{
	//Opening the bill file, creating an entry placeholder and position variable
	FILE* BillPoint = setFile("racuni.txt");
	Bill* Entry = NULL;
	Bill* Pos = List;

	//Checking if opening failed
	if (BillPoint == NULL)
		return EXIT_FAILURE;
	//If it didn't, sorted input of all bill names
	else
		while (!feof(BillPoint))
		{
			Entry = makeBill();
			fscanf(BillPoint, "%s", Entry->dateName);

			//If list is empty, add to start
			if (List->billNext == NULL)
			{
				Entry->billNext = List->billNext;
				List->billNext = Entry;
			}

			//If list isn't empty, compare dateName and sort
			//Case #1: Entry dateName is before Pos dateName
			if (Pos->billNext != NULL && strcmp(Entry->dateName, Pos->billNext->dateName) == -1)
			{
				Entry->billNext = Pos->billNext;
				Pos->billNext = Entry;
			}
			//Case #2: Entry dateName is after Pos dateName
			if (Pos->billNext != NULL && strcmp(Entry->dateName, Pos->billNext->dateName) == 1)
			{
				while (Pos->billNext != NULL && strcmp(Entry->dateName, Pos->billNext->dateName) == 1)
					Pos = Pos->billNext;

				//Case #3: Entry dateName is exactly the same as Pos dateName
				if (Pos->billNext->dateName == Entry->dateName)
					free(Entry);

				//Case #4: End of list
				if (Pos->billNext == NULL)
				{
					Entry->billNext = Pos->billNext;
					Pos->billNext = Entry;
				}

				//Case #5: Entry dateName is between Pos and Pos->billNext dateName
				else
				{
					Entry->billNext = Pos->billNext;
					Pos->billNext = Entry;
				}
			}

			//Resetting position pointer
			Pos = List;
		}

	//Closing the file
	fclose(BillPoint);
	return EXIT_SUCCESS;
}

//Defining a function for reading bill items
int readBill(Bill* List)
{
	//Defining a file, item and position variables for Item (PosI) and Bill (PosB)
	FILE* ItemPoint = NULL;
	Item* Entry = NULL;
	Bill* PosB = List->billNext;
	Item* PosI = NULL;
	char buffer[MAX];

	while (PosB != NULL)
	{
		//Opening the corresponding bill file
		//and skipping first line due to it being a date, not an item
		ItemPoint = setFile(PosB->dateName);
		while (fgetc(ItemPoint) != '\n');

		//Reading it and making a sorted input of items
		while (!feof(ItemPoint))
			//Checking that the line isn't empty
			if (fgets(buffer, MAX, ItemPoint))
			{
				//Making an item from the article
				Entry = makeItem(buffer);

				//If list is empty, add to beginning
				if (PosB->billItems == NULL)
				{
					Entry->next = PosB->billItems;
					PosB->billItems = Entry;
					PosI = PosB->billItems;
				}

				//Case #1: Entry comes before everything in the list - add to beginning
				if (strcmp(Entry->name, PosB->billItems->name) == -1)
				{
					Entry->next = PosB->billItems;
					PosB->billItems = Entry;
				}

				//Case #2: Entry comes after the first article in the list
				if (strcmp(Entry->name, PosB->billItems->name) == 1)
				{
					//Cycle while the Entry is alphabetically after the next article
					while (PosI->next != NULL && strcmp(Entry->name, PosI->next->name) == 1)
						PosI = PosI->next;

					//Case #3: At the end of the list and Entry comes after the last article - add to end
					if (PosI->next == NULL && strcmp(Entry->name, PosI->name) == 1)
					{
						Entry->next = PosI->next;
						PosI->next = Entry;
					}

					//Case #4: Not at the end of the list, Entry comes between the current and next article - add in between
					if (PosI->next != NULL && strcmp(Entry->name, PosI->next->name) == -1)
					{
						Entry->next = PosI->next;
						PosI->next = Entry;
					}
				}
				
			}
			
		//Closing the current bill and moving on to next
		//but appending item position only if the next bill isn't NULL
		fclose(ItemPoint);
		PosB = PosB->billNext;
		if (PosB != NULL)
			PosI = PosB->billItems;
	}

	return EXIT_SUCCESS;
}

//Defining a function for creating a bill list
Bill* setList(Bill* bills)
{
	//Setting up bill head
	bills = setHead(bills);

	//Sorted input of bill names
	readBillFile(bills);

	//Sorted input of bill items
	readBill(bills);

	return bills;
}

//Defining a function for searching the list
int searchList(Bill* bills, char* start, char* end, char* article)
{
	//Creating a 'data' array in the format [quantity, price]
	//Creating position variables for bills and items
	int data[2] = { 0 };
	Bill* posB = bills->billNext;
	Item* posI = posB->billItems;
	Bill* StartInt = NULL;
	Bill* EndInt = NULL;
	
	//Adapting strings to list
	strcat(start, ".txt");
	strcat(end, ".txt");

	//Searching start date
	while (posB != NULL)
	{
		if (strcmp(start, posB->dateName) == 0)
		{
			StartInt = posB;
			break;
		}
		else
			posB = posB->billNext;
	}

	//Searching end date
	posB = bills->billNext;
	while (posB != NULL)
	{
		if (strcmp(end, posB->dateName) == 0)
		{
			EndInt = posB;
			break;
		}
		else
			posB = posB->billNext;
	}

	//Case #1: Start date doesn't exist, but the end does
	if (StartInt == NULL && EndInt != NULL)
	{
		//Setting bill position variable to start of list
		posB = bills->billNext;
		while (posB != EndInt->billNext)
		{
			while (posI != NULL)
			{
				//Checking if the item is found
				if (strcmp(posI->name, article) == 0)
				{
					data[0] += posI->quant;
					data[1] += posI->price;
				}

				//Updating item position variable
				posI = posI->next;
			}

			//Updating bill position variable and resetting the item position variable
			posB = posB->billNext;
			if (posB != NULL)
				posI = posB->billItems;
		}
	}

	//Case #2: Start date exists, but the end doesn't
	if (StartInt != NULL && EndInt == NULL)
	{
		//Setting the bill position variable to the start and updating the item position variable
		posB = StartInt;
		posI = posB->billItems;
		while (posB != NULL)
		{
			while (posI != NULL)
			{
				//Checking if the item is found
				if (strcmp(posI->name, article) == 0)
				{
					data[0] += posI->quant;
					data[1] += posI->price;
				}

				//Updating item position variable
				posI = posI->next;
			}

			//Updating bill position variable and resetting the item position variable
			posB = posB->billNext;
			if (posB != NULL)
				posI = posB->billItems;
		}
	}

	//Case #3: Both dates exist
	if (StartInt != NULL && EndInt != NULL)
	{
		posB = StartInt;
		posI = posB->billItems;
		while (posB != EndInt->billNext)
		{
			while (posI != NULL)
			{
				//Checking if the item is found
				if (strcmp(posI->name, article) == 0)
				{
					data[0] += posI->quant;
					data[1] += posI->price;
				}

				//Updating item position variable
				posI = posI->next;
			}

			//Updating bill position variable and resetting the item position variable
			posB = posB->billNext;
			if (posB != NULL)
				posI = posB->billItems;
		}
	}

	//Case #4: Neither date exists
	if (StartInt == NULL && EndInt == NULL)
	{
		//Cycling entire bill list
		while (posB != NULL)
		{
			//Cycling entire item list
			while (posI != NULL)
			{
				//Checking if the item is found
				if (strcmp(posI->name, article) == 0)
				{
					data[0] += posI->quant;
					data[1] += posI->price;
				}

				//Updating item position variable
				posI = posI->next;
			}

			posB = posB->billNext;
			if (posB != NULL)
				posI = posB->billItems;
		}
	}

	//Checking if the article exists
	if (data[0] != 0)
	{
		//Fixing start and end strings
		start[10] = '\0';
		end[10] = '\0';

		//Printing the info to the user
		printf("The article '%s' exists in the list!\nThe period to search was:\nStart date: %s\nEnd date: %s\n", article, start, end);
		printf("In that period, you bought a total of %d articles, with a total price of %d EUR\n\n", data[0], data[1]);
	}
	//If it doesn't, say so
	else
		printf("The article '%s' does not exist in the list!\n\n", article);

	return EXIT_SUCCESS;
}

//Defining a function for making an inquiry into bill list
int inquiry(Bill* bills)
{
	char dates[2][50] = { 0 };
	char article[50] = { 0 };
	
	while (1)
	{
		printf("Enter start and end date in format YYYY-MM-DD:\n");
		scanf("%s", dates + 0);
		scanf("%s", dates + 1);
		char temp[50] = { 0 };

		//Check if the month values are correct
		if (dates[0][5] > '1' || dates[1][5] > '1')
			printf("Invalid month values!\n");

		//Check if the day values are correct
		if (dates[0][8] > '3' || dates[1][8] > '3')
		{
			//If not, skip over the rest of the code into the next iteration
			//NOTE: Placed continue here and not under month because of possible multiple errors
			printf("Invalid day values!\n");
			continue;
		}

		//Case #1: The same date is entered twice
		if (strcmp(dates[0], dates[1]) == 0)
		{
			//If yes, skipping into next iteration
			printf("You entered the same dates!\n");
			continue;
		}

		//Case #2: The interval of dates is inverted
		if (strcmp(dates[0], dates[1]) == 1)
		{
			//Invert the inverted interval and break
			strcpy(temp, dates[0]);
			strcpy(dates[0], dates[1]);
			strcpy(dates[1], temp); 
		}

		//Case #3: All the dates are entered correctly - ask for article
		if (strcmp(dates[0], dates[1]) == -1)
		{
			printf("Which article do you wanna search for? ");
			scanf("%s", article);
			break;
		}
	}

	//Searching the list for the article
	searchList(bills, dates + 0, dates + 1, article);

	return EXIT_SUCCESS;
}

//Defining a menu function
int menu(Bill* billList)
{
	int c;
	printf("Do you want to make an inquiry? (1-yes, 0-no) ");
	scanf("%d", &c);

	if (c == 0)
		return 0;
	else
	{
		inquiry(billList);
		return EXIT_SUCCESS;
	}
}



