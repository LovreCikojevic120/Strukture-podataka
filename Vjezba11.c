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