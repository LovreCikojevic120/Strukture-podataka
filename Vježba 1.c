#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct {

	char ime[20];
	char prezime[20];
	int bodovi;
	float rel_bod;
}Student;

int brojStud(FILE*);
int unos(FILE*, Student*, int);
int prosjek(FILE*, Student*, int);
int ispis(FILE*, Student*, int);
Student* alokacija(FILE*, Student*, int);


int main() {

	int br = 0;
	Student* student = NULL;
	FILE* studenti;
	studenti = fopen("studenti.txt", "r");

	br = brojStud(studenti);

	student = alokacija(studenti, student, br);
	unos(studenti, student, br);
	ispis(studenti, student, br);
	fclose(studenti);
	return 0;
}

Student * alokacija(FILE* studenti, Student* student, int br) {

	student = (Student*)malloc(br * sizeof(Student));
	return student;

}

int brojStud(FILE* studenti) {

	int br = 0;
	while (!feof(studenti)) {

		if (fgetc(studenti) == '\n') br++;
	}

	rewind(studenti);

	return br;
}

int unos(FILE* studenti, Student* student, int br) {

	int i = 0;
	for (i = 0; i < br; i++) {

		fscanf(studenti, "%d %s %s", &student[i].bodovi, student[i].ime, student[i].prezime);
	}

	return 0;
}

int prosjek(FILE* studenti, Student* student, int br) {

	int i = 0;
	int max = student[0].bodovi;
	for (i = 0; i < br; i++) {
		if (student[i].bodovi > max)max = student[i].bodovi;
	}
	return max;
}

int ispis(FILE* studenti, Student* student, int br) {

	int i = 0;
	for (i = 0; i < br-1; i++) {
		student[i].rel_bod = (float)student[i].bodovi / prosjek(studenti, student, br) * 100;
		printf("%d %.2f %s %s\n", student[i].bodovi, student[i].rel_bod, student[i].ime, student[i].prezime);
	}
	return 0;
}
