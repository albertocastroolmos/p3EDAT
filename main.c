#define BESTFIT 0 
#define WORSTFIT 1
#define FIRSTFIT 2 
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "print.h"
#include "add.h"
#include "dinamicArray.h"
#include "find.h"
#include "del.h"

/*Private Function*/
/** 
 * @brief Guarda los libros en los archivos .in y .lst, y libera memoria.
 * @file main.c
 * @author Ignacio Campos
 */
int menu_exit(DinamicArray *a, DinamicArrayDel *b, char *indice, char *delreg, int ordenacion);


int main(int arg, char *argv[]){

    char indice[STRLENGHT];
    char base_datos[STRLENGHT];
    char delreg[STRLENGHT];
    char input[BufferLenght] = "\0";
    char *cmd = NULL;
    char *book_data = NULL;
    int   ordenacion, pos_fin, pos_actual, book_id, ds;
    DinamicArray a;
    DinamicArrayDel b;
    indexbook index;
    indexdeletedbook del_index;
    FILE *f = NULL;

    if(arg!=3){
            printf("Missing argument\n");  
            return 0;     
        }

    if(strcasecmp(argv[1], "best_fit")==0){
            ordenacion = BESTFIT;
    
        }
    else if(strcasecmp(argv[1], "first_fit")==0){
            ordenacion = FIRSTFIT;
        }
    else if(strcasecmp(argv[1], "worst_fit")==0){
            ordenacion = WORSTFIT;
        }
    else{
            printf("Unknown search strategy %s\n", argv[1]);        /*Comprobacion de estrategia*/
            return 0;
        }

    sprintf(indice, "%s.ind", argv[2]);
    sprintf(base_datos, "%s.db", argv[2]);
    sprintf(delreg, "%s.lst", argv[2]); 

    /*Se inicializa el indice y se recuperan los datos del fichero .ind*/
    if(initArray(&a, 5) == -1) return -1;

    f = fopen(indice, "rb+");
    if(f != NULL){
        fseek(f, 0, SEEK_END);
        pos_fin = ftell(f);
        fseek(f, 0, SEEK_SET);
        pos_actual = ftell(f);

        while(pos_actual != pos_fin){
            fread(&index.key, sizeof(int), 1, f);
            fread(&index.offset, sizeof(long), 1, f);
            fread(&index.size, sizeof(size_t), 1, f);

            if(insertArray(&a, index) == -1){
                fclose(f);
                freeArray(&a);
                return -1;
            }

            pos_actual = ftell(f);

        }

        fclose(f);
    }
    else{
        f = fopen(indice, "wb"); /*Creamos el fichero en caso de que no exista*/
        fclose(f);
    }


    /*Se inicializa el del_index y se recuperan los datos del fichero .del*/

    if(initArrayDel(&b, 5)==-1) return -1;

    f = fopen(delreg, "rb+");
    if(f != NULL){
        fseek(f, 0, SEEK_END);
        pos_fin = ftell(f);
        fseek(f, 0, SEEK_SET);

        fread(&ds, sizeof(int), 1, f); /*Se guarda lo primero que hay en el .del por si es util*/

        pos_actual = ftell(f);

        while(pos_actual != pos_fin){
            fread(&del_index.offset, sizeof(long), 1, f);
            fread(&del_index.register_size, sizeof(size_t), 1, f);

            if(insertArrayDel(&b, del_index, ordenacion) == -1){
                fclose(f);
                freeArrayDel(&b);
                freeArray(&a);
                return -1;
            }

            pos_actual = ftell(f);

        }
        fclose(f);
    }
    else{
        f = fopen(delreg, "wb"); /*Creamos el fichero en caso de que no exista*/
        fclose(f);
    }



    fprintf(stdout, "Type command and argument/s.\n");


    while(1){

        fprintf(stdout, "exit\n");



        fgets(input, BufferLenght, stdin);

        cmd = strtok(input, " ");
        book_data = strtok(NULL, "");

        if(strcasecmp(cmd, "exit\n") == 0){  
            if(menu_exit(&a, &b, indice, delreg, ordenacion) == -1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }else return 0;
        }

        if(strcasecmp(cmd, "add")==0){   
            if(add(&a, &b, book_data, base_datos, delreg, ordenacion)==-1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }
            
        }
        else if(strcasecmp(cmd, "find")==0){

            book_id=(int)strtol(book_data, NULL, 10);

            if(find(&a, base_datos, book_id)==-1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }
        
        }
        else if(strcasecmp(cmd, "del")==0){
            book_id=(int)strtol(book_data, NULL, 10);
            if(delete(&a, &b, book_id, ordenacion) == -1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }
        }
        
        else if(strcasecmp(cmd, "printInd\n")==0){
            if(printInd(&a)==-1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }
            
        }
        else if(strcasecmp(cmd, "printLst\n")==0){
            if(printLst(&b) == -1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            
            }
        
        }
        else if(strcasecmp(cmd, "printRec\n")==0){
            if(printRec(&a, base_datos)==-1){
                freeArray(&a);
                freeArrayDel(&b);
                return 0;
            }
        }
        else{
            fprintf(stdout, "\nComando desconocido, introduzcalo de nuevo:\n");
        }
    }
    freeArray(&a);
    freeArrayDel(&b);
    return 0;
}


int menu_exit(DinamicArray *a, DinamicArrayDel *b, char *indice, char *delreg, int ordenacion){
    int i;
    FILE *f = NULL;

    /*Guardamos el contenido del indice en el fichero .ind*/
    f = fopen(indice, "wb");
            if(!f){
                return -1;
            }

            fseek(f, 0, SEEK_END);
 

            for(i=0; i<(int)a->used; i++){
                fwrite(&a->index[i].key, sizeof(int), 1, f);
                fwrite(&a->index[i].offset, sizeof(long), 1, f);
                fwrite(&a->index[i].size, sizeof(size_t), 1, f);
            }
            fclose(f);
            freeArray(a);


    /*Guardamos el contenido del del_index en el fichero .del*/
    f = fopen(delreg, "wb");
            if(!f){
                return -1;
            }

            fseek(f, 0, SEEK_END);


    /*Escribimos el metodo de ordenacion porque parece que hay que hacerlo?*/
    /*Pero según los test FF = 0, BF = 1 WF = 2 así que hay que cambiarlo*/

    fwrite(&ordenacion, sizeof(int), 1, f);



            for(i=0; i<(int)b->used; i++){
                fwrite(&b->index[i].offset, sizeof(size_t), 1, f);
                fwrite(&b->index[i].register_size, sizeof(size_t), 1, f);
            }
            fclose(f);
            freeArrayDel(b);
    return 0;
}