#ifndef PRINT_H
#define PRINT_H

#include "dinamicArray.h"
#define BufferLenght 128
#define STRLENGHT 64
/** 
 * @brief Imprime el contenido del array del indice.
 * @file print.h
 * @author Ignacio Campos
 */
int printInd(DinamicArray *a);

/** 
 * @brief Imprime el contenido del array de libros borrados.
 * @file print.h
 * @author Ignacio Campos
 */
int printLst(DinamicArrayDel *b);

/** 
 * @brief  Imprime los registros de los libros, siguiendo el indice.
 * @file print.h
 * @author Alberto Castro
 */
int printRec(DinamicArray *a, char *base_datos);
#endif