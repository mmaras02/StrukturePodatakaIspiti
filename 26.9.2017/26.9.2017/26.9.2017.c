/*Kreirati dvije datoteke i u njih upisati 10 sluÄŤajno generiranih brojeva iz opsega od 20-35. Svaku od
datoteka proÄŤitati i spremiti u vezanu listu (kreiraju se dvije vezane liste, npr. L1 i L2). Ispisati ih.
Iz ove dvije vezane liste se kreiraju dvije nove vezane liste koje sadrĹľe:
a) presjek parnih ÄŤlanova listi L1 i L2;
b) uniju neparnih ÄŤlanova listi L1 i L2.
Kod kreiranja listi pod a) i b) se ne smije koristiti malloc, veÄ‡ uzeti postojeÄ‡e elemente iz listi L1 i
L2 i preusmjeriti pokazivaÄŤe. Ispisati sve ÄŤetiri liste.
U listama pod a) i b) ne smije biti duplih vrijednosti i vrijednosti moraju bit sloĹľene uzlaznim
redoslijedom. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1024

struct _list;
typedef struct _list* Position;
typedef struct _list {
	int number;
	Position next;
}List;

int AddInFile(char* filename);
int ReadFromFile(char* filename, Position head);
int GetRandom();
int AddInList(Position head, int number);
int InsertAfter(Position head, Position newElement);
Position InitializeList(Position head);
int PrintList(Position head);
Position CreateListOfEvenNumbers(Position head1, Position head2);
Position CreateListOfOddNumbers(Position head1, Position head2);
int FindElement(Position head,int num);
Position FindPrev(Position head, int num);


int main()
{
	srand(time(0));
	Position head1 = NULL, head2 = NULL,head3=NULL,head4=NULL;
	head1 = InitializeList(head1);
	head2 = InitializeList(head2);

	AddInFile("file1.txt");
	AddInFile("file2.txt");

	ReadFromFile("file1.txt", head1);
	ReadFromFile("file2.txt", head2);
	
	printf("\n----List1-----------------\n");
	PrintList(head1->next);
	printf("\n\n----List2-----------------\n");
	PrintList(head2->next);
	printf("\n\n----Even numbers------------\n");
	head3 = CreateListOfEvenNumbers(head1, head2->next);
	PrintList(head3->next);
	printf("\n\n----Odd numbers--------\n");
	head4 = CreateListOfOddNumbers(head1, head2);
	PrintList(head4->next);

	return 0;
}
Position InitializeList(Position head)
{
	Position newElement = head;
	newElement = (Position)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	newElement->number = 0;
	newElement->next = NULL;

	return newElement;
}
int AddInList(Position head, int number)
{
	Position newElement = NULL;
	newElement = InitializeList(newElement);
	newElement->number = number;

	if (head == NULL)
		head = newElement;

	InsertAfter(head, newElement);
	return EXIT_SUCCESS;
}
int InsertAfter(Position head, Position newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int AddInFile(char* filename)
{
	int i = 0;
	FILE* f;
	f = fopen(filename, "w");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	for (i = 0;i < 10;i++)
	{
		int num = GetRandom();
		fprintf(f, " %d", num);
	}
	fclose(f);
	return 0;
}
int GetRandom()
{
	int num = 0;
	num = (rand() % (35 - 20 + 1)) + 20;

	return num;
}
int ReadFromFile(char* filename, Position head)
{
	int num = 0;
	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Coulnd't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %d", &num);
		AddInList(head, num);
	}
	fclose(f);
	return EXIT_SUCCESS;
}
int PrintList(Position head)
{
	Position temp = head;
	while (temp != NULL)
	{
		printf(" %d", temp->number);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
Position FindPrev(Position head, int num)
{
	Position current = head;
	Position prev = NULL;

	while (current != NULL)
	{
		if (head->number == num)
			return head;
		if (current->number == num)
			return prev;
		prev = current;
		current = current->next;
	}
	return NULL;
}
		
int FindElement(Position head, int num)
{
	while (head != NULL)
	{
		if (head->number == num)
			return 1;
		head = head->next;
	}
	return 0;
}
Position CreateListOfEvenNumbers(Position head1, Position head2)
{
	Position head3 = NULL;
	Position temp = NULL;
	head3 = InitializeList(head3);
	Position current1 = head1;
	Position current2 = head2;
	Position last = head3;

	while (current1->next != NULL)
	{
		if (current1->next->number % 2 == 0)
		{
			if (head3 == NULL)
			{
				temp = current1->next;
				current1->next = temp->next;
				last = temp;
			}
			else
			{
				if (FindElement(head3, current1->next->number) == 1)
					current1 = current1->next;
				else
				{
					temp = current1->next;
					current1->next = temp->next;
					InsertAfter(last, temp);
				}
			}
		}
		else
			current1 = current1->next;
	}

	while (current2->next != NULL)
	{
		if (current2->next->number % 2 == 0)
		{
			if (FindElement(head3, current2->next->number) == 1)
				current2 = current2->next;
			else
			{
				temp = current2->next;
				current2->next = temp->next;
				InsertAfter(last, temp);
			}
		}
		else
			current2 = current2->next;
	}
	return head3;
}
Position CreateListOfOddNumbers(Position head1, Position head2)
{
	Position head4 = NULL;
	Position temp = NULL;
	head4 = InitializeList(head4);
	Position current1 = head1;
	Position current2 = head2;
	Position last = head4;

	while (current1->next != NULL)
	{
		if (current1->next->number % 2 == 1)
		{
			if (head4 == NULL)
			{
				temp = current1->next;
				current1->next = temp->next;
				last = temp;
			}
			else
			{
				if (FindElement(head4, current1->next->number) == 1)
					current1 = current1->next;
				else
				{
					temp = current1->next;
					current1->next = temp->next;
					InsertAfter(last, temp);
				}
			}
		}
		else
			current1 = current1->next;
	}

	while (current2->next != NULL)
	{
		if (current2->next->number % 2 == 1)
		{
			if (FindElement(head4, current2->next->number) == 1)
				current2 = current2->next;
			else
			{
				temp = current2->next;
				current2->next = temp->next;
				InsertAfter(last, temp);
			}
		}
		else
			current2 = current2->next;
	}
	return head4;
}