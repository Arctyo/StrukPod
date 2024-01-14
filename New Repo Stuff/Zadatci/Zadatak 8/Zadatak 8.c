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



//Declaring binary tree structure
typedef struct tree
{
	int val;
	struct tree* left;
	struct tree* right;

} Tree;


//Declaring a stack structure
typedef struct stack
{
	struct tree* entity;
	struct stack* next;

} Stack;


//Declaring necessary functions
Tree* setup(Tree*);
Tree* make(int);
Stack* makeS(Stack*);
Tree* insert(Tree*, int);
Tree* search(Tree*, int);
Tree* searchMin(Tree*);
Tree* searchMax(Tree*);
Tree* erase(Tree*, int);
int preorder(Tree*);
int inorder(Tree*);
int postorder(Tree*);
int levelorder(Tree*);
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
	(n > root->val) ? root->right = insert(root->right, n) : 1;
	(n < root->val) ? root->left = insert(root->left, n) : 1;
	(n == root->val) ? root->val = n : 1;

	return root;
}

//Defining function for searching for an element
Tree* search(Tree* root, int n)
{
	//Checking if at end of tree
	if (root == NULL)
	{
		printf("Element doesn't exist!\n");
		return NULL;
	}

	//Checking position of value n in regards to value root->val
	(n > root->val) ? root->right = search(root->right, n) : 1;
	(n < root->val) ? root->left = search(root->left, n) : 1;
	(n == root->val) ? printf("Element found!\n") : 1;

	return root;
}

//Defining function for searching minimum in tree
Tree* searchMin(Tree* root)
{
	//Find leftmost node and return it
	(root->left != NULL) ? root->left = searchMin(root->left) : 1;

	return root;
}

//Defining function for searching maximum in tree
Tree* searchMax(Tree* root)
{
	//Find rightmost node and return it
	(root->right == NULL) ? root->right = searchMax(root->right) : 1;

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
			temp = searchMin(root->right);
			root->val = temp->val;
			root->right = erase(root->val, root->right);
		}

		//Free the temporary variable
		free(temp);
	}

	return root;
}

//Defining a function for printing in 'preorder' mode
int preorder(Tree* root)
{
	if (root != NULL)
	{
		printf("%d\n", root->val);
		preorder(root->left);
		preorder(root->right);
	}

	return EXIT_SUCCESS;
}

//Defining a function for printing in 'inorder' mode
int inorder(Tree* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d\n", root->val);
		inorder(root->right);
	}

	return EXIT_SUCCESS;
}

//Defining a function for printing in 'postorder' mode
int postorder(Tree* root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d\n", root->val);
	}

	return EXIT_SUCCESS;
}

//Defining a function for making a 'stack' entry
Stack* makeS(Tree* root)
{
	//Allocating space for 'stack' entry
	Stack* Entry = (Stack*)malloc(sizeof(Stack));
	
	//Checking if allocation was successful
	if (Entry != NULL)
	{
		Entry->next = NULL;
		Entry->entity = root;
		Entry->entity->left = root->left;
		Entry->entity->right = root->right;

		return Entry;
	}
	//If not, f u message
	else
	{
		printf("Failed to allocate stack variable!");
		return EXIT_FAILURE;
	}

}

//Defining a function for printing in 'levelorder' mode
int levelorder(Stack* startStack)
{
	//Declaring a static counter variable, a 'stack' variable and setting them up
	static int onStack[2] = { 1, 0 };
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	//Checking if allocation was successful
	if (stack == NULL)
	{
		printf("Allocation failed!");
		return EXIT_FAILURE;
	}
	//Setting stack up
	else
		stack->next = startStack;

	//Setting a 'end of stack' variable up
	static Stack* EOS = NULL;
	EOS = stack->next;

	//Setting up a trash variable for freeing space
	static Stack* trash = NULL;

	//Checking if the stack is empty
	if (startStack != NULL && onStack[0] != 0)
	{
		//Updating EOS to be constantly freshly on the end of the stack
		while (EOS->next != NULL)
			EOS = EOS->next;

		//Removing onStack[0] entries from the beginning of the stack
		for (int i = 0; i < onStack[0]; i++)
		{
			//Adding entry to trash
			trash = stack->next;
			printf("%d ", trash->entity->val);

			//Checking if entry has children, if so adding them to end of stack
			if (trash->entity->left != NULL)
			{
				EOS->next = makeS(trash->entity->left);
				EOS = EOS->next;
				onStack[1]++;
			}

			if (trash->entity->right != NULL)
			{
				EOS->next = makeS(trash->entity->right);
				EOS = EOS->next;
				onStack[1]++;
			}

			//Freeing trash
			stack->next = stack->next->next;
			free(trash);
		}

		//Printing newline to indicate deeper level
		printf("\n");

		//Setting values of stack counter 
		//for proper removal of entries in next pass
		onStack[0] = onStack[1];
		onStack[1] = 0;

		//Recursive call of function for passing through tree
		levelorder(stack->next);
	}

	//Resetting counter so it can be used
	//in multiple passes of main function
	onStack[0] = 1;
	onStack[1] = 0;

	return EXIT_SUCCESS;
}

//Defining menu function
int menu(Tree* root)
{
	int c, val;

	printf("\nList of possible options:\n");
	printf("-------------------------\n");
	printf("1 - Insert new value\n");
	printf("2 - Search for a value\n");
	printf("3 - Erase a value\n");
	printf("4 - Print preorder\n");
	printf("5 - Print inorder\n");
	printf("6 - Print postorder\n");
	printf("7 - Print levelorder\n");
	printf("8 - Exit program\n");

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
		printf("Which value do you want to search for? ");
		scanf("%d", &val);
		search(root, val);
		break;
	
	case 3:
		printf("Which value do you want to delete? ");
		scanf("%d", &val);
		(search(root, val) != NULL) ? root = erase(root, val): 1;
		break;
	
	case 4:
		preorder(root);
		break;

	case 5:
		inorder(root);
		break;
	
	case 6:
		postorder(root);
		break;
		
	case 7:
		levelorder(makeS(root));
		break;
		
	case 8:
		return 0;
		break;

	default:
		printf("Wrong option!\n");
		break;
	}

	return c;
}