#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NBT 9

long double calculeur(long a, long b){
    long i;
    long double ppi = 0;
    for (i=a ; i < b; i++) {
        ppi+= ((powl(-1, i)) / (2 * i + 1));
    }
    return ppi;
}


void * lanceur(long a, long b)
{
    long param;
    char buf[40];
    param = (long)p;
    long double ret = calculeur(a,b);
    pthread_exit(ret);
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
    pthread_t threadID[NBT];
    int a = 16000;
    int b = a/8;
    for (int i = 0; i < a; i=+b) {
        if ((err=pthread_create(&threadID[i], NULL, lanceur, i, b)) != 0) {
            fprintf(stderr,"Erreur %d avec pthread_create()\n",err);
            return 1;
        }

    }


    return 0;
}
