/*  . Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke. */

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* Pozicija;

typedef struct osoba {
	char ime[20];
	char prezime[20];
	int godina;
	char inicijal;
	Pozicija next;
}_osoba;

Pozicija inic(Pozicija x) {
	x->inicijal = x->prezime[0];
	return x;
}

void UnosP(Pozicija p)
{
	Pozicija q = 0;
	printf("za kraj unesite 'stop'\n");
	while (1) {
		q = (Pozicija)malloc(sizeof(_osoba));
		printf("Ime, prezime, godina rodenja:\n");
		scanf(" %s", &q->ime);
		if (!strcmp(q->ime, "stop")) break;
		scanf(" %s %d", &q->prezime, &q->godina);
		inic(q);
		if (!strcmp(q->ime, "stop")) break;
		q->next = p->next;
		p->next = q;
	}
}

void Ispis(Pozicija p)
{
	printf("\nLista:\n");
	while (p != 0) {
		printf("\n%s %s %d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}
}

void UnosK(Pozicija p)
{
	Pozicija q = 0;
	printf("\nza kraj unesite 'stop'\n");
	while (1) {
		q = (Pozicija)malloc(sizeof(_osoba));
		printf("Ime, prezime, godina rodenja:\n");
		scanf(" %s", &q->ime);
		if (!strcmp(q->ime, "stop")) break;
		scanf(" %s %d", &q->prezime, &q->godina);
		inic(q);
		while (p->next != 0)
			p = p->next;
		q->next = p->next;
		p->next = q;
	}
}

void Trazi(Pozicija p)
{
	char unos[50] = { 0 };
	printf("\nUnesite prezime:\n");
	scanf(" %s", unos);

	while (strcmp(unos, p->prezime)) {
		p = p->next;
		if (p->next == NULL) {
			printf("\nOsoba nije u listi\n");
			break;
		}
	}
	printf("\n%s %s %d\n", p->ime, p->prezime, p->godina);

}

Pozicija TraziPret(char unos[], Pozicija p) {
	Pozicija Pret = p;
	p = p->next;
	while (p != NULL && strcmp(unos, p->ime)) {
		Pret = p;
		p = p->next;
	}
	if (NULL == p) return 0;
	else return Pret;
}

int Brisi(Pozicija p)
{
	Pozicija priv = 0;
	char unos[50] = { 0 };
	printf("\nUnesite ime osobe koju zelite obrisati iz liste\n");
	scanf(" %s", unos);
	p = TraziPret(unos, p);
	priv = p->next;
	p->next = p->next->next;
	free(priv);
	return 0;
}

void UnosIza(Pozicija p, char* prez)
{
	Pozicija q = 0;
	printf("\nza kraj unesite 'stop'\n");
	while (1) {
		q = (Pozicija)malloc(sizeof(_osoba));
		printf("Ime, prezime, godina rodenja:\n");
		scanf(" %s", &q->ime);
		if (!strcmp(q->ime, "stop")) break;
		scanf(" %s %d", &q->prezime, &q->godina);
		inic(q);
		while (strcmp(p->prezime, prez))
			p = p->next;
		q->next = p->next;
		p->next = q;
	}
}

void UnosIspred(Pozicija p, char* prez)
{
	Pozicija q = 0;
	printf("\nza kraj unesite 'stop'\n");
	while (1) {
		q = (Pozicija)malloc(sizeof(_osoba));
		printf("Ime, prezime, godina rodenja:\n");
		scanf(" %s", &q->ime);
		if (!strcmp(q->ime, "stop")) break;
		scanf(" %s %d", &q->prezime, &q->godina);
		inic(q);
		while (strcmp(p->prezime, prez))
			p = p->next;
		p->next->next = TraziPret(prez, p);
		q->next = p->next;
		p->next = q;
	}
}

void Sort(Pozicija p)
{
	Pozicija q = 0, pret = 0, priv = 0, kraj = 0;
	while (kraj != p->next) {
		pret = p;
		q = p->next;
		while (kraj != q->next) {
			if (q->inicijal > q->next->inicijal) {
				priv = q->next;
				pret->next = priv;
				q->next = priv->next;
				priv->next = q;
				q = priv;
			}
			pret = q;
			q = q->next;
		}
		kraj = q;
	}
}

char* Naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	memset(fileName, '\0', MAX_LENGTH);
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
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
	return br;
}


int CitaIzDat(char* fileName, Pozicija p, int br) {

	int i = 0;
	Pozicija q = 0;

	FILE* f = NULL;
	f = fopen(fileName, "r");

	for (i = 0; i < br; i++) {

		q = (Pozicija)malloc(sizeof(_osoba));

		fscanf(f, " %s %s %d", q->ime, q->prezime, &q->godina);
		inic(q);

		while (p->next != 0)
			p = p->next;

		q->next = p->next;
		p->next = q;
	}
	fclose(f);

	return 0;
}

int sortiraniUnos(Pozicija p) {

	int i = 0;
	Pozicija q = NULL, pret = NULL, priv = NULL, kraj = NULL, head = NULL;
	printf("\nza kraj unesite 'stop'\n");

	while (!i) {
		while (1) {
			head = p;
			q = (Pozicija)malloc(sizeof(_osoba));
			printf("Ime, prezime, godina rodenja:\n");
			scanf(" %s", &q->ime);
			if (!strcmp(q->ime, "stop")) {
				i++;
				break;
			}

			scanf(" %s %d", &q->prezime, &q->godina);
			inic(q);
			while (head->next != NULL)head = head->next;
			q->next = head->next;
			head->next = q;
			head = p;
		}
		while (head->next!=kraj) {
			pret = head;
			q = head->next;
			while (q->next != kraj) {
				if (q->inicijal > q->next->inicijal) {
					priv = q->next;
					pret->next = priv;
					q->next = priv->next;
					priv->next = q;
					q = priv;
				}
				pret = q;
				q = q->next;
			}
			kraj = q;
		}
	}
}

int UnosUDat(char* fileName, Pozicija p) {

	FILE* f = NULL;
	f = fopen(fileName, "w");

	while (NULL != p) {
		fprintf(f, "%s %s %d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}
	fclose(f);

	return 0;
}

int main()
{
	char c = 0, prez[20];
	char* fileName = 0;
	int br = 0;
	_osoba Head;
	Head.next = 0;

do {
	printf("\n1 - dinamicki dodaje novi element na pocetak liste\n2 - ispisuje listu\n3 - dinamicki dodaje novi element na kraj liste\n4 - pronalazi element u listi (po prezimenu)\n5 - brise odredeni element iz liste\n6 - dinamicki dodaje novi element");
	printf(" iza odredenog elementa\n7 - dinamicki dodaje novi element ispred odredenog elementa\n8 - sortiraj\n9 - sortirani unos\n\nc- citanje liste iz datoteke\nu - unos u datoteku\nk - kraj\n");
	scanf(" %c", &c);
	switch (c) {
	case '1':   UnosP(&Head); break;
	case '2':   Ispis(Head.next); break;
	case '3':   UnosK(&Head); break;
	case '4':   Trazi(&Head);  break;
	case '5':   Brisi(&Head);  break;
	case '6':
		printf("Unesite prezime osobe iza koje treba dodati novi element:\t");
		scanf(" %s", prez);
		UnosIza(&Head, prez);
		break;
	case '7':
		printf("Unesite prezime osobe ispred koje treba dodati novi element:\t");
		scanf(" %s", prez);
		UnosIspred(&Head, prez);
		break;
	case '8':   Sort(&Head);  break;
	case '9': 
		printf("\n**Sortirani unos**\n\n");
		sortiraniUnos(&Head); break;
	case 'c':
		fileName = Naziv(fileName);
		br = brojStud(fileName);
		CitaIzDat(fileName, &Head, br);
		break;
	case 'u':
		fileName = Naziv(fileName);
		UnosUDat(fileName, Head.next);
		break;
	case 'k':   return 0;

	}
} while(1);
}
