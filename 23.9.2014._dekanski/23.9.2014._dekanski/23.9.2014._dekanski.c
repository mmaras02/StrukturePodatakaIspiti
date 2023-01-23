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
	int grade;
	Position next;
}List;

Position InicializeList(Position head);
int AddInList(Position head, char* firstName, char* lastName, int grade);
int ReadFromFile(char* filename, Position head);
int InsertAfter(Position head, Position newStudent);
int PrintList(Position head);
int ChangeToGrade(float grade);
int PassedAllList(Position exam1,Position exam2,Position final);
int InsertSorted(Position exam1, Position exam2, Position final);

int main()
{
	Position exam1 = NULL,exam2=NULL,final=NULL;
	exam1 = InicializeList(exam1);
	exam2 = InicializeList(exam2);
	final = InicializeList(final);

	ReadFromFile("exam1.txt", exam1);
	ReadFromFile("exam2.txt", exam2);

	int choice = 0;
	do {
		printf("\nEnter the action you wish to make:\n1.Read first exam\n2.Read second exam\n3.Passed with grade\n4.Exit\n");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			printf("\nExam1\n-------------------------\n");
			PrintList(exam1->next);
			break;
		case 2:
			printf("\nExam2\n-------------------------\n");
			PrintList(exam2->next);
			break;
		case 3:
			printf("\nPassed with grade\n------------------------\n");
			PassedAllList(exam1, exam2, final);
			PrintList(final->next);
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (choice != 4);

	return 0;
}
Position InicializeList(Position head)
{
	Position newStudent = head;
	newStudent = (Position)malloc(sizeof(List));
	if (!newStudent)
	{
		perror("couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newStudent->firstName, "");
	strcpy(newStudent->lastName, "");
	newStudent->grade = 0;
	newStudent->next = NULL;
	
	return newStudent;
}
int InsertAfter(Position head, Position newStudent)
{
	newStudent->next = head->next;
	head->next = newStudent;

	return EXIT_SUCCESS;
}
int AddInList(Position head, char* firstName, char* lastName, int grade)
{
	Position newStudent = NULL;
	newStudent = InicializeList(newStudent);
	strcpy(newStudent->firstName, firstName);
	strcpy(newStudent->lastName, lastName);
	newStudent->grade = grade;

	while(head != NULL)
	{
		if (strcmp(head->lastName, lastName) < 0)
			break;
		else if (strcmp(head->lastName, lastName) == 0)
			if (strcmp(head->firstName, firstName) < 0)
				break;
		head = head->next;
	}
	InsertAfter(head, newStudent);
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
	Position temp = head;
	while (temp != NULL)
	{
		printf(" %s %s %d\n", temp->firstName, temp->lastName, temp->grade);
		temp = temp->next;
	}
	return 0;
}
int ChangeToGrade(float grade)
{
	if (grade >= 50 && grade < 60)
		return 2;
	else if (grade >= 60 && grade < 74)
		return 3;
	else if (grade >= 74 && grade < 87)
		return 4;
	else if (grade >= 87 && grade < 100)
		return 5;
}
int PassedAllList(Position exam1, Position exam2, Position final)
{
	Position newEl = NULL;
	while (exam1 != NULL)
	{
		if (exam1->grade >= 50 && exam2->grade >= 50)
			InsertSorted(exam1, exam2, final);
		exam1 = exam1->next;
		exam2 = exam2->next;
	}
	return 0;
}
int InsertSorted(Position exam1, Position exam2, Position final)
{
	Position newEl = NULL;
	newEl = InicializeList(newEl);
	strcpy(newEl->firstName, exam1->firstName);
	strcpy(newEl->lastName, exam2->lastName);
	newEl->grade = ChangeToGrade((exam1->grade + exam2->grade) / 2);

	while (final->next != NULL)
	{
		if (final->next->grade < newEl->grade)
			break;
		final = final->next;
	}
	InsertAfter(final, newEl);
	return EXIT_SUCCESS;
}