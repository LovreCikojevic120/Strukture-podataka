//Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna rezultat.Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct Clan* Pozicija;

typedef struct Clan {

	int el;
	Pozicija next;
}clan;

char* naziv(char*);
void ispis(Pozicija);
void unos(char*, Pozicija);

int main() {

	clan head;
	head.next = NULL;
	char* fileName = NULL;
	fileName = naziv(fileName);
	unos(fileName, &head);
	ispis(head.next);
	
	return 0;
}

char* naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	memset(fileName, '\0', MAX_LENGTH);
	printf("Ime datoteke?\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

void unos(char* fileName, Pozicija head) {

	FILE* f = NULL;
	int i;
	Pozicija q = NULL;
	Pozicija p = head;
	f = fopen(fileName, "r");
	//while (fgetc(f)!='\0')
	for (i = 0; i < 1;i++) {

		q = (Pozicija)malloc(sizeof(clan));
		fscanf(f, "%d", &q->el);
		q->next = p->next;
		p->next = q;
	}
	rewind(f);
	fclose(f);

	//return 0;
}

void ispis(Pozicija head) {

	while (head != NULL) {
		printf(" %d", head->el);
		head = head->next;
	}

	//return 0;
}
