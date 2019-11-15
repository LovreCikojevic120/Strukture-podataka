//Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna rezultat.Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;


typedef struct Clan {

	int el;
	Pozicija next;
}clan;

char* naziv(char*);
int ispis(Pozicija);
//int unos(char*, Pozicija);
int sort(char*, Pozicija);
int Brisi(Pozicija);
int pop(Pozicija);
int push(int, Pozicija);

int main() {
	
	clan head;
	head.next = NULL;
	char* fileName = NULL;
	fileName = naziv(fileName);
	sort(fileName, &head);
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

int ispis(Pozicija head) {

	while (head->next != NULL) {
		printf("%c", head->el);
		head = head->next;
	}

	return 0;
}

int sort(char* fileName, Pozicija head) {

	Pozicija p = head, q=NULL;
	FILE* f = NULL;
	char z = 0, r = 0;
	f = fopen(fileName, "r");
	p = p->next;

	while (!feof(f)) {

		fscanf(f, " %c", &r);
		p = (Pozicija)malloc(sizeof(clan));
		if (r >= '0' && r <= '9') {
			z = (int)r;
			push(z, head);
		}
		else {
			int x = pop(p), y = pop(p);
			switch (z) {
			case'+': push(y + x, head); break;
			case'-': push(y - x, head); break;
			case'*': push(y * x, head); break;
			case'/': push(y / x, head); break;
			}
		}
		p = p->next;
	}
	return 0;
}

int push(int x, Pozicija head) {
	Pozicija p = head->next, q = NULL;
	while (p != NULL)
		p = p->next;
	q = (Pozicija)malloc(sizeof(clan));
	q = q->next;
	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}

int pop(Pozicija head) {
	int x;
	Pozicija p = head;
	x = p->next->el;
	Brisi(p);
	return x;
}

int Brisi(Pozicija head) {
	Pozicija priv, p = head;
	priv = p->next;
	p->next = p->next->next;
	free(priv);

	return 0;
}