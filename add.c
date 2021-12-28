#include "add.h"
#include <string.h>


int add(DinamicArray *a, DinamicArrayDel *b, char* book_data, char* base_datos, char* delreg, int ordenacion){

    indexbook ind;
    FILE *f = NULL;
    size_t tam, strategy_tam;
    char* book_id = NULL;
    char* isbn = NULL;
    char* titulo = NULL;
    char* editorial = NULL;
    char data[BufferLenght];
    int int_book_id, pos, pos_fin, i, strategy_pos, strategy_num, flag=0;

   if (!a|| !b || !book_data || !base_datos || !delreg){
       return -1;
   }

    if(strlen(book_data) < 21) return -1; /*Book_data no sería valido*/

    memset(data, 0, BufferLenght);

   /*Se separan los datos de book_data*/

    book_id=strtok(book_data, "|");
    isbn =strtok(NULL, "|");
    titulo =strtok(NULL, "|");
    editorial =strtok(NULL, "|"); 

    int_book_id = atoi(book_id);

    strcpy(data, isbn);
    strcat(data, titulo);
    strcat(data, "|");
    strcat(data, editorial);



    tam = strlen(data)-1+sizeof(int);
    
    if(a->used != 0){
        pos = IndexBinSearch(a, int_book_id); /*Se busca la posición adecuada en el indice*/

        if(pos != -1){
            fprintf(stdout, "\nRecord with BookID=%d exists.\n", int_book_id);
            return 0;
        }
    }


    /*Mirar en el listado de registros borrados si existe un hueco capaz de
    albergar el nuevo libro, siguiendo el metodo de ordenacion.*/

    if(ordenacion == 0){ /*BEST_FIT*/
        if(b->used > 0){
            strategy_tam = b->index[b->used-1].register_size; 
            strategy_num = (int)b->used-1;

            for(i=(int)b->used-1; i >= 0; i--){    /*Recorremos el array en busca de un hueco*/

                if(b->index[i].register_size <= strategy_tam && b->index[i].register_size >= tam){
                    strategy_tam = b->index[i].register_size;
                    strategy_num = i;
                }
            }
            if(strategy_num == (int)b->used-1 && b->index[strategy_num].register_size < tam){ /*No hay hueco*/
                strategy_num = -1;
            }
        }else{
            strategy_num = -1;
        }

    }else if(ordenacion == 1){  /*WORST_FIT*/

        if(b->used > 0){
            strategy_tam = b->index[b->used-1].register_size; 
            strategy_num = (int)b->used-1;

            for(i=(int)b->used-1; i >= 0; i--){    /*Recorremos el array en busca de un hueco*/

                if(b->index[i].register_size >= strategy_tam && b->index[i].register_size >= tam){
                    strategy_tam = b->index[i].register_size;
                    strategy_num = i;
                }
            }
            if(strategy_num == (int)b->used-1 && b->index[strategy_num].register_size < tam){ /*No hay hueco*/
                strategy_num = -1;
            }
        }else{
            strategy_num = -1;
        }
    }else if(ordenacion == 2){   /*FIRST_FIT*/
    
        if(b->used > 0){

            for(i=(int)b->used-1; i >= 0 && flag == 0; i--){ /*Encontramos cualquier hueco donde quepa (para poder comparar luego)*/
                if(b->index[i].register_size >= tam){
                    strategy_num = i;
                    strategy_pos = b->index[i].offset;
                    flag = 1;
                }
            }
        
            for(i = 0; i < (int)b->used; i++){   

                if((b->index[i].register_size) >= tam && (int)b->index[i].offset < strategy_pos){ 
                    strategy_num = i;
                    strategy_pos = b->index[i].offset;
                }
            }
            if(strategy_num == (int)b->used && b->index[strategy_num].register_size < tam){ /*No hay hueco*/
                strategy_num = -1;
            }
        }else{
            strategy_num = -1;
        }
    }

    f=fopen(base_datos, "rb+");
    if(!f){                                 /*No existe el fichero, así que lo creamos*/
        f=fopen(base_datos, "wb");
    }

if(strategy_num == -1){ /*No hay ningún hueco válido, se introduce al final del .db*/
    fseek(f, 0, SEEK_END);
    pos_fin = ftell(f);

    ind.key  = int_book_id;
    ind.offset = pos_fin;
    ind.size = tam;

    /*Actualizamos el indice*/
    if(insertArray(a, ind)==-1){
        fclose(f);
        return -1;
    }

    /*Guardamos el libro en la bd*/
    fwrite(&tam, sizeof(size_t), 1, f);
    fwrite(&int_book_id, sizeof(int), 1, f);
    fwrite(data, tam-sizeof(int), 1, f); 

    fprintf(stdout, "\nRecord with BookID=%d has been added to the database.\n", int_book_id);

    fclose(f);

}else{

    fseek(f, b->index[strategy_num].offset, SEEK_SET); /*Colocamos el puntero al principio del hueco*/
    strategy_pos = ftell(f);

    ind.key  = int_book_id;
    ind.offset = strategy_pos;
    ind.size = tam;


    /*Actualizamos el indice*/
    if(insertArray(a, ind)==-1){
        fclose(f);
        return -1;
    }


    /*Guardamos el libro en la bd*/
    fwrite(&tam, sizeof(size_t), 1, f);
    fwrite(&int_book_id, sizeof(int), 1, f);
    fwrite(data, tam-sizeof(int), 1, f);

    fprintf(stdout, "\nRecord with BookID=%d has been added to the database.\n", int_book_id);

    /*Actualizar array delreg*/

    pos_fin = ftell(f);

    b->index[strategy_num].offset = pos_fin; /*Aquí comienza el resto del hueco*/
    b->index[strategy_num].register_size -= tam; /*Este es en nuevo tamaño del hueco*/


    if(b->index[strategy_num].register_size == 0){ /*Si el hueco ya no existe, lo borramos*/
        for(i=strategy_num; i<(int)b->used; i++){
            b->index[i] = b->index[i+1];
        }
        b->used--;
    }

    fclose(f);
}

    return 0;
}


/*A lo mejor hacer el firstfit fuera*/