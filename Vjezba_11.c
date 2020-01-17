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
	lista* hashListe;
}hashT;

//funkcije
hashTabPoz inic(int);
int dodaj(hashTabPoz);
int unos(poz);
int kljuc(poz);
int ispisTablice(hashTabPoz);
int sorter(char*, char*);

int main() {

	int x = 0;
	hashTabPoz hashTablica = NULL;
	hashTablica = inic(11);
	do {
		printf("\nZa dodat upisi 1, za ispis 2, za trazenje maticnog broja 3, za kraj 4\n");
		scanf("%d", &x);
		switch (x) {
		case 1:	dodaj(hashTablica);
			break;

		case 2:	ispisTablice(hashTablica);
			break;

		case 3:	nadiLika(hashTablica);
			break;

		case 4:	return 0;
		}
	} while (x != 4);
	return 0;
}

int sorter(char* p1, char* p2) {

	int i = 0;
	while (p1[i] != '\0' && p2[i] != '\0') {
		if (p1[i] > p2[i])return 1;
		else if (p1[i] == p2[i])i++;
		else return -1;
	}
	return 0;
}

int nadiLika(hashTabPoz hash) {

	lista pathFinder = NULL;
	poz p = (poz)malloc(sizeof(cvor));
	if (p == NULL)return 0;
	printf("\nupisi ime i prezime\n");
	scanf("%s %s", &p->ime, &p->prezime);
	p->kljuc = kljuc(p);
	pathFinder = hash->hashListe[p->kljuc];
	while (pathFinder != NULL) {
		if (!sorter(pathFinder->ime, p->ime) && !sorter(pathFinder->prezime, p->prezime))break;
		pathFinder = pathFinder->next;
	}
	if (pathFinder == NULL)return 0;

	printf("Maticni broj trazene osobe je: %d", pathFinder->matBroj);

	return 0;

}


int ispisTablice(hashTabPoz hash) {

	lista printer = NULL;
	int i = 0, br = 0, mb = 0;
	char c = NULL;
	printf("zelis li ispisati i maticni broj? (d/n)\n");
	scanf(" %c", &c);
	if (c == 'd') mb++;
	else if (c == 'n') mb = 0;
	else { 
		printf("krivi unos!\n");
		return 0; 
	}

	for (i = 0; i < 11; i++) {
		br = 0;
		printer = hash->hashListe[i];
		while (printer != NULL) {
			if (!br) {
				printf("\nIndex %d: %s %s", i, printer->ime, printer->prezime);
				if (mb) printf(" %d", printer->matBroj);
				br++;
			}
			else {
				printf(" , %s %s", printer->ime, printer->prezime);
				if (mb) printf(" %d", printer->matBroj);
			}
			printer = printer->next;
		}
	}
	return 0;
}

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
	poz p = NULL, temp = NULL;
	int Kljuc = 0;
	printf("Upisi stop za kraj unosa\n");

	while (1) {
		
		target = NULL;
		p = (poz)malloc(sizeof(cvor));
		p->next = NULL;
		printf("Ime, prezime, maticni broj:\n");
		scanf(" %s", &p->ime);
		if (!strcmp(p->ime, "stop")) break;

		scanf(" %s %d", &p->prezime, &p->matBroj);

		Kljuc = kljuc(p);

		target = hash->hashListe[Kljuc];

		if (target == NULL) {

			hash->hashListe[Kljuc] = p;
		}

		else if ((strcmp(p->prezime, target->prezime) < 0 || (strcmp(p->prezime, target->prezime) == 0) && strcmp(p->ime, target->ime) < 0)) {
				p->next = target;
				hash->hashListe[Kljuc] = p;
		}

		else{
				while (target->next != NULL && (strcmp(p->prezime, target->next->prezime) > 0))
					target = target->next;

				if (strcmp(p->prezime, target->next->prezime) == 0)
					while (target->next != NULL && strcmp(p->prezime, target->next->prezime) == 0 && strcmp(p->ime, target->ime) < 0)
						target = target->next;

				temp = target->next;
				target->next = p;
				p->next = temp;
		}
	}
	return 0;
}

hashTabPoz inic(int size) {

	int i = 0;
	hashTabPoz h = NULL;
	h = (hashTabPoz)malloc(sizeof(hashT));
	if (h == NULL) {
		printf("Greska u alokaciji!\n");
		return 0;
	}
	h->tabSize = size;
	h->hashListe = (lista*)malloc(h->tabSize * sizeof(lista));
	if (h->hashListe == NULL) {
		printf("Greska\n");
		return 0;
	}

	for (i = 0; i < h->tabSize; i++) {

		h->hashListe[i] = NULL;
	}

	return h;
}
