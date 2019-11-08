//stog i red

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>


typedef struct Clan* Pozicija;
typedef struct Pamtilo* Adresa;

typedef struct Clan {

	int el;
	Pozicija next;
}clan;

typedef struct Pamtilo{

	Adresa First;
	Adresa Last;
}pamtilo;

int push(Pozicija);
int pop(Pozicija);
int createPamtilo();
int nasumicni(Pozicija);
int ispis(Pozicija);

int main(){

	int select = 0;
	clan Head;
	Head.next = NULL;
	do{
		printf("\nza push 0, za pop 1, za kraj 2\n");
		scanf("%d", &select);
		if(select == 0)push(&Head);
		if(select == 1)pop(&Head);
	}while(select!=2);
	
	return 0;
}

int nasumicni(Pozicija p){
	
	srand((unsigned)time(0));
	p->el = rand()%91+10;
	return 0;
}

int push(Pozicija p){

	int i = 0;
	Pozicija head = p;
	Adresa pamtilo = NULL;
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(clan));
	pamtilo = (Adresa)malloc(sizeof(pamtilo));
	nasumicni(q);
	q->next = p->next;
	p->next = q;
	ispis(head->next);
}

int pop(Pozicija p){
	
	Pozicija head = p;
	while(p->next->next!=NULL){
		p=p->next;
	}
	//free(p->next);
	p->next = NULL;
	ispis(head->next);
	return 0;
}

int ispis(Pozicija p){
	while(p!=NULL){
		printf("%d ", p->el);
		p=p->next;
	}
	return 0;
}

