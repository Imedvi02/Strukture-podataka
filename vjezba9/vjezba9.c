#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int number;
	Position left;
	Position right;
} tree;

struct _List;
typedef struct _List* LPosition;
typedef struct _List
{
	int number;
	LPosition next;
}List;

Position Insert(Position current, Position newElement);
Position CreateNewElement(int number);
int Inorder(Position current);
int Replace(Position current);
int PrintinList(Position current, LPosition head);
int PrependList(LPosition head, int number);
LPosition CreateNewListElement(int number);
int InsertAfter(LPosition position, LPosition newListElement);
int FileEntry(FILE* f, LPosition position);
LPosition FindLast(LPosition head);

int main()
{
	/*
	int array[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	Position root = NULL;
	Position newElement = NULL;
	int i = 0;

	root = (Position)malloc(sizeof(tree));
	root->number = array[0];
	root->left = NULL;
	root->right = NULL;

	
	for (i = 1; i < 10; i++)
	{
		newElement = CreateNewElement(array[i]);
		if (!newElement)
		{
			perror("Can't allocate memory!");
			return -1;
		}
		root = Insert(root, newElement);
	}

	Inorder(root);
	printf("\n");

	root->number = Replace(root);
	Inorder(root);
	printf("\n");
	*/
	srand(time(NULL));
	char dat[50] = { 0 };
	List head = { .next = NULL, .number = {0} };
	Position root = NULL;
	Position newElement = NULL;
	int i = 0;

	root = (Position)malloc(sizeof(tree));
	root->number = rand() % 80 + 10;
	root->left = NULL;
	root->right = NULL;

	for (i = 1; i < 10; i++)
	{
		newElement = CreateNewElement(rand() % 80 + 10);
		if (!newElement)
		{
			perror("Can't allocate memory!");
			return -1;
		}
		root = Insert(root, newElement);
	}

	printf("Upisite ime datoteke u koju zelite pohraniti svoju listu: ");
	scanf(" %s", dat);
	printf("\n");

	//a)
	PrintinList(root, &head);
	printf("\n");
	FileEntry(&head, dat);
	printf("\n");

	//b)
	root->number = Replace(root);
	PrintinList(root, &head);
	printf("\n");
	FileEntry(&head, dat);

	return 0;
}
Position Insert(Position current, Position newElement)
{
	if (current == NULL)
		return newElement;
	if (current->number <= newElement->number)
		current->left = Insert(current->left, newElement);
	else if (current->number > newElement->number)
		current->right = Insert(current->right, newElement);
	return current;
}
Position CreateNewElement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(tree));
	if (!newElement)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;
		
	return newElement;
}
int Inorder(Position current)
{
	if (current == NULL)
		return 0;
	Inorder(current->left);
	printf("%d ", current->number);
	Inorder(current->right);

	return 0;
}
int Replace(Position current)
{
	int temp;
	if (current == NULL)
		return 0;
	else {
		temp = current->number;
		current->number = Replace(current->right) + Replace(current->left);
	}
		
	return temp + current->number;
}
int PrintinList(Position current, LPosition head)
{
	if (current == NULL)
		return 0;
	PrintinList(current->right, head);
	printf("%d ", current->number);
	AppendList(head, current->number);
	PrintinList(current->left, head);

	return 0;
}
int AppendList(LPosition head, int number)
{
	LPosition newListElement = NULL;
	LPosition last = NULL;

	newListElement = CreateNewListElement(number);
	if (!newListElement) {
		return -1;
	}
	last = FindLast(head);
	InsertAfter(last, newListElement);

	return EXIT_SUCCESS;


}
LPosition FindLast(LPosition head)
{
	LPosition temp = head;
	
	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}
LPosition CreateNewListElement(int number)
{
	LPosition newListElement = NULL;
	newListElement = (LPosition)malloc(sizeof(List));
	if (!newListElement)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	newListElement->number = number;
	newListElement->next = NULL;

	return newListElement;
}
int InsertAfter(LPosition position, LPosition newListElement)
{
	newListElement->next = position->next;
	position->next = newListElement;

	return EXIT_SUCCESS;
}
int FileEntry(LPosition head, char* FileName)
{
	FILE* f = fopen(FileName, "w");
	LPosition position = head->next;
	if (!f) {
		printf("Greska!");
	}
	while (position != NULL)
	{
		fprintf(f, "%d ", position->number);
		position = position->next;
	}
	fprintf(f, "\n");

	printf("Upis liste u datoteku uspjesno obavljen!");
	fclose(f);

	return EXIT_SUCCESS;
}