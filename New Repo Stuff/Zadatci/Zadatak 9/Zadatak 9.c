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


//TO DO: replace, rand, inorder fix


//Declaring binary tree structure
typedef struct tree
{
	int CurrVal;
	int OldVal;
	struct tree* left;
	struct tree* right;

} Tree;


//Declaring necessary functions
Tree* setup(Tree*);
Tree* make(int);
Tree* insert(Tree*, int);
Tree* erase(Tree*, int);
FILE* setupFile(void);
int replace(Tree*);
int inorder(Tree*);
int randN(Tree*, int);
int menu(Tree*);



int main()
{
	//Making root of tree
	Tree* root = NULL;
	root = setup(root);

	while (menu(root));

	return EXIT_SUCCESS;
}



//Defining function for setting up the tree node
Tree* setup(Tree* root)
{
	//Allocating memory and checking if successful
	root = (Tree*)malloc(sizeof(Tree));

	if (root == NULL)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}
	//If it was successful, setting up the root node
	else
	{
		printf("Enter value of root: ");
		scanf("%d", &root->CurrVal);
		root->OldVal = 0;
		root->left = NULL;
		root->right = NULL;
	}

	return root;
}

//Defining function for making a new element
Tree* make(int n)
{
	//Allocating memory and checking if successful
	Tree* newEntry = (Tree*)malloc(sizeof(Tree));

	if (newEntry == NULL)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}
	else
	{
		//Setting up new entry
		newEntry->CurrVal = n;
		newEntry->OldVal = 0;
		newEntry->left = NULL;
		newEntry->right = NULL;

		return newEntry;
	}

}

//Defining function for inserting an element
Tree* insert(Tree* root, int n)
{
	//Checking if root is NULL
	(root == NULL) ? root = make(n) : 1;

	//Checking position of value n in regards to value root->val
	(n > root->CurrVal) ? root->left = insert(root->left, n) : 1;
	(n < root->CurrVal) ? root->right = insert(root->right, n) : 1;
	(n == root->CurrVal) ? root->CurrVal = n : 1;

	return root;
}

//Defining function for removing an element
Tree* erase(Tree* root, int n)
{
	//Finding the value to delete
	(n > root->CurrVal) ? root->right = erase(root->right, n) : 1;
	(n < root->CurrVal) ? root->left = erase(root->left, n) : 1;

	if (n == root->CurrVal)
	{
		//Making a temporary storage for root to delete
		Tree* temp = root;

		//If this is a leaf, set it to NULL, free later
		if (root->left == NULL && root->right == NULL)
			root = NULL;

		//If the left is NULL in the node, set this to the right branch/leaf
		if (root->left == NULL && root->right != NULL)
			root = root->right;

		//If the right is NULL in the node, set this to the right branch/leaf
		if (root->left != NULL && root->right == NULL)
			root = root->left;

		//If there are two branches in the node, find the minimum in the right node and return it to the node
		//Then, erase the duplicate value
		if (root->left != NULL && root->right != NULL)
		{
		}

		//Free the temporary variable
		free(temp);
	}

	return root;
}

//Defining a function for summing up elements and replacing with root value
int replace(Tree* root)
{
	//Put current value into "return slot" by the name of 'OldVal'
	//Set CurrVal to 0 to remove potential conflict of values and wrong calculation
	root->OldVal = root->CurrVal;
	root->CurrVal = 0;

	//If there are left members, calculate their sum before returning it to root's current value
	if (root->left != NULL)
		root->CurrVal += replace(root->left);

	//If there are right members, calculate their sum before returning it to root's current value
	if (root->right != NULL)
		root->CurrVal += replace(root->right);

	//The return sum is the sum of children, stored in 'CurrVal' + the old value of the parent, stored in 'OldVal'
	return root->CurrVal+root->OldVal;
}

//Defining a function for setting up file pointer
FILE* setupFile(void)
{
	//Declaring pointer to file and checking if opening was successful
	FILE* fileP = fopen("InorderTree.txt", "w");

	if (fileP == NULL)
	{
		printf("Failed to open file!\n");
		return NULL;
	}
	else
		return fileP;
}

//Defining a function for printing to file in 'inorder' mode
int inorder(Tree* root, FILE* file)
{
	//Inorder pass of binary tree and writing to file
	if (root != NULL && file != NULL)
	{
		inorder(root->right, file);
		fprintf(file, "%d\n", root->CurrVal);
		inorder(root->left, file);
	}

	return EXIT_SUCCESS;
}

//Defining a function for generating 'val' numbers randomly in range (10, 90)
int randN(Tree* root, int val)
{
	//Generating space for array of 'val' numbers and making an index variable
	int* genArr = (int*)malloc(val * sizeof(int));
	int i = 0;

	//Checking if the allocation was successful
	if (genArr == NULL)
	{
		printf("Failed to make array!");
		return NULL;
	}
	//Else, generate random numbers and fill genArr with them
	for (i; i < val; i++)
	{
		genArr[i] = (int)rand(time(0)) % (90 - 10 + 1) + 10;
		root = insert(root, genArr[i]);
	}


	return EXIT_SUCCESS;
}

//Defining menu function
int menu(Tree* root)
{
	//Declaring a choice and value variable and file pointer variable
	int c = 0, val = 0;
	FILE* file = NULL;

	printf("\nList of possible options:\n");
	printf("-------------------------\n");
	printf("1 - Insert new value\n");
	printf("2 - Write inorder to file\n");
	printf("3 - Sum up and replace\n");
	printf("4 - Generate numbers and make tree\n");
	printf("5 - Exit program\n");

	printf("Which option do you choose? ");
	scanf("%d", &c);

	switch (c)
	{
	case 1:
		printf("Which value do you want to insert? ");
		scanf("%d", &val);
		root = insert(root, val);
		break;

	case 2:
		//Checking if the file opened successfully and only then writing in 'inorder'
		file = setupFile();
		(file != NULL) ? inorder(root, file), fclose(file) : 1;
		break;

	case 3:
		replace(root);
		break;

	case 4:
		printf("How many numbers would you like to generate?\n");
		printf("NOTE: the numbers will only be in range of 10 to 90: \n");
		scanf("%d", &val);
		randN(root, val);
		break;

	default:
		printf("Wrong option!\n");
		break;
	}

	return c;
}