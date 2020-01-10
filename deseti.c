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
	Pozicija stog;

}stablo;

typedef struct Clan {

	Pozicija next;
	
}clan;

char* naziv(char*);
int ispis(Pozicija);
int pop(PozicijaStablo);
int push(Pozicija, int);
int racunaj(Pozicija, char*);
int IspisInfix(Pozicija, char*);

int main() {

	clan stog;
	FILE* b = fopen("a.txt", "a");
	char* filename = NULL;
	stog.next = NULL;
	filename = naziv(filename);
	racunaj(&stog, filename);
	fprintf(b, "\n\n");
	IspisInfix(&stog, filename);

	return 0;
}

PozicijaStablo novoStablo(int x){

	PozicijaStablo q = NULL;
	q = (PozicijaStablo)malloc(sizeof(stablo));
	q->elSt = x;
	q->l = NULL;
	q->r = NULL;
	return q;

}

char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

int pop(PozicijaStablo p) {
	int priv = 0;
	Pozicija q = NULL;
	while (p->stog->next->next != NULL)p->stog = p->stog->next;
	if (p->stog->next->next == NULL) {
		q = p->stog->next;
		priv = p->elSt;
		p->stog->next = NULL;
		free(q);
		return priv;
	}
	else if (p->stog->next == NULL) {
		q = p->stog->next;
		priv = p->elSt;
		p->stog->next = NULL;
		free(q);
		return priv;
	}
}

int push(PozicijaStablo p) {

	Pozicija q = NULL;
	while (p->stog->next != NULL)p->stog = p->stog->next;
	q = (Pozicija)malloc(sizeof(clan));
	//q->el = x;
	q->next = p->stog->next;
	p->stog->next = q;
	return 0;
}

int racunaj(Pozicija p, char* filename) {

	FILE* f;
	PozicijaStablo tmp = NULL;
	int x, a, b;
	char postfix[20];
	f = fopen(filename, "r");
	while (!feof(f)) {

		fscanf(f, "%s", postfix);
		if (postfix[0] >= '0' && postfix[0] <= '9') {
			x = atoi(postfix);
			tmp = novoStablo(x);
			push(tmp);
		}
		else {
			a = pop(p);
			b = pop(p);
			tmp = novoStablo(postfix[0]);
			tmp->l->elSt = b;
			tmp->r->elSt = a;
			push(tmp);
			
		}
	}
	return 0;
}

int IspisInfix(PozicijaStablo p, char* filename) {
		FILE* b = fopen("a.txt", "a");
	if (p != NULL) {
		IspisInfix(p->l, filename);
		if(p->elSt>='0' && p->elSt<='9')
		fprintf(b, "%c   ", p->elSt);
		IspisInfix(p->r, filename);
	}
	return 0;
}
