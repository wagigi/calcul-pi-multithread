#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NBT 9

struct parametre {
    long debut;
    long increment;
    long double ppi;
};

typedef struct parametre PARAMETRE;

void * calculeur(void * params){
    long i;
    PARAMETRE *P;
    P = (PARAMETRE*)params;
    for (i=P->debut; i < (P->debut+P->increment); i++) {
        P->ppi += ((powl(-1, i)) / (2 * i + 1));
    }
    pthread_exit(NULL);
}

int main() {
    /*Calcul de PI avec 8 threads
     * Thread 1 :     0 à 2000
     * Thread 2 :  2001 à 4000
     * Thread 3 :  4001 à 6000
     * Thread 4 :  6001 à 8000
     * Thread 5 :  8001 à 10000
     * Thread 6 : 10001 à 12000
     * Thread 7 : 12001 à 14000
     * Thread 8 : 14001 à 16000*/
    int err;
    long double ppiret=0;
    pthread_t threadID[NBT];
    PARAMETRE lanceur[NBT];
    for (int i = 0; i < NBT; i++) {

        if (i==0){lanceur[i].debut=0;}
        else{lanceur[i].debut=(i*2000)+1;}
        lanceur[i].increment=2000;
        lanceur[i].ppi=0;

        if ((err=pthread_create(&threadID[i], NULL, calculeur, (void*)&lanceur[i])) != 0) {
            fprintf(stderr,"Erreur %d avec pthread_create()\n",err);
            return 1;
        }
    }

    for (int j = 0; j < NBT; j++) {
        pthread_join(threadID[j],NULL);
        ppiret += lanceur[j].ppi;
    }
    long double pi;
    pi = ppiret*4;
    printf("La valeur de PI est : %.50Lf \n", pi);

    return 0;
}
