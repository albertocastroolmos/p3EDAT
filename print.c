#include "print.h"
#include <string.h>

int printInd(DinamicArray *a){

    int i;

    if(!a) return -1;

    for(i=0; i<(int)a->used; i++){

        fprintf(stdout, "Entry #%d\n", i);
        fprintf(stdout,"    key: #%d\n", a->index[i].key);
        fprintf(stdout,"    offset: #%ld\n", a->index[i].offset);
        fprintf(stdout,"    size: #%ld\n", a->index[i].size);
    }
    return 0;
}

int printLst(DinamicArrayDel *b){

  int i;

    if(!b) return -1;

    for(i=0; i<(int)b->used; i++){

        fprintf(stdout, "Entry #%d\n", i);
        fprintf(stdout,"    offset: #%ld\n", b->index[i].offset);
        fprintf(stdout,"    size: #%ld\n", b->index[i].register_size);
    }
    return 0;
}

int printRec(DinamicArray *a, char *base_datos){

    FILE *f = NULL;
    int i, book_id=0, j=0;
    size_t tam=0;
    char data[BufferLenght];
    char isbn[17];

    if(a->used==0){
        return 0;
    }

    f = fopen(base_datos, "rb+");
    if(!f) return -1;

    fseek(f, 0, SEEK_SET);

    memset(isbn, 0, 17);
    memset(data, 0, BufferLenght);

    for(i=0; j<(int)a->used;i++, j++){  /*eeeeeeeeeeeeeee*/

        fseek(f, a->index[j].offset, SEEK_SET);

        fread(&tam, sizeof(size_t), 1, f);
        fread(&book_id, sizeof(int), 1, f);
        fread(isbn, 16, 1, f);
        fread(data, tam-sizeof(int)-16, 1, f);

        printf("%d|%s|%s\n",book_id,isbn, data);
        memset(isbn, 0, 17);
        memset(data, 0, BufferLenght);
    }
       
    fclose(f);
    return 0;
}