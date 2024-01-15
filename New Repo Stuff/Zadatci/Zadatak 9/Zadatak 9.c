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
	int val;
	struct tree* left;
	struct tree* right;

} Tree;


//Declaring necessary functions
Tree* setup(Tree*);
Tree* make(int);
Tree* insert(Tree*, int);
Tree* erase(Tree*, int);
FILE* setupFile(void);
int replace(Tree*, FILE*);
int inorder(Tree*);
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
	else
	{
		printf("Enter value of root: ");
		scanf("%d", &root->val);
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
		newEntry->val = n;
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
	(n > root->val) ? root->left = insert(root->left, n) : 1;
	(n < root->val) ? root->right = insert(root->right, n) : 1;
	(n == root->val) ? root->val = n : 1;

	return root;
}

//Defining function for removing an element
Tree* erase(Tree* root, int n)
{
	//Finding the value to delete
	(n > root->val) ? root->right = erase(root->right, n) : 1;
	(n < root->val) ? root->left = erase(root->left, n) : 1;

	if (n == root->val)
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
	int LR[2] = { 0 };

	if (root == NULL)
		return 0;

	(root->right != NULL) ? replace(root->right) : 1;
	(root->left != NULL) ? replace(root->left) : 1;

	return 0;
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
		fprintf(file, "%d\n", root->val);
		inorder(root->left, file);
	}

	return EXIT_SUCCESS;
}

//Defining menu function
int menu(Tree* root)
{
	//Declaring a choice and value variable and file pointer variable
	int c, val;
	FILE* file = NULL;

	printf("\nList of possible options:\n");
	printf("-------------------------\n");
	printf("1 - Insert new value\n");
	printf("2 - Write inorder to file\n");
	printf("3 - Sum up and replace\n");
	printf("4 - Exit program\n");

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
		return 0;
		break;

	default:
		printf("Wrong option!\n");
		break;
	}

	return c;
}