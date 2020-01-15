/*Napisati kod koji za zadane podatke studenata (matièni broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim raèuna
ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Studenti s istim
kljuèem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem kljuèu se nalaze
koji podaci) te ponuditi moguænost da se za odreðenog studenta (prezime i ime) ispiše
njegov matièni broj.*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Cvor* poz;
typedef struct Cvor* lista;
typedef struct HashTab* hashTabPoz;

typedef struct Cvor {

	char ime[10];
	char prezime[20];
	int matBroj;
	int kljuc;
	poz next;
}cvor;

typedef struct HashTab {

	int tabSize;
	int index;
	lista* hashListe;
}hashT;

//funkcije
hashTabPoz inic(int);
int dodaj(hashTabPoz);
int unos(poz);
int kljuc(poz);
int ispisTablice(hashTabPoz);
int sortiraj(void*, void*);

int main() {

	int i;
	hashTabPoz hashTablica = NULL;
	hashTablica = inic(11);
	dodaj(hashTablica);
	/*for (i = 0; i < hashTablica->tabSize; i++) {
		qsort(hashTablica->hashListe[i], 2, sizeof(cvor), sortiraj);
	}*/
	ispisTablice(hashTablica);
	return 0;
}

int sortiraj(void* p1, void* p2) {

	poz lik1 = p1;
	poz lik2 = p2;
	return strcmp(lik1->ime, lik2->ime);
}

int ispisTablice(hashTabPoz hash) {
	
	lista printer = NULL;
	int i = 0;
	for (i = 0; i < 11; i++) {
		printer = hash->hashListe[i];
		while (printer != NULL) {
			printf("Index:%d\t%s %s %d\n", i, printer->ime, printer->prezime, printer->matBroj);
			printer = printer->next;
		}
	}
	return 0;
}

/*int unos(poz p) {

	int i = 0, zbroj = 0;
	lista q = NULL;
	printf("\nza kraj unesite 'stop'\n");

	while (1) {
		q = (poz)malloc(sizeof(cvor));
		printf("Ime, prezime, maticni broj:\n");
		scanf(" %s", &q->ime);
		if (!strcmp(q->ime, "stop")) { 
			free(q);
			break; 
		}

		scanf(" %s %d", &q->prezime, &q->matBroj);

		kljuc(q);	
	}
	return q;
}*/

int kljuc(poz q) {
	int i = 0, zbroj = 0;
	for (i = 0; i < 5; i++) {
		if (*(q->prezime + i) == '\0') break;
		zbroj += *(q->prezime + i);
	}
	q->kljuc = zbroj % 11;

	return q->kljuc;
}

int dodaj(hashTabPoz hash) {

	lista target = NULL;
	poz p = NULL;
	while (1) {
		p = (poz)malloc(sizeof(cvor));
		p->next = NULL;
		printf("Ime, prezime, maticni broj:\n");
		scanf(" %s", &p->ime);
		if (!strcmp(p->ime, "stop")) break;

		scanf(" %s %d", &p->prezime, &p->matBroj);

		kljuc(p);

		
		//p = unos(p);
		target = hash->hashListe[p->kljuc];

		while (!strcmp(target->prezime, p->prezime) && target != NULL)target = target->next;//while (target != NULL && target->matBroj != p->matBroj)target = target->next;
		if (target == NULL) {
			p->next = hash->hashListe[p->kljuc];
			hash->hashListe[p->kljuc] = p;
		}
		else if (target->prezime > p->prezime) {

			p->next = target->next;
			target->next = p;
		}
		else target = target->next;
	}
	return 0;
}

hashTabPoz inic(int size) {

	int i = 0;
	hashTabPoz h = NULL;
	h = (hashTabPoz)malloc(sizeof(hashT));
	if (h == NULL) {
		printf("Greska u alokaciji!\n");
		return -1;
	}
	h->tabSize = size;
	h->hashListe = (lista*)malloc(h->tabSize * sizeof(lista));
	if (h->hashListe == NULL) {
		printf("Greska\n");
		return -1;
	}

	for (i = 0; i < h->tabSize; i++) {

		h->hashListe[i] = NULL;
	}

	return h;
}