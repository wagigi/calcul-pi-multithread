#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NBT 8

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
    /* Exemple du calcul de PI avec 8 threads et avec un increment de 2000
     * Thread 1 :     0 à 1999
     * Thread 2 :  2000 à 3999
     * Thread 3 :  4000 à 5999
     * Thread 4 :  6000 à 7999
     * Thread 5 :  8000 à 9999
     * Thread 6 : 10000 à 11999
     * Thread 7 : 12000 à 13999
     * Thread 8 : 14000 à 15999*/
    int incrementation=999990;
    int err;
    long double ppiret=0;
    pthread_t threadID[NBT];
    PARAMETRE lanceur[NBT];
    for (int i = 0; i < NBT; i++) {

        lanceur[i].debut=(i*incrementation);
        lanceur[i].increment=incrementation;
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
    long double cpi=3.14159265358979323846264338327950288419716939937510;
    printf("La valeur calculée de PI est : %.50Lf \nLa valeur connue de PI est   : %.50Lf\n", pi, cpi);
    printf("La valeur calculée est proche à %Lf pourcents\n",((100*pi)/cpi));
    return 0;
}
