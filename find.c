#include "find.h"
#include <string.h>



int find(DinamicArray *a, char *base_datos, int key){

    FILE *f = NULL;
    int pos, book_id;
    size_t tam;
    char data[BufferLenght];

    memset(data, 0, BufferLenght);

    if(!a || !base_datos)return -1;

    /*Se realiza la busqueda binaria:*/

    pos = IndexBinSearch(a, key);
    if(pos==-1){
        fprintf(stdout, "\nRecord with bookId=%d does not exist\n", key);
        return 0;
    }

    /*Si el libro existe:*/

    f = fopen(base_datos, "rb+");
    if(!f) return -1;

    fseek(f, a->index[pos].offset, SEEK_SET); /*Vamos a la posición del libro en la bd*/

    /*Leemos el contenido del fichero por orden*/
    fread(&tam, sizeof(size_t), 1, f);
    fread(&book_id, sizeof(int), 1, f);
    fread(data, tam-sizeof(int), 1, f);

    fprintf(stdout, "\n%d|%s\n", book_id, data);    /*Se imprimen los datos del libro*/
    fclose(f);
    

    return 0;
}