//Iz datoteke cita kategoriju,naziv i kolicinu artikla u skladištu. Izgraditi vezanu list nakon toga iz druge datoteke
//koj apredstavlja rcun citaju podaci i umanjuje se stanje u skladštu. Ispisati kategoriju a zatim i 
//nazive artikala cija je kolicina pala ispod 5
//za 3-->napraviti vezanu listu kategorija a svaka kategorija ima dodatnu listu artikala koji joj pripadaju
//za 4-->kategorije i artikli sortirani po abecedi
//za 5-->artikli cija je kolicina najniza pomaknu na pocetak liste

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

struct _articleList;
typedef struct _articleList* ArticlePosition;
typedef struct _articleList {
	char articleName[MAX_SIZE];
	int quantity;
	ArticlePosition next;
}ArticleList;

struct _categoryList;
typedef struct _categoryList* CategoryPosition;
typedef struct _categoryList {
	char categoryName[MAX_SIZE];
	CategoryPosition next;
	ArticlePosition articleList;
}CategoryList;

CategoryPosition InicializeCategory(CategoryPosition head);
ArticlePosition InicializeArticle(ArticlePosition head);
int AddInCategoryList(CategoryPosition head, char* categoryName, char* article, int quantity);
ArticlePosition AddInArticleList(ArticlePosition head, char* article, int quantity);
int ReadFromFile(char* filename,CategoryPosition head);
CategoryPosition FindSameCategory(CategoryPosition head, char* name);
int PrintList(CategoryPosition head);
int PrintArticle(ArticlePosition head);

int main()
{
	CategoryPosition head = NULL;
	head = InicializeCategory(head);

	ReadFromFile("storage.txt", head);
	PrintList(head->next);

	return 0;
}
CategoryPosition InicializeCategory(CategoryPosition head)
{
	CategoryPosition newCategory = head;
	newCategory = (CategoryPosition)malloc(sizeof(CategoryList));
	if (!newCategory)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newCategory->categoryName, "");
	newCategory->articleList = InicializeArticle(newCategory->articleList);
	newCategory->next = NULL;

	return newCategory;
}
ArticlePosition InicializeArticle(ArticlePosition head)
{
	ArticlePosition newArticle = head;
	newArticle = (ArticlePosition)malloc(sizeof(ArticleList));
	if (!newArticle)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(newArticle->articleName, "");
	newArticle->quantity = 0;
	newArticle->next = NULL;

	return newArticle;
}
int ReadFromFile(char* filename, CategoryPosition head)
{
	char category[MAX_SIZE] = { 0 };
	char article[MAX_SIZE] = { 0 };
	int quantity = 0;
	CategoryPosition temp = NULL;
	temp = InicializeCategory(temp);

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!\n");
		return -1;
	}
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", category, article, &quantity);
		temp = FindSameCategory(head, category);
		if (temp == NULL)
			AddInCategoryList(head, category, article, quantity);
		else
			temp->articleList=AddInArticleList(temp->articleList, article, quantity);
	}
	fclose(f);
	return 0;
}
int AddInCategoryList(CategoryPosition head, char* categoryName,char* article,int quantity)
{
	CategoryPosition temp = head;
	CategoryPosition newElement = NULL;
	newElement = InicializeCategory(newElement);
	strcpy(newElement->categoryName, categoryName);
	newElement->articleList = AddInArticleList(newElement->articleList, article, quantity);

	while (temp !=NULL)
	{
		if (strcmp(temp->categoryName, categoryName) < 0)
			break;
		temp = temp->next;
	}
	newElement->next = temp->next;
	temp->next = newElement;

	return EXIT_SUCCESS;
}

//sortirano po imenu artikla(ocj4)
ArticlePosition AddInArticleList(ArticlePosition head, char* article, int quantity)
{
	ArticlePosition prev = NULL;
	ArticlePosition current = head;
	ArticlePosition newArticle = NULL;
	newArticle = InicializeArticle(newArticle);
	strcpy(newArticle->articleName, article);
	newArticle->quantity = quantity;

	if (head == NULL)
		return newArticle;

	while (current != NULL)
	{
		if (strcmp(current->articleName, article) == 0)
		{
			current->quantity += quantity;
			return head;
		}
		else if (strcmp(current->articleName, article) > 0)
		{
			newArticle->next = current;
			if (prev == NULL)
				head = newArticle;
			else
				prev->next = newArticle;
			return head;
		}
		prev = current;
		current = current->next;
	}
	prev->next = newArticle;

	return head;
}
CategoryPosition FindSameCategory(CategoryPosition head, char* name)
{
	while (head!=NULL)
	{
		if (strcmp(head->categoryName, name) == 0)
			return head;
		head = head->next;
	}
	return NULL;
}
int PrintArticle(ArticlePosition head)
{
	printf("-------------------------\n");
	ArticlePosition temp = head->next;
	while (temp != NULL)
	{
		printf(" %s %d\n", temp->articleName, temp->quantity);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintList(CategoryPosition head)
{
	while (head != NULL)
	{
		printf("\n%s\n", head->categoryName);
		PrintArticle(head->articleList);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

//artikl s najmanjom kolicinom se stavlja na početak liste
 
/*ArticlePosition AddInArticleList(ArticlePosition head, char* article, int quantity)
{
	ArticlePosition newArticle = NULL;
	newArticle = InicializeArticle(newArticle);
	strcpy(newArticle->articleName, article);
	newArticle->quantity = quantity;

	if (head == NULL)
		return newArticle;

	if (head->quantity > quantity) {
		newArticle->next = head;
		return newArticle;
	}

	ArticlePosition current = head;
	while (current->next != NULL) {
		if (current->next->quantity > quantity) {
			break;
		}
		current = current->next;
	}

	newArticle->next = current->next;
	current->next = newArticle;

	return head;
}*/