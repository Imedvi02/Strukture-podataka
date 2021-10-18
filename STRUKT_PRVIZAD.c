#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
} student;

int ProcitajBrojRedakaizDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke);
double MaksimalanBrojBodova(student* s, int brojStudenata);

int main()
{
    int brojStudenata = 0;
    int brojac = 0;
    student* s = NULL;
    double maxBrojBodova = 0;
    char* nazivDatoteke = "studenti.txt";

    brojStudenata = ProcitajBrojRedakaizDatoteke(nazivDatoteke);
    s = AlocirajMemorijuIProcitajStudente(brojStudenata, nazivDatoteke);
    maxBrojBodova = MaksimalanBrojBodova(s, brojStudenata);

    for (brojac = 0; brojac < brojStudenata; brojac++) {
        printf(" %s\t%s\t%lf\t%lf\n", s[brojac].ime, s[brojac].prezime, s[brojac].bodovi, s[brojac].bodovi / maxBrojBodova * 100);
    }

    return 0;
}

int ProcitajBrojRedakaizDatoteke(char* nazivDatoteke) {
    int brojac = 0;
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = { 0 };

    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka) {
        printf("Greska!\n");
        return -1;
    }
    while (!feof(datoteka)) {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke) {
    int brojac = 0;
    FILE* datoteka = NULL;
    student* studenti = NULL;

    studenti = (student*)malloc(brojStudenata * sizeof(student));
    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka) {
        printf("Greska alociranja!\n");
        free(studenti);
        return NULL;
    }
    while (!feof(datoteka)) {
        fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);
    return studenti;
}
double MaksimalanBrojBodova(student* s, int brojStudenata) {
    int brojac = 0;
    double maxBrojBodova = 0;

    for (brojac = 0; brojac < brojStudenata; brojac++) {
        if (s[brojac].bodovi > maxBrojBodova)
            maxBrojBodova = s[brojac].bodovi;
    }

    return maxBrojBodova;

}
