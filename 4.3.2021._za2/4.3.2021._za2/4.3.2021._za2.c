//Iz datoteke cita kategoriju,naziv i količinu artikla u skladištu. Izgraditi vezanu list nakon toga iz druge datoteke
//koja predstavlja račun čitaju podaci i umanjuje se stanje u skladštu. Ispisati kateoriju a zatim i 
//nazive artikala cija je količina pala ispod 5
//za 3-->napraviti vezanu listu kategorija a svaka kategorija ima dodatnu listu artikala koji joj pripadaju
//za 4-->kategorije i artikli sortirani po abecedi
//za 5-->artikli cija je kolicina najniza pomaknu na početak liste

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

struct _storageList;
typedef struct _storageList* Position;
typedef struct _storageList {
	char category[MAX_SIZE];
	char article[MAX_SIZE];
	int quantity;
	Position next;
}StorageList;

Position InicializeList(Position head);
int AddInList(Position head, char* category, char* article, int quantity);
int InsertAfter(Position head, Position newElement);
int ReadFromFile(char* filename, Position head);
int ReadReceiptFromFile(char* filename,Position head);
int PrintList(Position head);
int FindArticle(Position head, char* category, char* article, int quantity);
int UpdateStorage(Position head, char* category, char* article, int quantity);
int ChangeStorage(Position head, char* category, char* article, int quantity);

int main()
{
	Position head = NULL;
	head = InicializeList(head);

	printf("\nStorage status\n-------------------\n");
	ReadFromFile("storage.txt", head);
	PrintList(head);

	printf("\nStatus after reading receipt\n-------------------\n");
	ReadReceiptFromFile("receipt.txt", head);
	PrintList(head);

	return 0;
}
Position InicializeList(Position head)
{
	Position newElement = head;
	newElement = (Position)malloc(sizeof(StorageList));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->category, "");
	strcpy(newElement->article, "");
	newElement->quantity = 0;
	newElement->next = NULL;

	return newElement;
}
int AddInList(Position head, char* category, char* article, int quantity)
{
	Position newElement = NULL;
	newElement = InicializeList(newElement);
	strcpy(newElement->category, category);
	strcpy(newElement->article, article);
	newElement->quantity = quantity;

	while (head->next != NULL)
	{
		if (strcmp(head->next->category, category) < 0)
			break;
		head = head->next;
	}
	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}
int InsertAfter(Position head, Position newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int ReadFromFile(char* filename, Position head)
{
	char category[MAX_SIZE] = { 0 };
	char article[MAX_SIZE] = { 0 };
	int quantity = 0;
	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return NULL;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", category, article, &quantity);
		if (FindArticle(head, category, article, quantity) == 1)
			UpdateStorage(head, category, article, quantity);
		else
			AddInList(head, category, article, quantity);
	}
	fclose(f);
	return 0;
}
int FindArticle(Position head, char* category, char* article, int quantity)
{
	while (head != NULL)
	{
		if (strcmp(head->category, category) == 0 && strcmp(head->article, article) == 0)
			return 1;
		head = head->next;
	}
	return 0;
}
int UpdateStorage(Position head, char* category, char* article, int quantity)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		if (strcmp(temp->category, category) == 0 && strcmp(temp->article, article) == 0)
			temp->quantity += quantity;
		temp = temp->next;
	}
	return 0;
}
int PrintList(Position head)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		printf(" %s %s %d\n", temp->category, temp->article, temp->quantity);
		temp = temp->next;
	}
	return 0;
}
int ReadReceiptFromFile(char* filename, Position head)
{
	char category[MAX_SIZE] = { 0 };
	char article[MAX_SIZE] = { 0 };
	int quantity = 0;
	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return NULL;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", category, article, &quantity);
		ChangeStorage(head, category, article, quantity);
	}
	fclose(f);
	return 0;
}
int ChangeStorage(Position head, char* category, char* article, int quantity)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		if (strcmp(temp->category, category) == 0 && strcmp(temp->article, article) == 0)
			temp->quantity -= quantity;
		temp = temp->next;
	}
	return 0;
}