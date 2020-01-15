/*Napisati kod koji za zadane podatke studenata (mati�ni broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
klju� ra�una da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim ra�una
ostatak cjelobrojnog dijeljenja te vrijednosti s veli�inom tablice. Studenti s istim
klju�em se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem klju�u se nalaze
koji podaci) te ponuditi mogu�nost da se za odre�enog studenta (prezime i ime) ispi�e
njegov mati�ni broj.*/

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