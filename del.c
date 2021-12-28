#include "del.h"

int delete(DinamicArray *a, DinamicArrayDel *b, int key, int ordenacion){

    int pos, i;
    indexdeletedbook del_book;

    pos = IndexBinSearch(a, key);
    if(pos == -1){
        fprintf(stdout, "Item with key %d does not exist\n", key);
        return 0;
    }

    /*Se guardan los datos del libro a borrar*/
    del_book.offset = a->index[pos].offset;
    del_book.register_size = a->index[pos].size;

    /*Borramos la entrada del libro del indice*/
    for(i=pos; i<(int)a->used; i++){
        a->index[i] = a->index[i+1];
    }
    a->used--;

    /*Añadimos los datos del libro al array de libros borrados*/

    if(insertArrayDel(b, del_book, ordenacion)==-1) return -1;

    fprintf(stdout, "Record with BookID=%d has been deleted\n", key);
    return 0;
}