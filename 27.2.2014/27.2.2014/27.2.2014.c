#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

//Napisati program koji iz datoteke èita podatke o broju bodova koje je jedan student dobio na ispitu
// i sprema ih u binarno stablo pretraživanja. (Napomena : 0 <
//	broj_bodova <= 100).Ispisati binarno stablo na „inorder“ naèin.
//	U tako kreiranom binarnom stablu potrebno je za svakog od studenata izraèunati i relativan broj bodova
//	po formuli : relativan_broj_bodova = (broj_bodova / MAX(broj_bodova)).Ispisati binarno stablo na
//	„preorder“ naèin.

struct _studentTree;
typedef struct _studentTree* Position;
typedef struct _studentTree {
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	int points;
	float relativePoints;
	Position left;
	Position right;
}StudentTree;

Position InicializeTree(Position root);
Position AddInTree(Position root, char* firstName, char* lastName, int points);
int PrintInorder(Position root);
Position ReadFromFile(char* filename, Position root);
int PrintPreorder(Position root);
Position AddRelativePoints(Position root, Position max);
Position FindMax(Position root);


int main()
{
	Position root = NULL;
	Position max = NULL;
	max = InicializeTree(max);

	root = ReadFromFile("exam.txt", root);
	PrintInorder(root);
	max = FindMax(root);
	printf("\nRelative points\n");
	root = AddRelativePoints(root,max);
	PrintPreorder(root);

	return 0;
}
Position InicializeTree(Position root)
{
	Position newStudent = root;
	newStudent = (Position)malloc(sizeof(StudentTree));
	if (!newStudent)
	{
		perror("Couldn't allocate memrory!\n");
		return NULL;
	}
	strcpy(newStudent->firstName, "");
	strcpy(newStudent->lastName, "");
	newStudent->points = 0;
	newStudent->relativePoints = 0.0;
	newStudent->left = NULL;
	newStudent->right = NULL;

	return newStudent;
}
Position ReadFromFile(char* filename, Position root)
{
	char firstName[MAX_SIZE] = { 0 };
	char lastName[MAX_SIZE] = { 0 };
	int points = 0;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", firstName, lastName, &points);
		root = AddInTree(root, firstName, lastName, points);
	}
	fclose(f);
	return root;
}
Position AddInTree(Position root, char* firstName, char* lastName, int points)
{
	Position newStudent = NULL;
	newStudent = InicializeTree(newStudent);
	strcpy(newStudent->firstName, firstName);
	strcpy(newStudent->lastName, lastName);
	newStudent->points = points;

	if (root == NULL)
		root = newStudent;
	else if (root->points < points)
		root->right = AddInTree(root->right, firstName, lastName, points);
	else if (root->points > points)
		root->left = AddInTree(root->left, firstName, lastName, points);

	return root;
}
int PrintInorder(Position root)
{
	if (root == NULL)
		return 0;
	PrintInorder(root->left);
	printf(" %s %s %d\n", root->firstName, root->lastName, root->points);
	PrintInorder(root->right);

	return 0;
}
Position AddRelativePoints(Position root,Position max)
{
	//relativan_broj_bodova = (broj_bodova / MAX(broj_bodova))
	if (root == NULL)
		return NULL;

	root->relativePoints = ((float)root->points / max->points)*100;
	root->left = AddRelativePoints(root->left,max);
	root->right = AddRelativePoints(root->right,max);

	return root;
}
Position FindMax(Position root)
{
	if (root == NULL)
		return NULL;
	if (root->right == NULL)
		return root;
	else
		return FindMax(root->right);
}
int PrintPreorder(Position root)
{
	if (root == NULL)
		return NULL;

	printf("%s %s %d %lf\n", root->firstName, root->lastName, root->points, root->relativePoints);
	PrintPreorder(root->left);
	PrintPreorder(root->right);
	return 0;
}