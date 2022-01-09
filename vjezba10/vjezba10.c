#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50


struct _tree;
typedef struct _tree* TreePosition;
typedef struct _tree {
	char grad[MAX_SIZE];
	int broj_stanovnika;
	TreePosition left;
	TreePosition right;
}tree;

struct _List;
typedef struct _List* ListPosition;
typedef struct _List {
	char drzava[MAX_SIZE];
	TreePosition grad;
	ListPosition next;
}list;

int InsertToListFromFile(ListPosition head, char* filename);
int InsertToTreeFromFile(ListPosition drzava, char* filename);
int SortedInputList(ListPosition head, ListPosition newPerson);
int InsertAfter(ListPosition head, ListPosition newElement);
ListPosition MakeListElement(char* drzava);
int PrintList(ListPosition first);
int PrintTree(TreePosition current);
TreePosition SortedInputTree(TreePosition current, TreePosition newElement);
TreePosition MakeTreeElement(char* grad, int broj_stanovnika);

int main()
{
	list head = { .drzava = "", .grad = NULL, .next = NULL };
	ListPosition listaDrzava = &head;
    char ime_drzave[MAX_SIZE] = { 0 };
    int broj_stanovnika = 0;

	char filename[] = "drzave.txt";
	InsertToListFromFile(listaDrzava, filename);
	PrintList(listaDrzava);

	return 1;
}
int InsertToListFromFile(ListPosition head, char* fileName) {

    FILE* f = NULL;
    f = fopen(fileName, "r");
    char ime_drzave[MAX_SIZE] = { 0 };
    char buffer[MAX_SIZE] = { 0 };
    char ime_grada[MAX_SIZE] = { 0 };

    list t = { .drzava = "", .grad = NULL, .next = NULL };
    ListPosition temp = &t;

    if (!f) {
        printf("Greska!\n");
        return -1;
    }

    while (!feof(f)) {

        fscanf(f, "%s %s\n", ime_drzave, ime_grada);
        temp = MakeListElement(ime_drzave);

        InsertToTreeFromFile(temp, ime_grada);

        SortedInputList(head, temp);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int InsertToTreeFromFile(ListPosition ime_drzave, char* fileName) {
    FILE* f = NULL;
    f = fopen(fileName, "r");

    char ime_grada[MAX_SIZE] = { 0 };
    int broj_stanovnika = 0;

    if (!f) {
        perror("Greska!\n");
        return -1;
    }

    while (!feof(f)) {
        fscanf(f, "%s %d", ime_grada, &broj_stanovnika);
        TreePosition temp = MakeTreeElement(ime_grada, broj_stanovnika);
        ime_drzave->grad = SortedInputTree(ime_drzave->grad, temp);
    }

    fclose(f);

    return EXIT_SUCCESS;

}

int SortedInputList(ListPosition head, ListPosition NewEl) {

    ListPosition temp = NULL;
    temp = head->next;

    while (temp != NULL && strcmp(temp->drzava, NewEl->drzava) > 0) {
        temp = temp->next;
    }

    InsertAfter(NewEl, head);
    return EXIT_SUCCESS;
}

int InsertAfter(ListPosition head, ListPosition NewEl) {

    head->next = NewEl->next;
    NewEl->next = head;

    return EXIT_SUCCESS;
}

ListPosition MakeListElement(char* ime_drzave) {
    ListPosition NewEl = NULL;
    NewEl = (ListPosition)malloc(sizeof(list));

    if (!NewEl) {
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(NewEl->drzava, ime_drzave);
    NewEl->grad = NULL;
    NewEl->next = NULL;

    return NewEl;
}

int PrintList(ListPosition first) {
    ListPosition temp = first->next;

    while (temp) {
        printf("%s\n ", temp->drzava);
        PrintTree(temp->grad);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int PrintTree(TreePosition curr) {
    if (curr == NULL)
        return 0;

    PrintTree(curr->left);
    printf("\t%s - %d stanovnika\n", curr->grad, curr->broj_stanovnika);
    PrintTree(curr->right);

    return 0;
}

TreePosition SortedInputTree(TreePosition curr, TreePosition NewEl) {

    if (!curr)
        return NewEl;

    if (curr->broj_stanovnika < NewEl->broj_stanovnika) {
        curr->right = SortedInputTree(curr->right, NewEl);
    }

    else if (curr->broj_stanovnika > NewEl->broj_stanovnika) {
        curr->left = SortedInputTree(curr->left, NewEl);
    }
    else free(NewEl);

    return curr;
}

TreePosition MakeTreeElement(char* ime_grada, int broj_stanovnika) {
    TreePosition NewEl = (TreePosition)malloc(sizeof(tree));

    if (!NewEl) {
        printf("\nCan't allocate memory.");
        return NULL;
    }

    strcpy(NewEl->grad, ime_grada);
    NewEl->broj_stanovnika = broj_stanovnika;
    NewEl->right = NULL;
    NewEl->left = NULL;

    return NewEl;
}
int Print(ListPosition first) {
    ListPosition temp = first->next;

    while (temp) {
            printf("%s\n ", temp->drzava);
            PrintTree(temp->grad);
            temp = temp->next;
    }

    return EXIT_SUCCESS;
}