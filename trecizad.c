#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

Position CreatePerson(char* name, char* surname, int birthYear);
int PrependList(Position head, char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position PrintList(Position first);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindBefore(Position head, char* surname);
Position FindBySurname(Position first, char* surname);
int Delete(Position head, char* surname);
int AddAfter(Position head, char* surname);
int AddBefore(Position head, char* surname);
Position FindPosition(Position head, char* surname);
int SortedInput(Position head);
int Sort(Position head);
int FileEntry(Position head, char* vezaneliste);
int ReadFile(Position head, char* vezaneliste);
int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;
	char dat[50] = { 0 };
	printf("Lista prije brisanja:\n");

	AppendList(p, "Iva", "Medvidovic", 2001);
	AppendList(p, "Jakov", "Biocic", 2002);
	AppendList(p, "Nina", "Galic", 2001);
	AppendList(p, "Petra", "Medvidovic", 2004);
	PrependList(p, "Ivana", "Divic", 1980);
	PrintList(p->next);

	printf("\nLista nakon brisanja:\n");

	Delete(p, "Medvidovic");
	PrintList(p->next);

	AddAfter(p, "Galic");

	printf("\nLista nakon dodavanja iza odredenog elementa:\n");
	PrintList(p->next);

	AddBefore(p, "Biocic");
	printf("\nLista nakon dodavanja prije odredenog elementa:\n");
	PrintList(p->next);

	printf("\nLista nakon sortiranja:\n");
	Sort(p);
	PrintList(p->next);

	SortedInput(p);
	PrintList(p->next);

	printf("Upisite ime datoteke u koju zelite pohraniti svoju listu: ");
	scanf(" %s", dat);
	FileEntry(p, dat);
	
	printf("\nUpisite ime datoteke koju zelite ucitati u svoju listu: ");
	scanf(" %s", dat);
	ReadFile(p, dat);
	
	return EXIT_SUCCESS;
}
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}
int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}
int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}
Position PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("\nIme: %-15s\tPrezime: %-19s\tDatum rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	printf("\n");

	return EXIT_SUCCESS;
}
Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
		return -1;
	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}
Position FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp) {
		if (strcmp(temp->surname, surname) == 0)
			return temp;
		temp = temp->next;
	}

	return NULL;
}
Position FindBefore(Position head, char* surname)
{
	Position prev = head;
	Position curr = FindBySurname(head, surname);

	while (prev) {
		if (prev->next == curr)
			return prev;
		prev = prev->next;
	}
	return NULL;
}
int Delete(Position p, char* surname)
{
	Position curr = NULL;
	Position prev = p;

	while (prev->next != NULL) {
		if (strcmp(prev->next->surname, surname) == 0) {
			curr = prev->next;
			prev->next = curr->next;
			free(curr);
		}
		else
			prev = prev->next;
	}
	return 0;
}
int AddAfter(Position head, char* surname)
{
	Position temp = FindBySurname(head->next, surname);
	char tname[MAX_SIZE] = { 0 }, tsurname[MAX_SIZE] = { 0 };
	int tbirthYear = 0;

	printf("\nUnesite ime novog elementa: ");
	scanf(" %s", tname);
	printf("\nUnesite prezime novog elementa: ");
	scanf(" %s", tsurname);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", &tbirthYear);

	Position newPerson = CreatePerson(tname, tsurname, tbirthYear);
	if (!newPerson)
		return -1;
	InsertAfter(temp, newPerson);

	return 0;
}
int AddBefore(Position head, char* surname)
{
	Position newPerson = NULL;
	Position prev = NULL;
	char tname[MAX_SIZE] = { 0 }, tsurname[MAX_SIZE] = { 0 };
	int tbirthYear = 0;

	printf("\nUnesite ime novog elementa: ");
	scanf(" %s", tname);
	printf("\nUnesite prezime novog elementa: ");
	scanf(" %s", tsurname);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", &tbirthYear);

	newPerson = CreatePerson(tname, tsurname, tbirthYear);
	if (!newPerson)
		return -1;
	prev = FindBefore(head, surname);
	if (!prev)
		return -1;
	InsertAfter(prev, newPerson);

	return EXIT_SUCCESS;
}
Position FindPosition(Position head, char* surname)
{
	Position temp = head;

	while (temp->next != NULL && strcmp(surname, temp->next->surname) > 0)
		temp = temp->next;
	return temp;
}
int SortedInput(Position head)
{
	Position newPerson = NULL;
	Position q = NULL;
	char tname[MAX_SIZE] = { 0 }, tsurname[MAX_SIZE] = { 0 };
	int tbirthYear = 0;

	printf("\nUnesite ime novog elementa: ");
	scanf(" %s", tname);
	printf("\nUnesite prezime novog elementa: ");
	scanf(" %s", tsurname);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", &tbirthYear);

	newPerson = CreatePerson(tname, tsurname, tbirthYear);
	if (!newPerson)
		return -1;

	q = FindPosition(head, tsurname);

	InsertAfter(q, newPerson);

	return EXIT_SUCCESS;
}
int FileEntry(Position head, char* Vezaneliste) {

	FILE* f = fopen(Vezaneliste, "w");
	Position p = head->next;

	if (!f) {
		printf("Greska!\n");
		return -1;
	}
	while (p != NULL) {

		fprintf(f, "%s %s %d\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}
	printf("Upis liste uspjesno obavljen!\n");

	fclose(f);

	return EXIT_SUCCESS;
}

int ReadFile(Position head, char* Vezaneliste) {

	FILE* f = NULL;
	f = fopen(Vezaneliste, "r");
	char tname[MAX_SIZE] = { 0 };
	char tsurname[MAX_SIZE] = { 0 };
	int tbirthYear = 0;

	if (!f) {
		printf("Greska!\n");
		return -1;
	}

	while (!feof(f)) {
		fscanf(f, " %s %s %d\n", tname, tsurname, &tbirthYear);
		AppendList(head, tname, tsurname, tbirthYear);
	}

	printf("Datoteka je ucitana na pocetak liste.\n");
	fclose(f);
	return EXIT_SUCCESS;
}

int Sort(Position head) {

	Position first = NULL;
	Position prev = NULL;
	Position curr = NULL;
	Position temp = NULL;
	Position empty = NULL;

	if (head->next == NULL) {
		printf("Lista je prazna.");
		return -1;
	}


	while (head->next != empty) {

		prev = head;
		curr = head->next;

		while (curr->next != empty) {

			if (strcmp(curr->surname, curr->next->surname) > 0) {

				temp = curr->next;
				prev->next = temp;
				curr->next = temp->next;
				temp->next = curr;
				curr = temp;
			}

			prev = curr;
			curr = curr->next;
		}
		empty = curr;
	}

	return EXIT_SUCCESS;
}