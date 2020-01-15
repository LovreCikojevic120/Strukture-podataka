/*Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Studenti s istim
ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct Cvor* poz;
typedef struct Cvor* lista;
typedef struct HashTab* hashTabPoz;

typedef struct Cvor {

	char* ime;
	char* prezime;
	int matBroj;
	poz next;
}cvor;

typedef struct HashTab {

	int tabSize;
	lista* hashListe;
}hashT;

int main() {


	return 0;
}

poz Trazi(int x, hashTab H){
    lista L;
    
    L = H->hashListe[Preslikavanje(x, H->11)];
    
    while( l != NULL && l->kljuc != x)  l = l->next;
    
    return l;
}


int sortiraniUnos(lista p) {

	int i = 0, zbroj = 0;
	lista q = NULL;
	printf("\nza kraj unesite 'stop'\n");

		while (1) {
			q = (lista)malloc(sizeof(cvor));
			printf("Ime, prezime, godina rodenja:\n");
			scanf(" %s", &q->ime);
			if (!strcmp(q->ime, "stop")) break;

			scanf(" %s %d", &q->prezime, &q->godina);

			kljuc(q);
		}
}
int kljuc(poz q){
    int i = 0, zbroj = 0;
    for(i=0;i<5;i++){
        if (*(q->prezime + i) == '\0') break;
        zbroj += *(q->prezime + i);
        }
    q->kljuc = zbroj%11;
    
    return q->kljuc;
}
