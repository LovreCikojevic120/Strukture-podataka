//stog i red

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>


typedef struct Clan* Pozicija;

typedef struct Clan {

	int el;
	Pozicija next;
}clan;

int push(Pozicija);
int popStog(Pozicija);
int popRed(Pozicija);
int nasumicni(Pozicija);
int ispis(Pozicija);

int main() {

	int select = 0;
	clan Head;
	Head.next = NULL;
	do {
		printf("\nza push 0, za pop stog 1, za pop red 2, za kraj 3\n");
		scanf("%d", &select);
		if (select == 0)push(&Head);
		if (select == 1)popStog(&Head);
		if (select == 2)popRed(&Head);
	} while (select != 3);

	return 0;
}

int nasumicni(Pozicija p) {

	srand((unsigned)time(0));
	p->el = rand() % 91 + 10;
	return 0;
}

int push(Pozicija p) {

	int i = 0;
	Pozicija head = p;
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	nasumicni(q);
	q->next = p->next;
	p->next = q;
	ispis(head->next);
	return 0;
}

int popRed(Pozicija p) {

	Pozicija head = p;
	if (p->next == NULL) {
		printf("Lista je prazna!\n");
		return 0;
	}
	while (p->next->next != NULL) {
		p = p->next;
	}
	free(p->next);
	p->next = NULL;
	ispis(head->next);
	return 0;
}

int popStog(Pozicija p) {

	Pozicija head = p;
	if (head->next == NULL) {
		printf("Lista je prazna!\n");
		return 0;
	}
	p->next = p->next->next;
	ispis(head->next);
	return 0;
}

int ispis(Pozicija p) {
	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	return 0;
}


