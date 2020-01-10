#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;
typedef struct Stablo* PozicijaStablo;

typedef struct Stablo {

	int elSt;
	PozicijaStablo r;
	PozicijaStablo l;

}stablo;

typedef struct Clan {

	int el;
	Pozicija next;
	
	
}clan;

char* naziv(char*);
int ispis(Pozicija);
int pop(Pozicija);
int push(Pozicija, int);
int racunaj(Pozicija, char*);
int IspisInfix(Pozicija, char*);

int main() {

	clan stog;
	char* filename = NULL;
	stog.next = NULL;
	filename = naziv(filename);
	racunaj(&stog, filename);
	fprintf(filename, "\n\n");
	IspisInfix(&stog, filename);

	return 0;
}

char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

int pop(Pozicija p) {
	int priv = 0;
	Pozicija q = NULL;
	while (p->next->next != NULL)p = p->next;
	if (p->next->next == NULL) {
		q = p->next;
		priv = p->next->el;
		p->next = NULL;
		free(q);
		return priv;
	}
	else if (p->next == NULL) {
		q = p->next;
		priv = p->next->el;
		p->next = NULL;
		free(q);
		return priv;
	}
}

int push(Pozicija p, int x) {

	Pozicija q = NULL;
	while (p->next != NULL)p = p->next;
	q = (Pozicija)malloc(sizeof(clan));
	q->el = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int racunaj(Pozicija p, char* filename) {

	FILE* f;
	int x, a, b;
	char postfix[20];
	f = fopen(filename, "r");
	while (!feof(f)) {

		fscanf(f, "%s", postfix);
		if (postfix[0] >= '0' && postfix[0] <= '9') {
			x = atoi(postfix);
			push(p, x);
		}
		else {
			a = pop(p);
			b = pop(p);

			push(p, postfix[0]);
			while (p->next != NULL) p = p->next;
			
			/*switch (postfix[0]) {
			case '+':push(p, a + b); break;
			case '*':push(p, a * b); break;
			case '-':push(p, a - b); break;
			case '/':	if (NULL == a) {
				printf("\ndijeljenje s nulom\n");
				return 0;
			}
					push(p, (float)(a / b)); break;
			}*/
		}
	}
	return 0;
}

int IspisInfix(Pozicija p, char* filename) {

	if (p != NULL) {
		IspisInfix(p->l, filename);
		if(p->el>='0' && p->el<='9')
		fprintf(filename, "%c   ", p->el);
		IspisInfix(p->r, filename);
	}
	return 0;
}
