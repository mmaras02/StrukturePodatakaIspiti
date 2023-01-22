#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

struct _list;
typedef struct _list* Position;
typedef struct _list {
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	char coffePlace[MAX_SIZE];
	Position next;
}List;

Position InicializeList(Position head);
int AddInList(Position head, char* firstName, char* lastName, char* coffePlace);
int InsertAfter(Position head, Position newElement);
int PrintList(Position head);
int ReadFromFile(char* filename, Position head);
int FindCaffePlace(Position head, char* name);

int main()
{
	Position head = NULL;
	head = InicializeList(head);
	Position head1 = NULL;
	head1 = InicializeList(head1);
	char coffePlace[MAX_SIZE] = { 0 };
	int br = 0;

	printf("\nList of people and caffe places they have visited:\n");
	ReadFromFile("kafici.txt", head);
	PrintList(head->next);

	printf("\nPlease enter coffe place name you want to filter: ");
	scanf(" %s", coffePlace);

	FindCaffePlace(head, coffePlace);

	return 0;
}
Position InicializeList(Position head)
{
	Position newElement = head;
	newElement = (Position)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->firstName, "");
	strcpy(newElement->lastName, "");
	strcpy(newElement->coffePlace, "");
	newElement->next = NULL;

	return newElement;
}
int AddInList(Position head, char* firstName, char* lastName, char* coffePlace)
{
	Position newElement = NULL;
	newElement = InicializeList(newElement);
	strcpy(newElement->firstName, firstName);
	strcpy(newElement->lastName, lastName);
	strcpy(newElement->coffePlace, coffePlace);


	while (head->next != NULL)
	{
		if (strcmp(head->next->coffePlace, coffePlace) < 0)
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
	char firstName[MAX_SIZE] = { 0 };
	char lastName[MAX_SIZE] = { 0 };
	char coffePlace[MAX_SIZE] = { 0 };

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %s", firstName, lastName, coffePlace);
		AddInList(head, firstName, lastName, coffePlace);
	}
	fclose(f);
	return 0;
}
int PrintList(Position head)
{
	Position temp = head;
	while (temp != NULL)
	{
		printf(" %s %s  --> %s\n", temp->firstName, temp->lastName, temp->coffePlace);
		temp = temp->next;
	}
	return 0;
}
int FindCaffePlace(Position head, char* name)
{
	int br = 0;
	while (head != NULL)
	{
		if (strcmp(head->coffePlace, name) == 0)
		{
			printf(" %s %s\n", head->firstName, head->lastName);
			br++;
		}
		head = head->next;
	}
	printf("\nthere were %d people in that caffe place!\n", br);
	return 0;
}