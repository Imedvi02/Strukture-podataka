#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int number;
	Position left;
	Position right;
}tree;

Position CreateNewElement(int number);
Position Insert(Position root, Position NewElement);
int Inorder(Position root);
int Preorder(Position root);
int Postorder(Position root);
int Levelorder(Position root);
Position FindElement(Position root, int element);
Position DeleteElement(Position root, int element);
Position FindMin(Position root);

int main()
{
	Position root = NULL;
	Position newElement = NULL;
	char temp = 0;
	int num = 0;

	printf("Izbornik:\n");
	printf("1 - unosenje novog elementa\n2 - inorder ispis\n3 - preorder ispis\n4 - postorder ispis\n5 - pronalazenje elementa\n6 - brisanje elementa\n7- prekid programa\n");


	do {

		scanf("%c", &temp);
		switch (temp)
		{
		case '1':
			printf("\nKoji broj zelite unijeti? ");
			scanf("%d", &num);
			newElement = CreateNewElement(num);
			if (!newElement)
				return -1;
			root = Insert(root, newElement);
			break;
		case '2':
			Inorder(root);
			printf("\n");
			break;
		case '3':
			Preorder(root);
			printf("\n");
			break;
		case '4':
			Postorder(root);
			printf("\n");
			break;
		case '5':
			printf("Koji element zelite pronaci? ");
			scanf("%d", &num);
			if (FindElement(root, num))
				printf("Element %d postoji u stablu.", num);
			else
				printf("Element %d se ne nalazi u stablu.", num);
			printf("\n");
			break;
		case '6':
			printf("Koji element zelite izbrisati? ");
			scanf("%d", &num);
			DeleteElement(root, num);
			break;
		default:
			break;

		}
	} while (temp != '7');

	return 0;
}
Position CreateNewElement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(tree));
	if (!newElement)
	{
		printf("Nije moguce alocirati memoriju!");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
Position Insert(Position current, Position newElement)
{
	if (current == NULL)
		return newElement;
	if (current->number < newElement->number)
		current->right = Insert(current->right, newElement);
	else if (current->number > newElement->number)
		current->left = Insert(current->left, newElement);
	else
		free(newElement);

	return current;
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
int Preorder(Position current)
{
	if (current == NULL)
		return 0;
	printf("%d ", current->number);
	Preorder(current->left);
	Preorder(current->right);

	return 0;
}
int Postorder(Position current)
{
	if (current == NULL)
		return 0;
	Postorder(current->left);
	Postorder(current->right);
	printf("%d ", current->number);

	return 0;
}
Position FindElement(Position root, int element)
{
	if (root == NULL)
		return NULL;
	else if (element < root->number)
		return FindElement(root->left, element);
	else if (element > root->number)
		return FindElement(root->right, element);
	else
		return root;

}
Position DeleteElement(Position root, int element)
{
	Position temp = NULL;
	if (NULL == root)
		printf("\nElement se ne nalazi u stablu!\n");
	else if (element < root->number)
		root->left = DeleteElement(root->left, element);
	else if (element > root->number)
		root->right = DeleteElement(root->right, element);
	else if (root->left != NULL && root->right != NULL) {
		temp = FindMin(root->right);
		root->number = temp->number;
		root->right = DeleteElement(root->right, root->number);
	}
	else {
		temp = root;
		if (root->left == NULL)
			root = root->right;
		else
			root = root->left;
		free(temp);
	}
	return root;
}
Position FindMin(Position root)
{
	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return FindMin(root->left);
}

