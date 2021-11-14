#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	double number;
	Position next;
}Element;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int DeleteAll(Position position);
int Push(Position head, double number);
int Pop(double* Resultdestination, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixfromFile(double* Resultdestination, char* filename);

int main(int argc, char* argv[])
{
	double result = 0;

	if (argc == 1)
	{
		if (CalculatePostfixfromFile(&result, "postfix.txt") == EXIT_SUCCESS)
		{
			printf("Rezultat: %0.1lf", result);
		}
		else if (CalculatePostfixfromFile(&result, argv[1]) == EXIT_SUCCESS)
		{
			printf("Rezultat: %0.1lf", result);
		}
	}
	return EXIT_SUCCESS;
}
Position CreateElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Element));
	if (!newElement)
	{
		perror("Greska u alociranju memorije!");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}
int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;

}
int DeleteAfter(Position position)
{
	Position temp = NULL;

	temp = position->next;
	if (!temp)
	{
		return EXIT_SUCCESS;
	}
	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}
int DeleteAll(Position head)
{
	while (head->next)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}
int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);
	if (!newElement)
	{
		return -1;
	}

	InsertAfter(head, newElement);

}
int Pop(double* Resultdestination, Position head)
{
	Position first = head->next;

	if (!first)
	{
		perror("Postfix nije uredu! Provjerite datoteku.");
		return -1;
	}

	*Resultdestination = first->number;
	DeleteAfter(head);

	return EXIT_SUCCESS;
}
int PerformOperation(Position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}
	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0)
		{
			perror("Nazivnik ne smije biti nula!");
			return -3;
		}
		result = operand1 / operand2;
		break;
	default:
		perror("Ova operacija ne postoji!");
		return -4;
		break;
	}

	return Push(head, result);
}
int CalculatePostfixfromFile(double* Resultdestination, char* filename)
{
	FILE* f = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numbOfbytes = 0;
	double number = 0; //bilo int number
	int status = 0;
	char operation = 0;
	Element head = { .number = 0, .next = NULL };

	f = fopen(filename, "rb");
	if (!f)
	{
		perror("Greska s datotekom!");
		return -4;
	}
	fseek(f, 0, SEEK_END);
	fileLength = ftell(f);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Nemoguce alocirati memoriju!");
		return -5;
	}
	rewind(f);
	fread(buffer, sizeof(char), fileLength, f);
	printf("|%s|\n", buffer);
	fclose(f);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numbOfbytes);
		if (status == 1)
		{
			status = Push(&head, number);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -6;
			}
			currentBuffer += numbOfbytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numbOfbytes);
			status = PerformOperation(&head, operation);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -7;
			}
			currentBuffer += numbOfbytes;
		}
	}
	free(buffer);
	status = Pop(Resultdestination, &head);
	if (status != EXIT_SUCCESS)
	{
		DeleteAll(&head);
		return -8;
	}

	if (head.next)
	{
		perror("Postfix nije uredu! Provjerite datoteku.");
		DeleteAll(&head);
		return -9;
	}
	return EXIT_SUCCESS;
}