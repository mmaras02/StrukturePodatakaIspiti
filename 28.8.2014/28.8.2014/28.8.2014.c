#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

struct _list;
typedef struct _list* Position;
typedef struct _list {
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	int grade;
	Position next;
}List;

Position InicializeList(Position head);
int AddInList(Position head, char* firstName, char* lastName, int grade);
int InsertAfter(Position head, Position newElement);
int PrintList(Position head);
int ReadFromFile(char* filename, Position head);
int PassedAll(Position math,Position bio,Position physics,Position listAll);
int AverageGrade(Position math, Position bio, Position physics, Position average);

int main()
{
	Position math = NULL;
	math = InicializeList(math);

	Position bio = NULL;
	bio = InicializeList(bio);

	Position physics = NULL;
	physics = InicializeList(physics);

	Position passedAll = NULL;
	passedAll = InicializeList(passedAll);

	Position average = NULL;
	average = InicializeList(average);

	int choice = 0;

	do {
		printf("\nEnter the action you wish to make:\n1.Read math results\n2.Read bio results\n3.Read physics results\n4.Students who passed all subjetcs\n5.Average score of students\n6.exit\n");
		scanf(" %d", &choice);
		switch (choice)
		{
		case 1:
			printf("\nMath\n----------------------------------\n");
			ReadFromFile("math.txt", math);
			PrintList(math->next);
			break;
		case 2:
			printf("\nBio\n----------------------------------\n");
			ReadFromFile("bio.txt", bio);
			PrintList(bio->next);
			break;
		case 3:
			printf("\nPhysics\n----------------------------------\n");
			ReadFromFile("physics.txt", physics);
			PrintList(physics->next);
			break;
		case 4:
			printf("\nPassed All\n------------------------------\n");
			PassedAll(math, bio, physics, passedAll);
			PrintList(passedAll->next);
			break;
		case 5:
			printf("\nAverage\n------------------------------\n");
			AverageGrade(math, bio, physics, average);
			PrintList(average->next);
			break;
		case 6:
			break;
		default:
			break;
		}
	} while (choice != 6);

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
	newElement->grade = 0;
	newElement->next = NULL;

	return newElement;
}
int InsertAfter(Position head, Position newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int AddInList(Position head, char* firstName, char* lastName, int grade)
{
	Position newElement = NULL;
	newElement = InicializeList(newElement);
	strcpy(newElement->firstName, firstName);
	strcpy(newElement->lastName, lastName);
	newElement->grade = grade;

	while (head != NULL)
	{
		if (strcmp(head->lastName, lastName) < 0)
			break;
		head = head->next;
	}
	InsertAfter(head, newElement);
	return EXIT_SUCCESS;
}
int ReadFromFile(char* filename, Position head)
{
	char firstName[MAX_SIZE] = { 0 };
	char lastName[MAX_SIZE] = { 0 };
	int grade = 0;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", firstName, lastName, &grade);
		AddInList(head, firstName, lastName, grade);
	}
	fclose(f);
	return 0;
}
int PrintList(Position head)
{
	while (head != NULL)
	{
		printf(" %s %s %d\n", head->firstName, head->lastName, head->grade);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int PassedAll(Position math, Position bio, Position physics, Position listAll)
{
	Position newPerson = NULL;
	while (math != NULL)
	{
		if (math->grade >= 50 && bio->grade >= 50 && physics->grade >= 50)
		{
			newPerson = InicializeList(newPerson);
			strcpy(newPerson->firstName, math->firstName);
			strcpy(newPerson->lastName, math->lastName);

			InsertAfter(listAll, newPerson);
		}
		math = math->next;
		bio = bio->next;
		physics = physics->next;
	}
	return EXIT_SUCCESS;
}
int AverageGrade(Position math, Position bio, Position physics, Position average)
{
	Position newElement = NULL;
	int result = 0;
	while (math != NULL)
	{
		result =(math->grade + bio->grade + physics->grade)/3;
		newElement = InicializeList(newElement);
		newElement->grade = result;
		strcpy(newElement->firstName, math->firstName);
		strcpy(newElement->lastName, math->lastName);

		InsertAfter(average, newElement);

		math = math->next;
		bio = bio->next;
		physics = physics->next;
		result = 0;
	}
	return EXIT_SUCCESS;
}