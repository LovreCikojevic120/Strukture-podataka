//Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat.Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;

typedef struct Clan {

	char el;
	Pozicija next;
}clan;

char* naziv(char*);
int ispis(Pozicija);
int unos(char*, Pozicija);

int main() {

	clan head;
	head.next = NULL;
	char* fileName = NULL;
	fileName = naziv(fileName);
	unos(fileName, &head);
	ispis(head.next);

	return 0;
}

char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

int unos(char* fileName, Pozicija p) {

	FILE* f = NULL;
	Pozicija q = NULL;
	f = fopen(fileName, "r");
	while (!feof(f)){

		q = (Pozicija)malloc(sizeof(clan));
		fscanf(f, " %c", &q->el);

		while (p->next != 0)
			p = p->next;

		q->next = p->next;
		p->next = q;
	}
	fclose(f);

	return 0;
}

int ispis(Pozicija head) {

	while (head->next != NULL) {
		printf("%c", head->el);
		head = head->next;
	}

	return 0;
}
