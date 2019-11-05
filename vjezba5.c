#define _CRT_SECURE_NO_WARNINGS

/*Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1UL2,
b) L1VL2.
Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;

typedef struct Clan {

	int el;
	Pozicija next;
}clan;

int brisi(Pozicija, Pozicija);
int unesi(Pozicija, int);
int upis(Pozicija);
int unija(Pozicija, Pozicija, Pozicija);
int presjek(Pozicija, Pozicija, Pozicija);
int ispis(Pozicija);
Pozicija traziPret(Pozicija, Pozicija);

int main() {

	clan Lista1;
	clan Lista2;
	clan Presjek;
	clan Unija;
	Lista1.next = NULL;
	Lista2.next = NULL;
	Presjek.next = NULL;
	Unija.next = NULL;

	upis(&Lista1);
	upis(&Lista2);
	presjek(&Lista1, &Lista2, &Presjek);
	unija(&Lista1, &Lista2, &Unija);
	printf("\nPresjek:\n");
	ispis(Presjek.next);
	printf("\nUnija:\n");
	ispis(Unija.next);

	return 0;
}

Pozicija traziPret(Pozicija head, Pozicija clan) {

	Pozicija p = head->next, q = head;
	while (p != NULL && p->el != clan->el) {
		q = p;
		p = p->next;
	}
	if (p == NULL) return 0;
	return q;
}

int upis(Pozicija head) {

	int br = 0, el = 0;
	printf("Koliko clanova?\n");
	scanf("%d", &br);
	for (int i = 0; i < br; i++) {
		printf("%d. clan:", i + 1);
		scanf("%d", &el);
		unesi(head, el);
	}
	return 0;
}

int brisi(Pozicija head, Pozicija a) {
	Pozicija temp = NULL, x = a;
	x = traziPret(head, a);
	temp = x->next;
	if (a->next == NULL) x->next = NULL;
	else x->next = x->next->next;
	free(temp);
	return 0;
}

int unesi(Pozicija head, int x) {

	Pozicija p = head, q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	while (p->next != NULL) {
		p = p->next;
	}
	q->el = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int unija(Pozicija lista1, Pozicija lista2, Pozicija unija) {

	Pozicija L1 = lista1, L2 = lista2, u = unija;
	while (L1->next != NULL && L2->next != NULL) {
		if (L1->next->el == L2->next->el) {
			brisi(lista2, L2->next);
			if (L2->next == NULL)break;
			L2 = L2->next;
		}
		else {
			L2 = L2->next;
		}
		if (L2->next == NULL) {
			L1 = L1->next;
			L2 = lista2;
		}

	}
	
	u->next = lista1->next;
	while (u->next != NULL)u = u->next;
	u->next = lista2->next;
	return 0;
}

int presjek(Pozicija lista1, Pozicija lista2, Pozicija presjek) {
	Pozicija L1 = lista1, L2 = lista2, p = presjek, prethodni = NULL, brisac = NULL;
	while (L1->next != NULL && L2->next != NULL) {
		if (L1->next->el == L2->next->el) {
			unesi(presjek, L2->next->el);
			L2 = L2->next;
		}
		else {
			L2 = L2->next;
		}
		if (L2->next == NULL) {
			L1 = L1->next;
			L2 = lista2;
		}
	}
	return 0;
}

int ispis(Pozicija p) {

	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	return 0;
}
