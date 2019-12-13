/*  Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
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
Pozicija vratise(PozicijaStog);

int main() {

	clan stablo, priv;
	char imedirektorija[10];
	Pozicija trenutni = &stablo;
	stog stog;
	int i = 0, izbor = 0;
	stablo.child = NULL;
	stablo.next = NULL;
	stablo.root = 1;
	printf("unesi ime roota: ");
	scanf(" %s", stablo.ime);
	stog.next = NULL;
	push(&stog, &stablo);

	while (1) {

		printf("\n1-unos\t2-prijelaz u poddirektorij\t3-ispis poddir.\t4-vrati se\t5-izlaz\n");
		scanf(" %c", &izbor);

		switch (izbor) {
		case '1':
			unos(trenutni);
			break;

		case '2':
			trenutni = pomak(trenutni, &stog);
			IspisStoga(stog.next);
			break;

		case '3':
			ispisPoddir(trenutni); break;
		
		case '4':
			trenutni = vratise(&stog);
			IspisStoga(stog.next); 
			break;

		case '5':
			return 0;
		}
	}
	return 0;
}

Pozicija vratise(PozicijaStog s) {

	Pozicija p = pop(s);
	return p;
}

int ispisPoddir(Pozicija p) {

	puts("poddirektoriji:");
	p = p->child;
	printf("%s\n", p->ime);
	p = p->next;

	while (p != NULL) {
		printf("%s\n", p->ime);
		p = p->next;
	}
}

int unos(Pozicija p) {
	Pozicija q = NULL;
	int i = 0;
	char naziv[20];
	printf("\nunesi naziv novog direktorija\n");
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

	puts("napisi ime direktorija u kojeg zelis uc");
	scanf("%s", imedirektorija);


	p = stablo;
	p = p->child;
	while (p != NULL) {
		if (!strcmp(imedirektorija, p->ime)) {
			//stablo = p;
			push(stog, p);
			return stablo->child;
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

	Pozicija priv = NULL;
	PozicijaStog q = NULL;
	while (p->next->next != NULL)p = p->next;
	//if (p->next->next == NULL) {
	if(p->next->adresa->root != 1){
		q = p->next;
		priv = p->adresa;
		p->next = NULL;
		free(q);
		return priv;
	}
	else {
		puts("na rootu si debilu >:(");
		return p;
	}
	/*else if (p->next == NULL) {
		q = p->next;
		priv = p->adresa;
		p->next = NULL;
		free(q);
		return priv;
	}*/
}

int IspisStoga(PozicijaStog p) {

	while (p != NULL) {
		if(p->adresa->root) printf("%s", p->adresa->ime);
		else printf(" :\\ %s", p->adresa->ime);
		p = p->next;
	}
	printf(">");
}
