#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

//cita iz datoteke tekst kreira binarno stablo pretrazivanja. U njega se upisuju sve razlicite rijeci iz teksta s pripadajućim duljinama
//Program iz stabla upisuje u listu sve samo rijeci koje su dulje od prosjecne duljine svvih rijči--ispisati listu

struct _list;
typedef struct _list* ListPosition;
typedef struct _list {
	char word[MAX_SIZE];
	int length;
	ListPosition next;
}List;

struct _tree;
typedef struct _tree* TreePosition;
typedef struct _tree {
	char word[MAX_SIZE];
	int length;
	TreePosition right;
	TreePosition left;
	ListPosition list;
}Tree;

ListPosition InicializeList(ListPosition head);
TreePosition InicializeTree(TreePosition root);
TreePosition AddInTree(TreePosition root, char* word);
int AddInList(ListPosition head, char* word,int length);
int InsertAfter(ListPosition head, ListPosition newWord);
int PrintList(ListPosition head);
int PrintInOrder(TreePosition root);
TreePosition ReadFromFile(char* filename,TreePosition root);
int FindAvg(TreePosition root);
TreePosition FindBiggerThan(TreePosition root, int avg, ListPosition head);
void FindAvgHelper(TreePosition root, int* num, int* length);

int main()
{
	int avg = 0;
	TreePosition root = NULL;
	ListPosition head = NULL;
	head = InicializeList(head);
	
	root = ReadFromFile("file.txt", root);
	PrintInOrder(root);
	avg = FindAvg(root);
	printf("\nAverage length is %d\n", avg);
	printf("\nList\n----------------\n");
	FindBiggerThan(root, avg, head);
	PrintList(head);

	return 0;
}
ListPosition InicializeList(ListPosition head)
{
	ListPosition newWord = head;
	newWord = (ListPosition)malloc(sizeof(List));
	if (!newWord)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newWord->word, "");
	newWord->length = 0;
	newWord->next = NULL;

	return newWord;
}
TreePosition InicializeTree(TreePosition root)
{
	TreePosition newWord = root;
	newWord = (TreePosition)malloc(sizeof(Tree));
	if (!newWord)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newWord->word, "");
	newWord->length = 0;
	newWord->left = NULL;
	newWord->right = NULL;

	return newWord;
}
TreePosition ReadFromFile(char* filename, TreePosition root)
{
	char word[MAX_SIZE] = { 0 };

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f," %s", word);
		root = AddInTree(root, word);
	}
	fclose(f);
	return root;
}
TreePosition AddInTree(TreePosition root, char* word)
{
	TreePosition newWord = NULL;
	newWord = InicializeTree(newWord);
	strcpy(newWord->word,word);
	newWord->length = strlen(word);

	if (root == NULL)
		root = newWord;
	else if (strcmp(root->word, word) < 0)
		root->right = AddInTree(root->right, word);
	else if (strcmp(root->word, word) > 0)
		root->left = AddInTree(root->left, word);
	return root;
}
int PrintInOrder(TreePosition root)
{
	if (root == NULL)
		return -1;
	PrintInOrder(root->left);
	printf(" %s (%d)\n", root->word, root->length);
	PrintInOrder(root->right);

	return EXIT_SUCCESS;
}
int FindAvg(TreePosition root)
{
	if (root == NULL)
		return 0;
	int num = 0, length = 0;
	FindAvgHelper(root, &num, &length);
	return length / num;
}

void FindAvgHelper(TreePosition root, int* num, int* length)
{
	if (root == NULL)
		return;
	(*num)++;
	(*length) += root->length;
	FindAvgHelper(root->left, num, length);
	FindAvgHelper(root->right, num, length);
}
TreePosition FindBiggerThan(TreePosition root, int avg, ListPosition head)
{
	if (root == NULL)
		return -1;
	FindBiggerThan(root->left,avg,head);
	if (root->length >= avg)
		AddInList(head, root->word,root->length);
	FindBiggerThan(root->right,avg,head);

	return 0;
}
int AddInList(ListPosition head, char* word, int length)
{
	ListPosition newWord = NULL;
	newWord = InicializeList(newWord);
	strcpy(newWord->word, word);
	newWord->length = length;

		while (head != NULL)
		{
			if (strcmp(head->word, word) < 0)
				break;
			head = head->next;
		}
	InsertAfter(head, newWord);

	return EXIT_SUCCESS;
}
int InsertAfter(ListPosition head, ListPosition newWord)
{
	newWord->next = head->next;
	head->next = newWord;

	return EXIT_SUCCESS;
}
int PrintList(ListPosition head)
{
	while (head->next != NULL)
	{
		printf(" %s (%d)\n", head->next->word, head->next->length);
		head = head->next;
	}
	return EXIT_SUCCESS;
}