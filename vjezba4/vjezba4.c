#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX_SIZE 50
#define MAX_LINE 1024

struct Polinom;
typedef struct _Polinom* Position;
typedef struct _Polinom {
	int koeficijent;
	int eksponent;
	Position next;
}polinom;

Position CreateP(int koef, int eks);
int ReadFile(Position head1, Position head2);
int StringToList(Position head, char* buffer);
int SortedInput(Position head, Position newP);
int MergeAfter(Position position, Position newP);
int InsertAfter(Position position, Position newP);
int DeleteAfter(Position position);
int PrintP(char* name, Position first);
int CreateandInsertAfter(int koeficijent, int eksponent, Position position);
int AddP1(Position resultHead, Position head1, Position head2);
int AddP2(Position resultHead, Position head1, Position head2);
int MultiplyP(Position resultHead, Position head1, Position head2);
int FreeMemory(Position head);

int main(int argc, char** argv)
{
	polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	polinom head2 = { .koeficijent = 0, .eksponent = 0, . next = NULL };
	polinom resultAdd = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	polinom resultMultiply = { .koeficijent = 0, .eksponent = 0, .next = NULL };

	if (ReadFile(&head1, &head2) == EXIT_SUCCESS)
	{
		PrintP("p1", head1.next);
		PrintP("p2", head2.next);

		AddP1(&resultAdd, &head1, &head2);
		MultiplyP(&resultMultiply, &head1, &head2);

		PrintP("pAdd", resultAdd.next);
		PrintP("pMultiply", resultMultiply.next);

		FreeMemory(&head1);
		FreeMemory(&head2);
		FreeMemory(&resultAdd);
		FreeMemory(&resultMultiply);
	}
	else
	{
		printf("Problem s funkcijom ReadFile!");
	}
	return EXIT_SUCCESS;
}
Position CreateP(int koef, int eks)
{
	Position newP = NULL;

	newP = (Position)malloc(sizeof(polinom));
	if (!newP) {
		perror("Greska kod alokacije memorije!");
		return -1;
	}

	newP->eksponent = eks;
	newP->koeficijent = koef;
	newP->next = NULL;

	return newP;
}

int ReadFile(Position head1, Position head2)
{

	FILE* f = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;
	char dat[MAX_SIZE] = { 0 };

	printf("Upisite ime datoteke:");
	scanf(" %s", dat);


	f = fopen(dat, "r");
	if (!f) {
		perror("Greska kod ucitavaja memorije!");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, f);
	status = StringToList(head1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	fgets(buffer, MAX_LINE, f);
	status = StringToList(head2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(f);

	return EXIT_SUCCESS;

}
int StringToList(Position head, char* buffer)
{
	char* tempBuffer = buffer;
	int koeficijent = 0;
	int eksponent = 0;
	int status = 0;
	int numofBytes = 0;
	Position newP = NULL;

	while (strlen(tempBuffer) > 0)
	{
		status = sscanf(tempBuffer, " %d %d %n", &koeficijent, &eksponent, &numofBytes);
		if (status != 2) {
			perror("Datoteka ne valja!");
			return EXIT_FAILURE;
		}

		newP = CreateP(koeficijent, eksponent);
		if (!newP) {
			return EXIT_FAILURE;
		}

		SortedInput(head, newP);
		tempBuffer += numofBytes;
	}
	return EXIT_SUCCESS;
}
int SortedInput(Position head, Position newP)
{
	Position temp = head;

	while (temp->next != NULL && temp->next->eksponent < newP->eksponent)
	{
		temp = temp->next;
	}

	MergeAfter(temp, newP);

	return EXIT_SUCCESS;
}
int MergeAfter(Position position, Position newP)
{
	if (position->next == NULL || position->next->eksponent != newP->eksponent)
	{
		InsertAfter(position, newP);
	}
	else
	{
		int resultKoef = position->next->koeficijent + newP->koeficijent;
		if (resultKoef == 0)
		{
			DeleteAfter(position);
		}
		else
		{
			position->next->koeficijent = resultKoef;
		}
		free(newP);
	}

	return EXIT_SUCCESS;

}
int InsertAfter(Position position, Position newP)
{
	newP->next = position->next;
	position->next = newP;

	return EXIT_SUCCESS;
}
int DeleteAfter(Position previous)
{
	Position curr = previous->next;

	previous->next = curr->next;
	free(curr);

	return EXIT_SUCCESS;

}
int PrintP(char* name, Position first)
{
	printf(" %s = ", name);
	if (first) {
		if (first->eksponent < 0) {
			if (first->koeficijent == 1) {
				printf("x^(%d) ", first->eksponent);
			}
			else {
				printf("%dx^(%d) ", first->koeficijent, first->eksponent);
			}
		}
		else {
			if (first->koeficijent == 1) {
				printf("x^(%d) ", first->eksponent);
			}
			else {
				printf("%dx^(%d) ", first->koeficijent, first->eksponent);
			}
		}
	}

	first = first->next;

	for (; first != NULL; first = first->next)
	{
		if (first->koeficijent < 0)
		{
			if (first->eksponent < 0)
			{
				printf(" - %dx^(%d) ", abs(first->koeficijent), first->eksponent);
			}
			else
			{
				printf(" - %dx^%d ", abs(first->koeficijent, first->eksponent));
			}
		}
		else
		{
			if (first->eksponent < 0)
			{
				if (first->koeficijent == 1)
				{
					printf(" + x^(%d) ", first->eksponent);
				}
				else
				{
					printf(" + %dx^(%d) ", first->koeficijent, first->eksponent);
				}

			}
			else
			{
				if (first->koeficijent == 1)
				{
					printf(" + x^(%d) ", first->eksponent);
				}
				else
				{
					printf(" + %dx^(%d) ", first->koeficijent, first->eksponent);
				}
			}
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}
int CreateandInsertAfter(int koeficijent, int eksponent, Position position)
{
	Position newP = CreateP(koeficijent, eksponent);
	if (!newP)
	{
		return EXIT_FAILURE;
	}

	InsertAfter(position, newP);
	position = position->next;

	return EXIT_SUCCESS;
}
int AddP1(Position resultHead, Position head1, Position head2)
{
	Position i = head1->next;
	Position j = head2->next;
	Position k = resultHead;
	Position temp = NULL;

	while (i->next != NULL && j->next != NULL)
	{
		if (i->eksponent == j->eksponent)
		{
			CreateandInsertAfter(i->koeficijent + j->koeficijent, i->eksponent, k);
			i = i->next;
			j = j->next;
		}
		else if (i->eksponent < j->eksponent)
		{
			CreateandInsertAfter(i->koeficijent, i->eksponent, k);
			i = i->next;
		}
		else
		{
			CreateandInsertAfter(j->koeficijent, j->eksponent, k);
			j = j->next;
		}
	}
	if (i == NULL)
	{
		temp = j;
	}
	else
	{
		temp = i;
	}
	while (temp != NULL)
	{
		CreateandInsertAfter(temp->koeficijent, temp->eksponent, k);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}
int AddP2(Position resultHead, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		Position newP = CreateP(i->koeficijent, i->eksponent);
		if (!newP)
		{
			return EXIT_FAILURE;
		}

		SortedInput(resultHead, newP);
	}
	for (j = head2->next; j != NULL; j = j->next)
	{
		Position newP = CreateP(j->koeficijent, j->eksponent);
		if (!newP)
		{
			return EXIT_FAILURE;
		}

		SortedInput(resultHead, newP);
	}
	return EXIT_SUCCESS;
}
int MultiplyP(Position resultHead, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			Position newP = CreateP(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);
			if (!newP)
			{
				return EXIT_FAILURE;
			}
			SortedInput(resultHead, newP);
		}
	}
	return EXIT_SUCCESS;
}
int FreeMemory(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		DeleteAfter(temp);
	}
	return EXIT_SUCCESS;
}