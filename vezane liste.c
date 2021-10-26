#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position head, Position first);
int Delete(Position head, char* surname);

int main(int argc, char** argv)
{

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	AppendList(p, "Iva", "Medvidovic", 2001);
	AppendList(p, "Jakov", "Biocic", 2002);
	AppendList(p, "Nina", "Galic", 2001);
	AppendList(p, "Petra", "Medvidovic", 2004);

	PrintList(p->next);

	printf("Lista nakon brisanja:\n");
	Delete(p, "Medvidovic");
	PrintList(p->next);

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("Ime: %s\tPrezime: %s\tDatum rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	printf("\n");

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
Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;

}
int FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

Position FindBefore(Position head, Position first)
{
	Position temp = head;
	Position temp1 = first;
	while (temp)
	{
		if (temp->next == temp1) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
int Delete(Position p, char* surname)
{
	Position curr = FindBySurname(p, surname);
	Position prev = FindBefore(p, curr);
	if (prev == NULL)
		return -1;
	prev->next = curr->next;
	free(curr);

	return 0;
}