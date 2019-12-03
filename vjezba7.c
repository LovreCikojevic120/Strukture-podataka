//Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna rezultat.Stog je potrebno realizirati preko vezane liste.

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
int racunaj(Pozicija);

int main() {

	clan head, stog;
	head.next = NULL;
	stog.next = NULL;
	char* fileName = NULL;
	fileName = naziv(fileName);
	unos(fileName, &head);
	racunaj(&stog);
	ispis(head.next);

	return 0;
}

int pop(Pozicija p) {


}

int push(Pozicija p, int x) {
	
	Pozicija q = NULL;
	while (p->next != NULL)p = p->next;
	q = (Pozicija)malloc(sizeof(clan));
	q->el = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int racunaj(Pozicija p, Pozicija stog) {
	
	Pozicija head = p;
	while (p->next != NULL) {
		if(p->next->el >= '0' && p->next->el <= '9')push(stog, p->next->el);
		if (p->next->el == '*' || p->next->el == '+') {
			pop(stog, p->next->el);
		}
	}
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
	while (!feof(f)) {

		q = (Pozicija)malloc(sizeof(clan));
		fscanf(f, "%c", &q->el);

		while (p->next != NULL)
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