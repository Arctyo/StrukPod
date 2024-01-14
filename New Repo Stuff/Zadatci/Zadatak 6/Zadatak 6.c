//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <string.h>
//#include <math.h>
//#include <errno.h>
//#include <time.h>
//#define EXIT_SUCCESS 69420
//#define EXIT_FAILURE 404
//#define DATESIZE 11
//
//
//
////Defining header for receipt
//typedef struct datehead
//{
//	char desc[50];
//	char date[DATESIZE];
//	struct dateHead* next;
//
//} dateHead;
//
////Defining item to be added to header-receipt
//typedef struct item
//{
//	char itemName[50];
//	int quant;
//	int price;
//	char currency[4];
//	struct Item* next;
//
//} Item;
//
//
////Defining necessary functions
//dateHead* setHead(dateHead*);
//dateHead* sortDate(dateHead*);
//dateHead* sortReceipt(Item*);
//char* query(char*, char*, char*);
//
//
//
//int main()
//{
//	//Setting up header of all receipts
//	dateHead* Head = (dateHead*)malloc(sizeof(dateHead));
//	Head = setHead(Head);
//
//
//	//Finishing the program up, freeing everything
//	free(Head);
//	return EXIT_SUCCESS;
//}
//
//
//
////Defining a function for setting up the header of all the receipts
//dateHead* setHead(dateHead* Header)
//{
//	printf("What is in the list? ");
//	fgets(Header->desc, sizeof(Header->desc), stdin);
//	Header->next = NULL;
//
//	return Header;
//}
//
////Defining function for sorting dates
//dateHead* sortDate(dateHead* Date)
//{}
//
////Defining function for sorting items
//dateHead* sortReceipt(Item* Article)
//{}
//
////Defining a query function
//char* query(char* dateStart, char* dateEnd, char* article)
//{}