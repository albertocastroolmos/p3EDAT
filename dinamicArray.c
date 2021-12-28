#include "dinamicArray.h"

int initArray (DinamicArray *a, size_t initialSize){

    if(initialSize <= 0) return -1;

    a->index = (indexbook*)malloc(initialSize * sizeof(indexbook));

    if(a->index == NULL) return -1;

    a->used = 0;
    a->size = initialSize;

    return 0;
}

int insertArray(DinamicArray *a, indexbook indice){

    int i;
    indexbook aux;

    if(!a) return -1;

    if(a->used == a->size){
        a->size *= 2;
        a->index = (indexbook*)realloc(a->index, a->size * sizeof(indexbook));

        if(a->index == NULL) return -1;
    }

    a->index[a->used] = indice; /*Se inserta en la ultima posicion*/


    /*Si la tabla solo tiene 1 elemento*/
    if(a->used == 0){
        a->used++;
        return 0;
    }

    /*Reordenamos el array con el nuevo elemento*/

    for(i=(int)a->used; i>0; i--){

        if((a->index[i].key) < (a->index[i-1].key)){
            aux = a->index[i-1];
            a->index[i-1] = a->index[i];
            a->index[i] = aux;
        }
        else{                   /*Si llega aqui, el array está ordenado y no hacen falta mas operaciones*/
            a->used++; 
            return 0;
        }
    }

    a->used++;
    return 0;
}

void freeArray(DinamicArray *a){

    if(!a) return;

    free(a->index);
    a->index = NULL;
    a->size = 0;
    a->used = 0;

    return;
}

int IndexBinSearch(DinamicArray *a, int book_id){

    int p=0, u=0, m=0;

    if(!a) return -1;

    p = 0; /*Primera posición del array*/
    u = a->used-1; /*Ultima posicion en uso del array*/

    while(p<=u){

        m = (p+u)/2;

        if(a->index[m].key == book_id){
            return m;
        }else if(a->index[m].key < book_id){
            p = m+1;
        }else if(a->index[m].key > book_id){
            u = m-1;
        }
    }
    return -1; /*No hay ningun elemento con el mismo book_id*/
}

int initArrayDel(DinamicArrayDel *a, size_t initialSize){

    if(initialSize <= 0) return -1;

    a->index = (indexdeletedbook*)malloc(initialSize * sizeof(indexdeletedbook));

    if(a->index == NULL) return -1;

    a->used = 0;
    a->size = initialSize;

    return 0;
}

void freeArrayDel(DinamicArrayDel *a){

    if(!a) return;

    free(a->index);
    a->index = NULL;
    a->size = 0;
    a->used = 0;

    return;
}

int insertArrayDel(DinamicArrayDel *a, indexdeletedbook indice, int ordenacion){

    int i;
    indexdeletedbook aux;

    if(!a) return -1;

    if(a->used == a->size){
        a->size *= 2;
        a->index = (indexdeletedbook*)realloc(a->index, a->size * sizeof(indexdeletedbook));

        if(a->index == NULL) return -1;
    }



    a->index[a->used] = indice; /*Se inserta en la ultima posicion*/


    /*Si la tabla solo tiene el elemento introducido*/
    if(a->used == 0){
        a->used++;
        return 0;
    }

    /*No se si esto es aquí pero parece que si por los test*/
    /*Dependiendo de la estrategia de ordenación:*/

    if(ordenacion == 0){ /*BEST_FIT*/
    /*Reordenamos el array con el nuevo elemento*/

        for(i=(int)a->used; i>0; i--){

            if((a->index[i].register_size) < (a->index[i-1].register_size)){
                aux = a->index[i-1];
                a->index[i-1] = a->index[i];
                a->index[i] = aux;
            }
        }
        a->used++; 

        }else if(ordenacion == 1){  /*WORST_FIT*/

        for(i=(int)a->used; i>0; i--){

            if((a->index[i].register_size) > (a->index[i-1].register_size)){
                aux = a->index[i-1];
                a->index[i-1] = a->index[i];
                a->index[i] = aux;
            }
        }
        a->used++;
        }else if(ordenacion == 2){  /*FIRST_FIT*/
        a->used++;
        }else return -1;

        return 0;
    }
