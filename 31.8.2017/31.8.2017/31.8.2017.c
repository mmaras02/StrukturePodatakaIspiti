/*Napisati program koji generira 15 sluÄŤajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu
listu, po redoslijedu generiranja, a ne sortirano. U listi ne smije biti duplih vrijednosti.
a) Potrebno je pronaÄ‡i minimalnu i maksimalnu vrijednost, te iz njih izraÄŤunati srednju vrijednost
((min+max)/2) i nakon toga sve vrijednosti koje su veÄ‡e od srednje prebaciti na kraj liste. Ispisati
minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu.
b) PronaÄ‡i vrijednost u listi koja je najbliĹľa srednjoj vrijednosti i nju postaviti kao root element
binarnog stabla za pretraĹľivanje. Nakon toga sve elemente iz liste prebaciti u stablo i gotovo
stablo ispisati na level order naÄŤin.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<math.h>

#define MAX_SIZE 1024

struct _list;
typedef struct _list* Position;
typedef struct _list {
	int number;
	Position next;
}List;

struct _tree;
typedef struct _tree* TreePosition;
typedef struct _tree {
	int number;
	TreePosition right;
	TreePosition left;
}Tree;

Position InitializeList(Position head);
int AddInList(Position head,int number);
int GenerateNumbers();
int PrintList(Position head);
int	InsertAfter(Position head, Position newElement);
int FindMax(Position head);
int FindMin(Position head);
int FindDouble(Position head, int num);
int CreateNewList(Position head, int avg);
Position FindLast(Position head);
TreePosition InitializeTree(TreePosition root);
TreePosition AddInTree(TreePosition root, int num);
int PrintInOrder(TreePosition root);
Position FindClosest(Position head, int avg);
void BuildTree(TreePosition root, Position head);

int main()
{
	srand(time(0));
	Position head = NULL;
	head = InitializeList(head);
	int min = 0, max = 0,i=0,avg=0,number=0;
	Position closest = NULL;

	for (i = 0;i < 15;i++)
	{
		number = GenerateNumbers();
		if (FindDouble(head, number) == 0)
			AddInList(head, number);
		else
			i--;
	}
	printf("\n----Random numbers list----\n");
	PrintList(head->next);

	min = FindMin(head);
	max = FindMax(head);
	avg = (max + min) / 2;

	printf("\n\n------------------\n");
	printf("Min element: %d\n", min);
	printf("Max element : % d\n", max);
	printf("Average: %d\n", avg);

	printf("\n------New list------\n");
	CreateNewList(head, avg);
	PrintList(head->next);

	closest = FindClosest(head, avg);
	printf(" \n\nClosest number to average is %d\n\n", closest->number);

	printf("\n---Binary tree---\n");
	TreePosition root = NULL;
	root=InitializeTree(root);
	root->number = closest->number;

	BuildTree(root, head->next);
	PrintInOrder(root);

	return 0;
}
Position InitializeList(Position head)
{
	Position newNumber = head;
	newNumber = (Position)malloc(sizeof(List));
	if (!newNumber)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	newNumber->number = 0;
	newNumber->next = NULL;

	return newNumber;
}
int GenerateNumbers()
{
	int num = 0;
	num = (rand() %(120 - 100 + 1)) + 100;

	return num;
}
int	InsertAfter(Position head, Position newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}

int AddInList(Position head,int number)
{
	Position newNumber = NULL;
	newNumber = InitializeList(newNumber);
	newNumber->number = number;

	if (head == NULL)
		head = newNumber;

	newNumber->next = head->next;
	head->next = newNumber;

	return EXIT_SUCCESS;
}
int PrintList(Position head)
{
	while (head != NULL)
	{
		printf(" %d ", head->number);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int FindDouble(Position head,int num)
{
	while (head != NULL)
	{
		if (head->number == num)
			return 1;
		head = head->next;
	}
	return 0;
}
int FindMin(Position head)
{
	int min=120;
	Position current = head->next;
	while (current != NULL)
	{
		if (current->number < min)
			min = current->number;
		current = current->next;
	}
	return min;
}
int FindMax(Position head)
{
	int max = 100;
	Position current = head->next;
	while (current != NULL)
	{
		if (current->number > max)
			max = current->number;
		current = current->next;
	}
	return max;
}
int CreateNewList(Position head, int avg)
{
	Position current = head;
	Position last = NULL;
	Position temp = NULL;
	last = FindLast(current);

	while (current->next != last) {
		if (current->next->number >= avg) {
			temp = current->next;
			current->next = temp->next;
			InsertAfter(last, temp);
		}
		else
			current = current->next;
	}
	return 0;
}
Position FindLast(Position head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}
Position FindClosest(Position head, int avg)
{
	int diff = 0;
	Position closest = head;
	int minDiff = abs(head->number - avg);
	Position current = head->next;
	while (current != NULL)
	{
		diff = abs(current->number - avg);
		if (diff < minDiff)
		{
			closest = current;
			minDiff = diff;
		}
		current = current->next;
	}
	return closest;
}
TreePosition InitializeTree(TreePosition root)
{
	TreePosition newElement = root;
	newElement = (TreePosition)malloc(sizeof(Tree));
	if (!newElement)
	{
		perror("Couldn't allocate memory\n");
		return NULL;
	}
	newElement->number = 0;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
int PrintInOrder(TreePosition root)
{
	if (root == NULL)
		return NULL;
	PrintInOrder(root->left);
	printf(" %d ", root->number);
	PrintInOrder(root->right);

	return EXIT_SUCCESS;
}
TreePosition AddInTree(TreePosition root,int num)
{
	TreePosition newElement = NULL;
	newElement = InitializeTree(newElement);

	if (!root)
	{
		newElement->number = num;
		return newElement;
	}
	if (root->number > num)
		root->left = AddInTree(root->left, num);
	if (root->number < num)
		root->right = AddInTree(root->right, num);
	return root;
}
void BuildTree(TreePosition root, Position head)
{
	while (head != NULL)
	{
		root = AddInTree(root, head->number);
		head = head->next;
	}
}