
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct node_;
typedef struct node_* pos;
typedef struct node_ {
    int value;
    pos left;
    pos right;
} node;

pos add_node(int value);
pos insert(pos root, int value);
int in_o(pos root);
int pre_o(pos root);
int post_o(pos root);
int level_o(pos root);
pos search(pos root, int value);
pos delete_node(pos root, int value);
int replace(pos root);
int random();

/*int root_value = 0;
printf("Enter root value: ");
scanf(" %d", &root_value);
root = insert(root, root_value);*/

int main() {
    pos root = NULL;
    pos root_r = NULL;
    srand(time(0));



    root = insert(root, 2);
    insert(root, 5);
    insert(root, 7);
    insert(root, 8);
    insert(root, 11);
    insert(root, 1);
    insert(root, 4);
    insert(root, 2);
    insert(root, 3);
    insert(root, 7);

    level_o(root);
    replace(root);
    puts("\n");
    in_o(root);

    root_r = insert(root_r, random());
    for (int i = 0; i < 10; i++) {
        insert(root_r, random());
    }

    puts("\n");
    in_o(root_r);

    return EXIT_SUCCESS;
}

/*while (1) {
    printf("\nMenu:\n");
    printf("1 - Insert node\n");
    printf("2 - Search node\n");
    printf("3 - Delete node\n");
    printf("4 - Print preorder\n");
    printf("5 - Print inorder\n");
    printf("6 - Print postorder\n");
    printf("7 - Print level order\n");
    printf("8 - exit\n");

    char choice[10] = { 0 };
    printf("Enter your choice: ");
    scanf(" %s", choice);

    if (strcmp(choice, "1") == 0) {
        int value = 0;
        puts("Enter value: ");
        scanf(" %d", &value);
        insert(root, value);
    }
    else if (strcmp(choice, "2") == 0) {
        int value = 0;
        pos result = NULL;
        puts("Enter value: ");
        scanf(" %d", &value);
        result = search(root, value);
        if (!result)
            printf("Node %d found\n", value);
        else
            printf("Node %d not found\n", value);
    }
    else if (strcmp(choice, "3") == 0) {
        int value = 0;
        puts("Enter value: ");
        scanf(" %d", &value);
        delete_node(root, value);
    }
    else if (strcmp(choice, "4") == 0) {
        puts("Preorder: ");
        pre_o(root);
    }
    else if (strcmp(choice, "5") == 0) {
        puts("Inorder: ");
        in_o(root);
    }
    else if (strcmp(choice, "6") == 0) {
        puts("Postorder: ");
        post_o(root);
    }
    else if (strcmp(choice, "7") == 0) {
        puts("Levelorder:");
        level_o(root);
    }
    else if (strcmp(choice, "8") == 0) {
        puts("Exiting\n");
        break;
    }
    else {
        puts("Invalid choice\n");
    }
}*/


int random() {
    return (rand()%(80 + 1)) + 10;
}

int replace(pos root) {
    if (!root) {
        return 0;
    }

    int left_value = replace(root->left);
    int right_value = replace(root->right);

    int original_value = root->value;
    root->value = left_value + right_value;

    return original_value + root->value;
}
pos insert(pos root, int value) {
    if (!root)
        return add_node(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

pos add_node(int value) {
    pos new_node = (pos)malloc(sizeof(node));
    if (!new_node) {
        printf("!new_node\n");
        return NULL;
    }
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

pos insert(pos root, int value) {
    if (!root)
        return add_node(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int in_o(pos root) {
    if (root) {
        in_o(root->left);
        printf("%d ", root->value);
        in_o(root->right);
    }
    return EXIT_SUCCESS;
}

int pre_o(pos root) {
    if (root) {
        printf("%d ", root->value);
        pre_o(root->left);
        pre_o(root->right);
    }
    return EXIT_SUCCESS;
}

int post_o(pos root) {
    if (root) {
        post_o(root->left);
        post_o(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int level_o(pos root) {
    if (!root)
        return;

    pos queue[100] = { 0 };
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        pos current = queue[front++];
        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}

pos search(pos root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

pos delete_node(pos root, int value) {
    if (!root)
        return root;

    if (value < root->value)
        root->left = delete_node(root->left, value);
    else if (value > root->value)
        root->right = delete_node(root->right, value);
    else {

        if (root->left == NULL) {
            pos temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            pos temp = root->left;
            free(root);
            return temp;
        }

        pos temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->value = temp->value;
        root->right = delete_node(root->right, temp->value);
    }

    return root;
}


























































/*#define _CRT_SECURE_NO_WARNINGS
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


//Declaring necessary functions
Tree* setup(Tree*);
Tree* make(int);
Tree* insert(Tree*, int);
Tree* search(Tree*, int);
Tree* searchMin(Tree*);
Tree* searchMax(Tree*);
Tree* erase(Tree*, int);
int preorder(Tree*);
int inorder(Tree*);
int postorder(Tree*);
//int levelorder(Tree*);
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
		/*
	case 7:
		levelorder(S);
		break;
		*
	case 8:
		return 0;
		break;

	default:
		printf("Wrong option!\n");
		break;
	}

	return c;
}*/