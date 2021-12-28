#ifndef DINAMICARRAY_H
#define DINAMICARRAY_H

#include "stdio.h"
#include "stdlib.h"

typedef struct _indexbook{
    int key;         
    long int offset; 
    size_t size;    
}indexbook;

typedef struct _DinamicArray{
    indexbook *index;
    size_t used;
    size_t size;
}DinamicArray;

typedef struct {
    size_t register_size; /*Size of the deleted register*/
    size_t offset;  /*Record's offset in file*/
} indexdeletedbook ;

typedef struct _DinamicArrayDel{
    indexdeletedbook *index;
    size_t used;
    size_t size;
}DinamicArrayDel;

/** 
 * @brief Inicializa el array del indice.
 * @file dinamicArray.h
 * @author Ignacio Campos
 */
int initArray(DinamicArray *a, size_t initialSize);

/** 
 * @brief Libera la memoria del el array del indice.
 * @file dinamicArray.h
 * @author Ignacio Campos
 */
void freeArray ( DinamicArray *a);

/** 
 * @brief inserta un elemento en el array.
 * @file dinamicArray.h
 * @author Ignacio Campos
 */
int insertArray (DinamicArray *a, indexbook indice);

/** 
 * @brief Realiza una busqueda binaria del libro introducido.
 * @file dinamicArray.h
 * @author Alberto Castro
 */
int IndexBinSearch(DinamicArray *a, int book_id);

/** 
 * @brief Inicializa el array para libros borrados.
 * @file dinamicArray.h
 * @author Alberto Castro
 */
int initArrayDel(DinamicArrayDel *a, size_t initialSize);

/** 
 * @brief Libera la memoria del array para libros borrados.
 * @file dinamicArray.h
 * @author Alberto Castro
 */
void freeArrayDel(DinamicArrayDel *a);

/** 
 * @brief Inserta un elemento en el array para libros borrados.
 * @file dinamicArray.h
 * @author Alberto Castro
 */
int insertArrayDel(DinamicArrayDel *a, indexdeletedbook indice, int ordenacion);



#endif