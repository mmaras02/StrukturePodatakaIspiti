#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

struct _peopleList;
typedef struct _peopleList* PeoplePosition;
typedef struct _peopleList {
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	PeoplePosition next;
}peopleList;

struct _caffeList;
typedef struct _caffeList* CaffePosition;
typedef struct _caffeList {
	char caffe[MAX_SIZE];
	CaffePosition next;
	PeoplePosition listOfPeople;
}caffeList;

PeoplePosition InicilaizePeople(PeoplePosition head);
CaffePosition InicializeCaffe(CaffePosition head);
int ReadFromFile(char* filename, CaffePosition head);
int AddCoffeToList(CaffePosition head, char* firstName,char* lastName,char* caffe);
PeoplePosition AddPeopleToList(PeoplePosition head, char* firstName,char* lastName);
int PrintList(CaffePosition head);
int PrintPeople(PeoplePosition head);
CaffePosition FindSameCaffe(CaffePosition head, char* name);

int main()
{
	CaffePosition head = NULL;
	head = InicializeCaffe(head);

	ReadFromFile("kafici.txt", head);
	PrintList(head);

	return 0;
}
CaffePosition InicializeCaffe(CaffePosition head)
{
	CaffePosition newElement = head;
	newElement = (CaffePosition)malloc(sizeof(caffeList));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->caffe, "");
	newElement->listOfPeople = InicilaizePeople(newElement->listOfPeople);
	newElement->next = NULL;

	return newElement;
}
PeoplePosition InicilaizePeople(PeoplePosition head)
{
	PeoplePosition newElement = head;
	newElement = (PeoplePosition)malloc(sizeof(peopleList));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->firstName, "");
	strcpy(newElement->lastName, "");
	newElement->next = NULL;

	return newElement;
}
int ReadFromFile(char* filename, CaffePosition head)
{
	char firstName[MAX_SIZE] = { 0 };
	char lastName[MAX_SIZE] = { 0 };
	char caffe[MAX_SIZE] = { 0 };
	CaffePosition temp = NULL;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f," %s %s %s", firstName, lastName, caffe);
		temp = FindSameCaffe(head, caffe);
		if(temp==NULL)
			AddCoffeToList(head, firstName, lastName, caffe);
		else
			AddPeopleToList(temp->listOfPeople, firstName, lastName);

	}
	fclose(f);
	return 0;
}
int AddCoffeToList(CaffePosition head, char* firstName, char* lastName, char* caffe)
{
	CaffePosition newElement = NULL;
	newElement = InicializeCaffe(newElement);
	strcpy(newElement->caffe, caffe);
	newElement->listOfPeople=AddPeopleToList(newElement->listOfPeople, firstName, lastName);

	while (head->next != NULL)
	{
		if (strcmp(head->next->caffe, caffe) < 0)
			break;
		head = head->next;
	}
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
PeoplePosition AddPeopleToList(PeoplePosition head, char* firstName, char* lastName)
{
	PeoplePosition newElement = NULL;
	newElement = InicilaizePeople(newElement);
	strcpy(newElement->firstName, firstName);
	strcpy(newElement->lastName, lastName);

	while (head->next != NULL)
	{
		if (strcmp(head->next->lastName, lastName) > 0)
			break;
		head = head->next;
	}
	newElement->next = head->next;
	head->next = newElement;

	return head;
}
int PrintList(CaffePosition head)
{
	while (head != NULL)
	{
		printf("\n%s", head->caffe);
		PrintPeople(head->listOfPeople);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int PrintPeople(PeoplePosition head)
{
	while (head != NULL)
	{
		printf(" %s %s\n", head->firstName, head->lastName);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int Find(CaffePosition head, char* name)
{
	while (head != NULL)
	{
		if (strcmp(head->caffe, name) == 0)
			return 1;
		head = head->next;
	}
	return 0;
}
CaffePosition FindSameCaffe(CaffePosition head, char* name)
{
	while (head != NULL)
	{
		if (strcmp(head->caffe, name) == 0)
			return head;
		head = head->next;
	}
	return NULL;
}