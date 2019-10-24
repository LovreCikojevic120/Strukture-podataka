#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LENGTH 1024

typedef struct {

	char ime[20];
	char prezime[20];
	int bodovi;
	float rel_bod;
}Student;

char* naziv(char*);
int brojStud(char*);
int unos(char*, Student*, int);
int prosjek(Student*, int);
int ispis(Student*, int);
Student* alokacija(char*, Student*, int);


int main() {

	int br = 0;
	char* fileName = NULL;
	Student* student = NULL;

	fileName = naziv(fileName);
	
	br = brojStud(fileName);

	student = alokacija(fileName, student, br);
	unos(fileName, student, br);
	ispis(student, br);
	return 0;
}

char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	memset(fileName, '\0', MAX_LENGTH);
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

Student* alokacija(char* fileName, Student* student, int br) {

	FILE* f = NULL;
	f = fopen(fileName, "r");
	student = (Student*)malloc(br * sizeof(Student));
	fclose(f);
	return student;

}

int brojStud(char* fileName) {

	int br = 0;
	char temp[MAX_LENGTH] = { 0 };
	FILE* f = NULL;
	f = fopen(fileName, "r");

	while (!feof(f)) {

		fgets(temp, MAX_LENGTH, f);
		if (strlen(temp) == 0) continue;
		br++;
	}
	fclose(f);
	return br + 1;
}

int unos(char* fileName, Student* student, int br) {

	int i = 0;
	FILE* f = NULL;
	f = fopen(fileName, "r");
	for (i = 0; i < br; i++) {

		fscanf(f, "%d %s %s", &student[i].bodovi, student[i].ime, student[i].prezime);
	}
	fclose(f);

	return 0;
}

int prosjek(Student* student, int br) {

	int i = 0;
	int max = student[0].bodovi;
	for (i = 0; i < br; i++) {
		if (student[i].bodovi > max)max = student[i].bodovi;
	}
	return max;
}

int ispis(Student* student, int br) {

	int i = 0;
	for (i = 0; i < br - 1; i++) {
		student[i].rel_bod = (float)student[i].bodovi / prosjek(student, br) * 100;
		printf("%d %.2f %s %s\n", student[i].bodovi, student[i].rel_bod, student[i].ime, student[i].prezime);
	}
	return 0;
}
