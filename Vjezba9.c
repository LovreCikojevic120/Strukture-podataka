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
Pozicija unos(Pozicija, int);
Pozicija trazi(Pozicija, int);
Pozicija brisi(Pozicija, int);

int main() {

	Pozicija stablo = NULL; //= (Pozicija)malloc(sizeof(clan));
	char izbor;
	int el = 0;
	while (1) {

		printf("\n1-unos\t2-infix ispis\t3-postfix ispis\t4-prefix ispis\t5-brisi\t6-trazi\t7-kraj\n");
		scanf(" %c", &izbor);

		switch (izbor) {
		case '1':
			printf("unesi broj\n");
			scanf("%d", &el);
			stablo = unos(stablo, el);
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
			printf("unesi broj koi zelis izbrisat\n");
			scanf("%d", &el);
			stablo = brisi(stablo, el);
			break;

		case '6':
			printf("unesi broj koi zelis nac\n");
			scanf("%d", &el);
			trazi(stablo, stablo, el);
			break;

		case '7':
			return 0;
		}
	}

	return 0;
}

Pozicija brisi(Pozicija p, int el) {

	Pozicija priv, q = NULL;
	if (p == NULL)return p;
	if (el < p->el)
	p->l = brisi(p->l, el);
	else if (el > p->el)
	p->r = brisi(p->r, el);
	else {

		if (p->l != NULL && p->r != NULL) {
			priv = p;
			p = p->l;
			while (p->r != NULL)p = p->r;
			q = p;
			p = priv;
			p->el = q->el;
			p->l = brisi(p->l, q->el);


		}
		else {
			puts("dosa");
			q = p;
			if (p->l == NULL)p = p->r;
			else p = p->l;
			free(q);
		}
	}
	return p;
}

Pozicija trazi(Pozicija p, Pozicija roditelj, int el) {

	if (p == NULL) {
		printf("NEMA GA\n");
		return p;
	}

	if (p->el < el) {
		roditelj = p;
		return trazi(p->r, roditelj, el);
	}
	else if (p->el > el) {
		roditelj = p;
		return trazi(p->l, roditelj, el);
	}

	else{
		printf("naden je element %d, njegov roditelj je %d", el, roditelj->el);
		if (p->l != NULL) printf("\nnjegovo lijevo dijete je %d", p->l->el);
		if (p->r != NULL) printf("\nnjegovo desno dijete je %d", p->r->el);
		return p;
	}

}

int IspisInfix(Pozicija p) {

	if (p != NULL) {
		IspisPostfix(p->l);
		printf("%d   ", p->el);
		IspisPostfix(p->r);
	}
}

int IspisPrefix(Pozicija p) {

	if (p != NULL) {
		printf("%d   ", p->el);
		IspisPostfix(p->l);
		IspisPostfix(p->r);
	}
}

int IspisPostfix(Pozicija p) {

	if (p != NULL) {
		IspisPostfix(p->l);
		IspisPostfix(p->r);
		printf("%d   ", p->el);
	}
}

Pozicija unos(Pozicija p, int el) {

	if (p == NULL) {
		p = (Pozicija)malloc(sizeof(clan));
		p->el = el;
		p->l = NULL;
		p->r = NULL;
	}

	else if (el > p->el) p->r = unos(p->r, el);
	
	else if (el < p->el) p->l = unos(p->l, el);

	else puts("clan postoi");

	return p;

}


