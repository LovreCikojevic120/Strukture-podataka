/*  Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.   */


#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;
typedef struct Stog* PozicijaStog;

typedef struct Clan {

	char ime[20];
	int root;
	Pozicija next;
	Pozicija child;
}clan;

typedef struct Stog {
	Pozicija adresa;
	PozicijaStog next;
}stog;

int unos(Pozicija);
Pozicija pomak(Pozicija, PozicijaStog);
int IspisStoga(PozicijaStog);
Pozicija pop(PozicijaStog);
int push(PozicijaStog, Pozicija);
Pozicija vratiSe(PozicijaStog);

int main() {

	clan stablo, priv;
	char imedirektorija[10];
	Pozicija trenutni = &stablo;
	stog stog;
	int i = 0;
	char izbor[20];
	stablo.child = NULL;
	stablo.next = NULL;
	stablo.root = 1;
	printf("Unesi ime roota: ");
	scanf(" %s", stablo.ime);
	stog.next = NULL;
	push(&stog, &stablo);

	while (1) {

		printf("\n\nmd-unos\t   cd-prijelaz u poddirektorij\t  dir-ispis poddirektorija\t  cd..-vrati se\t\texit-izlaz\n\n");
		IspisStoga(stog.next);
		scanf(" %s", &izbor);

		if(!strcmp(izbor, "md"))
			unos(trenutni);

		else if(!strcmp(izbor, "cd")){
			trenutni = pomak(trenutni, &stog);
			IspisStoga(stog.next);
		}

		else if(!strcmp(izbor, "dir"))
			ispisPoddir(trenutni);

		else if(!strcmp(izbor, "cd..")){
			trenutni = vratiSe(&stog);
			IspisStoga(stog.next);
		}

		else if(!strcmp(izbor, "exit"))
			return 0;

        else puts("Pogresan unos.");
		}

	return 0;
}

Pozicija vratiSe(PozicijaStog s) {

	Pozicija p = pop(s);
	return p;
}

int ispisPoddir(Pozicija p) {

	puts("Poddirektoriji:");
	p = p->child;
	if(p == NULL){ 
		puts("prazno");
		return 0;
	}
	printf("%s\n", p->ime);
	p = p->next;

	while (p != NULL) {
		printf("%s\n", p->ime);
		p = p->next;
	}
	return 0;
}

int unos(Pozicija p) {
	Pozicija q = NULL;
	int i = 0;
	char naziv[20];
	scanf("%s", naziv);
	q = (Pozicija)malloc(sizeof(clan));
	strcpy(q->ime, naziv);
	if (p->child == NULL) {
		p->child = q;
		q->next = NULL;
		q->root = 0;
		q->child = NULL;
	}
	else {
		p = p->child;

		while (p->next != NULL)  p = p->next;
		q->next = p->next;
		p->next = q;
		q->child = NULL;
		q->root = 0;
	}

	return 0;
}

Pozicija pomak(Pozicija p, PozicijaStog stog) {
	Pozicija stablo = p;
	char imedirektorija[20];

	scanf("%s", imedirektorija);


	p = stablo;
	p = p->child;
	while (p != NULL) {
		if (!strcmp(imedirektorija, p->ime)) {
			push(stog, p);
			return p;
		}

		else p = p->next;
	}

}

int push(PozicijaStog p, Pozicija x) {

	PozicijaStog q = NULL;
	while (p->next != NULL) p = p->next;
	q = (PozicijaStog)malloc(sizeof(stog));
	q->adresa = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

Pozicija pop(PozicijaStog p) {

	PozicijaStog priv = p;
	PozicijaStog q = NULL;
	while (p->next->next != NULL)p = p->next;
	if(p->next->adresa->root != 1){
		q = p->next;
		priv = p->adresa;
		p->next = NULL;
		free(q);
		return priv;
	}
	else {
		puts("Nalazite se na root-u.");
		return p->next->adresa;
	}
}

int IspisStoga(PozicijaStog p) {

	while (p != NULL) {
		if(p->adresa->root) printf("%s", p->adresa->ime);
		else printf(" :\\ %s", p->adresa->ime);
		p = p->next;
	}
	printf(">");
}
