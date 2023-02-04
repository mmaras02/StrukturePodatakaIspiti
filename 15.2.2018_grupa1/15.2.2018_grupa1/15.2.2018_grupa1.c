/*Napisati program koji:
a) Iz datoteke â€ždrzave.txtâ€ś ÄŤita popis drĹľava i njihov ID od proÄŤitanih drĹľava izgraditi vezanu listu
drĹľava na sortirani naÄŤin od poÄŤetka prema kraju abecede (treba raditi sortirani unos, a ne
naknadno sortirati). Uz pokazivaÄŤ na sljedeÄ‡u drĹľavu struktura od koje se gradi vezana lista
mora sadrĹľavati i pokazivaÄŤ na stablo gradova koji su u toj drĹľavi (trenutno NULL) - za 2

b) Iz datoteke â€žgradovi.txtâ€ś proÄŤitati ime grada i ID drĹľave u kojoj se nalazi. PronaÄ‡i odgovarajuÄ‡u
drĹľavu u gornjoj listi, te dodati proÄŤitani grad u stablo gradova te drĹľave. Za zadanu drĹľavu
ispisati sve njene gradove po abecedi. â€“ za 5*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 1024

struct _city;
typedef struct _city* CityPosition;
typedef struct _city{
	char cityName[MAX_SIZE];
	int countryId;
	CityPosition right;
	CityPosition left;
}City;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country {
	char countryName[MAX_SIZE];
	int id;
	CountryPosition next;
	CityPosition cityList;//stablo
}Country;

CountryPosition InitializeCountry(CountryPosition head);
CityPosition InitializeCity(CityPosition root);
int AddCountyInList(CountryPosition head, char* Countryname, int id);
int AddCityInTree(CityPosition root, char* cityName);
int ReadCountriesFromFile(char* filename, CountryPosition head);
int ReadCitiesFromFile(char* filename,CountryPosition head);
int InsertAfter(CountryPosition head, CountryPosition newElement);
int PrintList(CountryPosition head);
int PrintTree(CityPosition root);
CountryPosition FindCountry(CountryPosition head, int id);

int main()
{
	int searchedCounty=0 ;
	CountryPosition foundCountry = NULL;

	CountryPosition head = NULL;
	head = InitializeCountry(head);

	printf("List of ");
	ReadCountriesFromFile("countries.txt", head);
	ReadCitiesFromFile("cities.txt", head);
	PrintList(head->next);

	printf("\nEnter the country id to see cities: ");
	scanf(" %d", &searchedCounty);

	foundCountry = FindCountry(head, searchedCounty);
	if (!foundCountry)
		printf("Country not found! \n");
	else
	{
		printf("\nCities in %s are: ", foundCountry->countryName);
		PrintTree(foundCountry->cityList);
	}
	return 0;
}
CountryPosition InitializeCountry(CountryPosition head)
{
	CountryPosition newElement = head;
	newElement = (CountryPosition)malloc(sizeof(Country));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->countryName, "");
	newElement->id = 0;
	newElement->cityList = InitializeCity(newElement->cityList);
	newElement->next = NULL;

	return newElement;
}
CityPosition InitializeCity(CityPosition root)
{
	CityPosition newElement = root;
	newElement = (CityPosition)malloc(sizeof(City));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newElement->cityName, "");
	newElement->countryId = 0;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
int InsertAfter(CountryPosition head, CountryPosition newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int AddCountyInList(CountryPosition head, char* countryName, int id)
{
	CountryPosition temp=head;
	CountryPosition newElement = NULL;
	newElement = InitializeCountry(newElement);
	strcpy(newElement->countryName, countryName);
	newElement->id = id;

	while (temp->next != NULL && strcmp(temp->next->countryName, countryName) < 0)
		temp = temp->next;

	if (temp->next == NULL || strcmp(temp->next->countryName, countryName))
		InsertAfter(temp, newElement);

	return EXIT_SUCCESS;
}
int ReadCountriesFromFile(char* filename, CountryPosition head)
{
	char countryName[MAX_SIZE] = { 0 };
	int id = 0;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %d %s", &id, countryName);
		AddCountyInList(head, countryName, id);
	}
	fclose(f);
	return EXIT_SUCCESS;
}
int PrintList(CountryPosition head)
{
	while (head != NULL)
	{
		printf(" %d. %s\n", head->id, head->countryName);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int AddCityInTree(CityPosition root, char* cityName)
{
	CityPosition newElement = NULL;
	newElement = InitializeCity(newElement);
	strcpy(newElement->cityName, cityName);

	if (root == NULL)
		return newElement;
	if (strcmp(root->cityName, cityName) < 0)
		root->right = AddCityInTree(root->right, cityName);
	if (strcmp(root->cityName, cityName) > 0)
		root->left = AddCityInTree(root->left, cityName);

	return root;
}
int ReadCitiesFromFile(char* filename,CountryPosition head)
{
	char cityName[MAX_SIZE] = { 0 };
	int countryId = 0;
	CountryPosition foundCounty = NULL;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %d", cityName, &countryId);
		foundCounty = FindCountry(head, countryId);
		if (foundCounty)
			AddCityInTree(foundCounty->cityList, cityName);
	}
	fclose(f);
	return EXIT_SUCCESS;
}
CountryPosition FindCountry(CountryPosition head, int id)
{
	while (head != NULL)
	{
		if (head->id == id)
			return head;
		head = head->next;
	}
	return NULL;
}
int PrintTree(CityPosition root)
{
	if (root == NULL)
		return NULL;
	PrintTree(root->left);
	printf(" %s\n", root->cityName);
	PrintTree(root->right);

	return EXIT_SUCCESS;
}