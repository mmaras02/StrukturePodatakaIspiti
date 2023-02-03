/*Napisati program koji iz datoteke â€žtext.txtâ€ś ÄŤita zadani tekst. Od proÄŤitanih rijeÄŤi se gradi binarno
stablo pretraĹľivanja, s tim da ukoliko se pronaÄ‘e rijeÄŤ koja se veÄ‡ nalazi u stablu potrebno ju je
dodati u vezanu listu istih rijeÄŤi za odreÄ‘eni ÄŤvor. Ispisati stablo. Za odabranu rijeÄŤ ispitat koliko se
puta ponavlja.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>
#include<string.h>
#define MAX_SIZE 1024

struct _list;
typedef struct _list* Position;
typedef struct _list {
	char word[MAX_SIZE];
	Position next;
}List;

struct _tree;
typedef struct _tree* TreePosition;
typedef struct _tree {
	char word[MAX_SIZE];
	Position list;
	TreePosition right;
	TreePosition left;
}Tree;

Position InitializeList(Position head);
TreePosition InitializeTree(TreePosition root);
int AddInList(Position head, char* word);
int AddInTree(TreePosition root, char* word);
int PrintList(Position head);
int PrintInOrder(TreePosition root);
TreePosition ReadFromFile(char* filename, TreePosition root);
TreePosition FindWord(TreePosition root, char* word);

int main()
{
	TreePosition root = NULL;
	Position head = NULL;
	TreePosition node = NULL;
	char searchedWord[MAX_SIZE] = { 0 };
	head = InitializeList(head);

	root=ReadFromFile("file.txt", root);
	PrintInOrder(root);

	printf("\n\nEnter the word you want to find: ");
	scanf(" %s", searchedWord);
	node = FindWord(root, searchedWord);
	if (node == NULL)
	{
		printf("Searched word repeats 1 time in text!\n");
		return;
	}
	else
		PrintList(node->list);

	return 0;
}
Position InitializeList(Position head)
{
	Position newElement = head;
	newElement = (Position)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Coulnd't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->word, "");
	newElement->next = 0;

	return newElement;
}
TreePosition InitializeTree(TreePosition root)
{
	TreePosition newElement = root;
	newElement = (TreePosition)malloc(sizeof(Tree));
	if (!newElement)
	{
		perror("Coulnd't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->word, "");
	newElement->list = InitializeList(newElement->list);
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

TreePosition ReadFromFile(char* filename, TreePosition root)
{
	char word[MAX_SIZE] = { 0 };
	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n ");
		return NULL;
	}
	while (!feof(f))
	{
		fscanf(f, " %s", word);
		root = AddInTree(root, word);
	}
	fclose(f);
	return root;
}
int AddInTree(TreePosition root, char* word)
{
	TreePosition newElement = NULL;
	newElement = InitializeTree(newElement);
	strcpy(newElement->word, word);

	if (root == NULL)
		root = newElement;
	else if (strcmp(root->word, word) < 0)
		root->right = AddInTree(root->right, word);
	else if (strcmp(root->word, word) > 0)
		root->left = AddInTree(root->left, word);
	else if (strcmp(root->word, word) == 0)
		AddInList(root->list, word);

	return root;
}
int AddInList(Position head, char* word)
{
	Position newElement = NULL;
	newElement = InitializeList(newElement);
	strcpy(newElement->word, word);

	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int PrintList(Position head)
{
	int num = 0;
	while (head != NULL)
	{
		num++;
		head = head->next;
	}
	printf("Searched word repeats %d times in text!\n\n", num);
	return EXIT_SUCCESS;
}
int PrintInOrder(TreePosition root)
{
	if (root == NULL)
		return NULL;
	PrintInOrder(root->left);
	printf(" %s", root->word);
	PrintInOrder(root->right);

	return EXIT_SUCCESS;
}
TreePosition FindWord(TreePosition root, char* word)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(root->word, word) < 0)
		return FindWord(root->right, word);
	else if (strcmp(root->word, word) > 0)
		return FindWord(root->left, word);
	return root;
}