#define _CRT_SECURE_NO_WARNINGS

/*Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1UL2,
b) L1VL2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
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
	unija(&Lista1, &Lista2, &Unija);
	ispis(Unija.next);

	return 0;
}

Pozicija traziPret(Pozicija head, Pozicija clan) {
	Pozicija q = head;
	head = head->next;
	while (q != clan)q = q->next;

	return q;
}

int upis(Pozicija head) {

	int br = 0, el = 0;
	printf("Koliko clanova?\n");
	scanf("%d", &br);
	for (int i = 0; i < br; i++) {
		printf("%d. clan:", i+1);
		scanf("%d", &el);
		unesi(head, el);
	}
	return 0;
}

int brisi(Pozicija head, Pozicija a) {
	Pozicija temp = NULL;
	puts("3");
	a = traziPret(head, a);
	puts("4");
	temp = a->next;
	a->next = a->next->next;
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
}

int unija(Pozicija lista1, Pozicija lista2, Pozicija unija) {

	Pozicija L1 = lista1->next, L2 = lista2->next, u = unija, prethodni = NULL, brisac=NULL;
	while (L1 != NULL && L2 != NULL) {
		if (L1->el == L2->el) {
			brisi(&lista2, L2);
			puts("1");
			L1 = L1->next;
			L2 = L2->next;
		}
		else{
			puts("2");
			L2 = L2->next;
		}
	}
	u->next = lista1->next;
	while (u->next != NULL)u = u->next;
	u->next = lista2->next;

	return 0;
}

int ispis(Pozicija p) {

	while (p != NULL) {
		printf("%d", p->el);
		p = p->next;
	}
	return 0;
}
