#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;

typedef struct Clan {
	int el;
	Pozicija l;
	Pozicija r;
}clan;

int IspisPostfix(Pozicija);
int IspisPrefix(Pozicija);
int IspisInfix(Pozicija);
Pozicija Unos(Pozicija, int);
Pozicija Trazi(Pozicija, Pozicija, int);
Pozicija Brisi(Pozicija, int);

int main() {

	Pozicija stablo = NULL;
	char izbor = NULL;
	int el = NULL;

	while (1) {

		printf("\n1-unos\t2-infix ispis\t3-postfix ispis\t4-prefix ispis\t5-brisi\t6-trazi\t7-kraj\n");
		scanf(" %c", &izbor);

		switch (izbor) {

		case '1':
			printf("Unesi broj:\n");
			scanf("%d", &el);
			stablo = Unos(stablo, el);
			break;

		case '2':
			IspisInfix(stablo);
			break;

		case '3':
			IspisPostfix(stablo);
			break;

		case '4':
			IspisPrefix(stablo);
			break;

		case '5':
			printf("Unesi broj koji zelis izbrisati:\n");
			scanf("%d", &el);
			stablo = Brisi(stablo, el);
			break;

		case '6':
			printf("Unesi broj koji zelis pronaci:\n");
			scanf("%d", &el);
			Trazi(stablo, stablo, el);
			break;

		case '7':
			return 0;
		}
	}
	return 0;
}

Pozicija Brisi(Pozicija p, int el) {

	Pozicija priv = NULL, q = NULL;

	if (p == NULL)return p;

	if (el < p->el){
        	p->l = Brisi(p->l, el);
	}
	else if (el > p->el){
        	p->r = Brisi(p->r, el);
	}
	else {
		if (p->l != NULL && p->r != NULL) {
			priv = p;
			p = p->l;
			while (p->r != NULL)p = p->r;
			q = p;
			p = priv;
			p->el = q->el;
			p->l = Brisi(p->l, q->el);
		}
		else {
			q = p;
			if (p->l == NULL)p = p->r;
			else p = p->l;
			free(q);
		}
	}
	return p;
}

Pozicija Trazi(Pozicija p, Pozicija roditelj, int el) {

	if (p == NULL) {
		printf("Nema ga!\n");
		return p;
	}

	if (p->el < el) {
		roditelj = p;
		return Trazi(p->r, roditelj, el);
	}
	else if (p->el > el) {
		roditelj = p;
		return Trazi(p->l, roditelj, el);
	}

	else{
		printf("Pronaden je element %d, njegov roditelj je %d", el, roditelj->el);
		if (p->l != NULL) printf("\nNjegovo lijevo dijete je %d", p->l->el);
		if (p->r != NULL) printf("\nNjegovo desno dijete je %d", p->r->el);
		return p;
	}

}

int IspisInfix(Pozicija p) {

	if (p != NULL) {
		IspisInfix(p->l);
		printf("%d   ", p->el);
		IspisInfix(p->r);
	}
}

int IspisPrefix(Pozicija p) {

	if (p != NULL) {
		printf("%d   ", p->el);
		IspisPrefix(p->l);
		IspisPrefix(p->r);
	}
}

int IspisPostfix(Pozicija p) {

	if (p != NULL) {
		IspisPostfix(p->l);
		IspisPostfix(p->r);
		printf("%d   ", p->el);
	}
}

Pozicija Unos(Pozicija p, int el) {

	if (p == NULL) {
		p = (Pozicija)malloc(sizeof(clan));
		p->el = el;
		p->l = NULL;
		p->r = NULL;
	}

	else if (el > p->el) p->r = Unos(p->r, el);

	else if (el < p->el) p->l = Unos(p->l, el);

	else printf("Clan vec postoji!\n");

	return p;
}
