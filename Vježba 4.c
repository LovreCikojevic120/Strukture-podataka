/*Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct clan* Pozicija;
typedef struct clan poz;


struct clan{

	int koef;
	int exp;
	Pozicija next;
};

typedef struct clan Clan;

int Unos(Pozicija);
char* Naziv(char*);
int Ispis(Pozicija);
int Zbroji(Pozicija, Pozicija, Pozicija);
int Alokacija(Pozicija*);
int Mnozenje(Pozicija, Pozicija, Pozicija);


int main() {

	Clan head ;
	Clan head2;
	Clan zbroj;
	Clan umnozak;

	head.next = NULL;
	head2.next = NULL;
	zbroj.next = NULL;
	umnozak.next = NULL;

	printf("\nPrvi polinom:\n");
	Unos(&head);
	printf("\nDrugi polinom:\n");
	Unos(&head2);

	printf("\nPrvi polinom:\n");
	Ispis(head.next);

	printf("\n\nDrugi polinom:\n");
	Ispis(head2.next);

	Zbroji(head.next, head2.next, &zbroj);
	printf("\n\nZbroj:\n");
	Ispis(zbroj.next);

	Mnozenje(head.next, head2.next, &umnozak);
	printf("\n\nUmnozak:\n");
	Ispis(umnozak.next);
	puts("");

	return 0;
}

int Zbroji(Pozicija p, Pozicija d, Pozicija zbroj) {

	Pozicija q = NULL;

	while (p != NULL && d != 0) {
            Alokacija(&q);

			if (p->exp > d->exp) {
				q->exp = p->exp;
				q->koef = p->koef;
				p = p->next;
			}
			else if (d->exp > p->exp) {
				q->exp = d->exp;
				q->koef = d->koef;
				d = d->next;
			}
			else if (p->exp == d->exp) {
				q->exp = p->exp;
				q->koef = p->koef + d->koef;
				p = p->next;
				d = d->next;
			}

        q->next = zbroj->next;
        zbroj->next = q;
        zbroj = q;
}
    return 0;
}

char* Naziv(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));

	printf("Ime datoteke?\n");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

int Unos(Pozicija prvi) {

	Pozicija q = NULL, p = NULL;
	FILE* f = NULL;
	char* fileName = NULL;

	fileName = (char*)malloc(sizeof(char) * MAX_LENGTH);
	if (fileName == NULL) return 0;

	fileName = Naziv(fileName);
	f = fopen(fileName, "r");
	if (f == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		return 0;
	}

	while (!feof(f)) {

        Alokacija(&q);

        fscanf(f, " %d %d", &q->koef, &q->exp);

        p = prvi;
		while (p->next != NULL && p->next->exp > q->exp)
        p = p->next;

		if (p->next != NULL && p->next->exp == q->exp)
		{
			p->next->koef += q->koef;
			free(q);

			if (p->next->koef == 0)
			{
				q = p->next;
				p->next = q->next;
				free(q);
			}
		}
		else
		{
			q->next = p->next;
			p->next = q;
		}
    }
    fclose(f);
	return 0;
}

int Ispis(Pozicija p) {

    int i = 1;

	while (p != NULL) {
        if(i){
            printf("%d*x^%d", p->koef, p->exp);
            i = 0;
        }
        else if(p->exp > 0) printf(" + %d*x^%d", p->koef, p->exp);
        else    printf(" + %d", p->koef);
		p = p->next;
	}
	return 0;
}

int Alokacija(Pozicija *head)
{
	Pozicija q = NULL;

	*head = (Pozicija)malloc(sizeof(poz));

	q = *head;
	q->next = NULL;

	return 0;
}

int Mnozenje(Pozicija prvi, Pozicija drugi, Pozicija umnozak)
{
    Pozicija q = NULL;
    Pozicija p = NULL;
    Pozicija d = NULL;
    Pozicija umn = NULL;

    p = prvi;
    while(p != 0){
            d = drugi;

            while(d != 0){
                Alokacija(&q);
                umn = umnozak;

                q->exp = p->exp + d->exp;
                q->koef = p->koef * d->koef;

                while(umn->next != NULL && umn->next->exp > q->exp)    umn = umn->next;

                if(umn->next != NULL && umn->next->exp == q->exp){
                    umn->next->koef += q->koef;
                    free(q);

                    if(umn->next->koef == 0){
                        q = umn->next;
                        umn->next = q->next;
                        free(q);
                    }
                }
                else{
                    q->next = umn->next;
                    umn->next = q;
                }
                d = d->next;
            }
            p = p->next;
    }
    return 0;
}
