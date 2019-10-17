/*  Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable  */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* Pozicija;

typedef struct osoba{
    char ime[20];
    char prezime[20];
    int godina;
    Pozicija next;
}_osoba;

void UnosP(Pozicija p)
{
    Pozicija q = 0;
    printf("za kraj unesite 'stop' i bilo koje dvije rijeci\n");
    while(1){
    q = (Pozicija)malloc(sizeof(_osoba));
    printf("Ime, prezime, godina rodenja:\n");
    scanf("%s %s %d", &q->ime, &q->prezime, &q->godina);
    if(!strcmp(q->ime,"stop")) break;
    q->next = p->next;
    p->next = q;
    }
}

void Ispis(Pozicija p)
{
    while(p != 0){
        printf("%s %s %d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }
}

void UnosK(Pozicija p)
{
    Pozicija q = 0;
    printf("za kraj unesite 'stop' i bilo koje dvije rijeci\n");
    while(1){
    q = (Pozicija)malloc(sizeof(_osoba));
    printf("Ime, prezime, godina rodenja:\n");
    scanf("%s %s %d", &q->ime, &q->prezime, &q->godina);
    if(!strcmp(q->ime,"stop")) break;
    while(p->next != 0)
        p = p->next;
    q->next = p->next;
    p->next = q;
}
}

void Trazi(Pozicija p)
{
    char unos[50];
    scanf("%s", unos);

    while(strcmp(unos, p->prezime))
        p = p->next;
    printf("%s %s %d\n", p->ime, p->prezime, p->godina);
}

Pozicija TraziPret(char unos[], Pozicija p){
    Pozicija Pret = p;
    p = p->next;
    while(p != NULL && strcmp(unos, p->ime)){
        Pret = p;
        p = p->next;
    }
    if(NULL == p) return 0;
    else return Pret;
}

int Brisi(Pozicija p) //DODAT USPOREDBU I S IMENON I S GODINON
{
    Pozicija priv;
    char unos[50];
    scanf("%s", unos);
    p = TraziPret(unos, p);

    //while(1){
       // if(!strcmp(unos, p->ime)){
                priv = p->next;
                p->next = p->next->next;
                free(priv);
            //    break;
      //  }
      //  else p = p->next;
    //}
    return 0;
}

int main()
{
    _osoba Head;
	Head.next = 0;
    char c, unos[50];
	povratak: printf("\n1 - dinamicki dodaje novi element na pocetak liste\n2 - ispisuje listu\n3 - dinamicki dodaje novi element na kraj liste\n4 - pronalazi element u listi (po prezimenu)\n5 - brise odredeni element iz liste\n6 - kraj\n\n");
    scanf(" %c", &c);
    switch (c) {
        case '1':   UnosP(&Head); break;
        case '2':   Ispis(Head.next); break;
        case '3':   UnosK(&Head); break;
        case '4':   Trazi(&Head);  break;
        case '5':   Brisi(&Head);  break;
        case '6':   return 0;

    }
    goto povratak;
}
