#define _CRT_SECURE_NO_WARNINGS
#define C_LEN (30)
#define c_LEN (30)
#define uf_LEN (30)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
//struct node_;
//typedef struct node_* n_pos;
//typedef struct node_
//{
//	char name[c_LEN];
//	int br_stan;
//	n_pos left;
//	n_pos right;
//
//}node;
//
//struct countries_;
//typedef struct countries_* c_pos;
//typedef struct countries_
//{
//	char name[C_LEN];
//	c_pos c_next;
//	node n_head;
//
//}countryy;
//c_pos create_country(char* name);
//n_pos sort_city(n_pos root, char* name, int stan);
//int usporedi(c_pos c_head, char* name, int br);
//int usporedi_st(n_pos current_n, int br);
//int ispis(c_pos c_head);
//int ispisi_grad(n_pos root);
//int sort_country(c_pos head, c_pos new_c);
//int read_cities(n_pos root, char* file);
//n_pos create_node(char* name, int stan);
//n_pos sort_population(n_pos root, char* name, int stan);
//

struct con_list_;
typedef struct con_list_* position;
typedef struct con_list_
{

	char name[c_LEN];
	int br_stan;
	position next;

}con_list;


struct country_;
typedef struct country_* pos;
typedef struct country_
{
	char name[C_LEN];
	pos left;
	pos right;
	con_list r_head;

}countryy;


int usporedi2(pos root, char* name, int br);
int ispis2(pos root);
int ispisi_grad(position head);
int read_cities2(position head, char* f_name);
position create_city2(char* name, int br);
int sort_city2(const position head, position new_city);
pos insert2(pos root, char* name);
pos create_root2(char* name);



int main(void)
{
	pos root = NULL;

	FILE* file = fopen("drzave.txt", "r");
	if (!file) return EXIT_FAILURE;

	while (!feof(file))
	{
		char name[C_LEN] = { 0 };
		char dat[uf_LEN] = { 0 };
		int ret=fscanf(file," %s %s", name, dat);
		if (ret != 2) break;
		root = insert2(root,name);
		if (!root) break;
		read_cities2(&root->r_head, dat);



	}
	fclose(file);

	ispis2(root);

	puts("\nUnesite drzavu i br san za usporedbu: ");
	int br = 0;
	char drzava[C_LEN] = { 0 };
	scanf(" %s %d", drzava, &br);
	usporedi2(root, drzava, br);

	return EXIT_SUCCESS;

}

int usporedi2(pos root, char* name, int br)
{
	if (strcmp(root->name, name) == 0)
	{
		position current = root->r_head.next;
		while (current != NULL)
		{
			if (current->br_stan > br)
				printf("To je: %s", current->name);
			current = current->next;

		}
		return EXIT_SUCCESS;
	}

	if (strcmp(root->name, name) > 0)
		return usporedi2(root->left, name, br);
	else if (strcmp(root->name, name) < 0)
		return usporedi2(root->right, name, br);
}

int ispis2(pos root)
{

	if (root)
	{
		ispis2(root->left);
		printf("%s:\n", root->name);
		ispisi_grad(&root->r_head);
		ispis2(root->right);
	}
	return EXIT_SUCCESS;
}

int ispisi_grad(position head)
{
	position curr = head->next;

	while (curr != NULL)
	{
		printf("%s--", curr->name);
		curr = curr->next;
	}
	puts("\n");
	return EXIT_SUCCESS;
}
int read_cities2(position head, char* f_name)
{
	FILE* file = fopen(f_name, "r");
	if (!file) return EXIT_FAILURE;

	while (!feof(file))
	{
		char name[c_LEN] = { 0 };
		int br = 0;

		int ret=fscanf(file, " %[^,],%d", name, &br);
		if (ret != 2) return EXIT_FAILURE;
		strcat(name, "");
		position new_city = create_city2(name, br);
		sort_city2(head,new_city);


	}
	fclose(file);
	return EXIT_SUCCESS;

}
position create_city2(char* name, int br)
{
	position new = (position)malloc(sizeof(con_list));
	if (!new) return NULL;

	strcpy(new->name, name);
	new->br_stan = br;
	new->next = NULL;

	return new;

}
int sort_city2( position head, position new_city)
{
	position current = head;

	while (current->next != NULL && current->next->br_stan > new_city->br_stan)
		current = current->next;
	if (current->next==NULL || current->next->br_stan != new_city->br_stan)
	{
		new_city->next = current->next;
		current->next = new_city;
	}
	else
	{
		while (strcmp(current->next->name, new_city->name) < 0)
			current = current->next;

		new_city->next = current->next;
		current->next = new_city;
	}
	return EXIT_FAILURE;
}


pos insert2(pos root,char* name)
{
	if (!root) return create_root2(name);

	if (strcmp(root->name, name) > 0)
		root->left = insert2(root->left, name);
	else if (strcmp(root->name, name) < 0)
		root->right = insert2(root->right, name);

	return root;
}

pos create_root2(char* name)
{
	pos new = (pos)malloc(sizeof(countryy));
	if (!new) return NULL;

	strcpy(new->name, name);
	new->r_head.next = NULL;
	new->left = NULL;
	new->right = NULL;

	return new;
}





























//
//
//int main(void)
//{
//	countryy c_head =
//	{
//		.c_next = NULL,
//		.name = " ",
//		.n_head =
//		{
//			.br_stan = 0,
//			.name = " ",
//			.left = 0,
//			.right = 0
//		}
//
//	};
//
//	FILE* file = fopen("drzave.txt", "r");
//	if (!file) return EXIT_FAILURE;
//
//	while (!feof(file))
//	{
//		char c_name[C_LEN] = { 0 };
//		char u_file[uf_LEN] = { 0 };
//
//		int fsf_r = fscanf(file, " %s %s", c_name, u_file);
//		if (fsf_r != 2) break;
//
//		c_pos new_country = create_country(c_name);
//		if (!new_country) break;
//		read_cities(&new_country->n_head, u_file);
//
//		sort_country(&c_head, new_country);
//
//	}
//	fclose(file);
//
//	ispis(&c_head);
//	puts("\nUnesite drzavu i br san za usporedbu: ");
//	int br = 0;
//	char drzava[C_LEN] = { 0 };
//	scanf(" %s %d", drzava, &br);
//	usporedi(&c_head, drzava, br);
//
//	return EXIT_SUCCESS;
//}
//int usporedi(c_pos c_head, char* name, int br)
//{
//	c_pos current = c_head->c_next;
//	if (!current) return EXIT_FAILURE;
//
//	while (current != NULL && strcmp(current->name, name) != 0)
//	{
//		current = current->c_next;
//	}
//
//	if (!current) return 0;
//	else {
//
//		n_pos current_n = &current->n_head;
//		usporedi_st(current_n, br);
//	}
//	return EXIT_FAILURE;
//}
//int usporedi_st(n_pos current_n, int br)
//{
//	n_pos curr = current_n;
//	if (curr)
//	{
//		usporedi_st(curr->left, br);
//		if (br < curr->br_stan) printf("\n -to su %s: ", curr->name);
//		usporedi_st(curr->right, br);
//	}
//
//	return EXIT_SUCCESS;
//}
//
//
//int ispis(c_pos c_head)
//{
//	c_pos current = c_head->c_next;
//	if (!current) return EXIT_FAILURE;
//
//	while (current)
//	{
//		printf("\n[%s]", current->name);
//
//		ispisi_grad2(&current->n_head);
//		current = current->c_next;
//	}
//
//	return EXIT_SUCCESS;
//}
//int ispisi_grad2(n_pos root)
//{
//	if (root)
//	{
//		ispisi_grad(root->left);
//		if (strcmp(root->name, "") != 0) printf("\n%s", root->name);
//		ispisi_grad(root->right);
//
//	}
//	return EXIT_SUCCESS;
//}
//
//int sort_country(c_pos head, c_pos new_c)
//{
//
//	c_pos current = head;
//	if (!current) return 0;
//	while (current->c_next != NULL && strcmp(current->c_next->name, new_c->name) < 0)
//	{
//		current = current->c_next;
//	}
//
//	new_c->c_next = current->c_next;
//	current->c_next = new_c;
//
//	return EXIT_SUCCESS;
//}
//int read_cities(n_pos root, char* file)
//{
//	FILE* file_p = fopen(file, "r");
//	if (!file_p) return EXIT_FAILURE;
//
//	while (!feof(file_p))
//	{
//		char name[c_LEN] = { 0 };
//		long int stan = 0;
//
//		int fsf_r = fscanf(file_p, " %[^,],%d", name, &stan);
//		if (fsf_r != 2) break;
//
//		root = sort_city(root, name, stan);
//		if (!root) break;
//
//
//	}
//
//	fclose(file_p);
//	return EXIT_SUCCESS;
//}
//
//n_pos create_node(char* name, int stan)
//{
//	n_pos new_c = (n_pos)malloc(sizeof(node));
//	if (!new_c) return NULL;
//
//	strcpy(new_c->name, name);
//	new_c->br_stan = stan;
//	new_c->left = NULL;
//	new_c->right = NULL;
//
//	return new_c;
//}
//n_pos sort_population(n_pos root, char* name, int stan)
//{
//
//	if (strcmp(root->name, name) < 0)
//	{
//		root->right = sort_city(root->right, name, stan);
//	}
//	else if (strcmp(root->name, name) > 0)
//	{
//		root->left = sort_city(root->left, name, stan);
//
//
//	}
//
//	return root;
//}
//
//n_pos sort_city(n_pos root, char* name, int stan)
//{
//	if (!root) return create_node(name, stan);
//
//	if (stan < root->br_stan)
//		root->left = sort_city(root->left, name, stan);
//	else if (stan > root->br_stan)
//		root->right = sort_city(root->right, name, stan);
//	else
//		return sort_population(root, name, stan);
//
//
//	return root;
//}
//
//c_pos create_country(char* name)
//{
//	c_pos new_c = (c_pos)malloc(sizeof(countryy));
//	if (!new_c) return NULL;
//
//	strcpy(new_c->name, name);
//	new_c->c_next = NULL;
//	new_c->n_head.left = NULL;
//	new_c->n_head.right = NULL;
//	strcpy(new_c->n_head.name, " ");
//
//	return new_c;
//
//}