#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Stablo* PozicijaStablo;
typedef struct Clan* Pozicija;

typedef struct Stablo {

	char* elSt;
	PozicijaStablo r;
	PozicijaStablo l;
}stablo;

typedef struct Clan {

    PozicijaStablo el;
	Pozicija next;
}clan;

char* naziv(char*);
int pop(Pozicija, PozicijaStablo*);
int push(Pozicija, PozicijaStablo);
int racunaj(Pozicija, char*, PozicijaStablo*);
int IspisInfix(PozicijaStablo);
int pushStablo(PozicijaStablo*);
int push3(Pozicija*);

int main() {

	Pozicija stog = NULL;
	PozicijaStablo stablo = NULL;
	FILE* b = fopen("a.txt", "a");
	char* filename = NULL;

	filename = naziv(filename);
	push3(&stog);
	racunaj(stog, filename, &stablo);
   	IspisInfix(stablo);

	return 0;
}

int pushStablo(PozicijaStablo *x){

	PozicijaStablo q = NULL;
	q = (PozicijaStablo)malloc(sizeof(stablo));
	if(q == NULL){
        printf("Greska alokacije\n");
        return 0;
	}
	q->elSt = NULL;
	q->l = NULL;
	q->r = NULL;
	*x = q;

	return 0;
}

int push3(Pozicija *x){

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	if(q == NULL){
        printf("Greska alokacije\n");
        return 0;
	}
	q->el = NULL;
	q->next = NULL;
	*x = q;
	return 0;
}


char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	if(fileName == NULL){
        printf("Greska alokacije\n");
        return 0;
	}
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

int pop(Pozicija p, PozicijaStablo *x) {

	Pozicija priv = NULL;
	PozicijaStablo q = NULL;
	priv = p->next;
	p->next = priv->next;
	q = priv->el;
	free(priv);
	*x = q;

	return 0;
}

int push(Pozicija p, PozicijaStablo x) {

	Pozicija q = NULL;
	if(push3(&q)) return 0;
	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}

int racunaj(Pozicija p, char* filename, PozicijaStablo *x) {

	FILE* f = NULL;
	PozicijaStablo q = NULL;
	int br = 0, duzina = 0;
	char *postfix = NULL;

	postfix = (char*)malloc(MAX_LENGTH * sizeof(char));
	if(postfix == NULL){
        printf("Greska alokacije\n");
        return 0;
	}

	f = fopen(filename, "r");
	while (!feof(f)) {

        	pushStablo(&q);
		fscanf(f, " %s", postfix);
		duzina = strlen(postfix);
		q->elSt = (char*)malloc(sizeof(char) * duzina);
		if(q->elSt == NULL){
            printf("Greska alokacije\n");
            return 0;
        }
		strcpy(q->elSt, postfix);
		q->l = NULL;
		q->r = NULL;

		duzina = sscanf(postfix, " %d", &br);
		if(duzina <= 0) {
			pop(p, &q->r);
			pop(p, &q->l);
		}
		push(p, q);
	}

	fclose(f);
	free(postfix);
    	pop(p, &q);
    	*x = q;
	return 0;
}

int IspisInfix(PozicijaStablo p) {

	if (p != NULL) {
        if (p->l != NULL) printf(" ( ");
		IspisInfix(p->l);
		printf(" %s", p->elSt);
		IspisInfix(p->r);
        if (p->r != NULL) printf(" ) ");
	}
	return 0;
}
