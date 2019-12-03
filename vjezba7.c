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
int pop(Pozicija);
int push(Pozicija, int);
int unos(char*, Pozicija);
int racunaj(Pozicija, Pozicija);

int main() {

	clan head, stog;
	head.next = NULL;
	stog.next = NULL;
	char* fileName = NULL;
	fileName = naziv(fileName);
	unos(fileName, &head);
	racunaj(&head, &stog);
	printf("%d", head.next->el);
	//ispis(stog.next);

	return 0;
}

int pop(Pozicija p) {

	int priv = 0;
	Pozicija q = NULL;
	q = p->next;
	priv = p->next->el;
	p->next = p->next->next;
	free(q);
	return priv - 48;
}

int pushStog(Pozicija p, int x) {
	
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	q->el = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int push(Pozicija p, int x) {

	Pozicija q = NULL;
	while (p->next != NULL)p = p->next;
	q = (Pozicija)malloc(sizeof(clan));
	q->el = x;
	//printf("%d", q->el);
	q->next = p->next;
	p->next = q;
	return 0;
}

int racunaj(Pozicija p, Pozicija stog) {

	Pozicija head = p;
	int a, b;

	while (p->next != NULL) {
		while(p->next->el >= '0' && p->next->el <= '9') p = p->next;
			
		switch (p->next->el) {
			case '*':
				a = pop(head);
				b = pop(head);
				pop(head);
				pushStog(head, a * b);
				break;
			case '+':
				a = pop(head);
				b = pop(head);
				pop(head);
				pushStog(head, a + b);
				break;
		}
		if (head->next->next != NULL)p = p->next;
		else break;
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
	if(head == NULL)printf("kurac");
	printf("%d ", head->el);
	return 0;
}
