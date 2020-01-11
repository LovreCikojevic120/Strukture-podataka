//dodat provjere alokacije, inicijalizirat varijable na nulu, ta sranja

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

	Pozicija stog;
	PozicijaStablo stablo;
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
	q->elSt = NULL;
	q->l = NULL;
	q->r = NULL;
	*x = q;

	return 0;
}

int push3(Pozicija *x){

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	q->el = NULL;
	q->next = NULL;
	*x = q;
	return 0;
}


char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
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
	if(push3(&q)) return 0; //nean pojma
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

	f = fopen(filename, "r");
	while (!feof(f)) {

        	pushStablo(&q);
		fscanf(f, " %s", postfix);
		duzina = strlen(postfix);
		q->elSt = (char*)malloc(sizeof(char) * duzina);
		strcpy(q->elSt, postfix);
		q->l = NULL;
		q->r = NULL;

		duzina = sscanf(postfix, " %d", &br);
		if(duzina <= 0) { //nean pojma
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
