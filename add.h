#ifndef ADD_H
#define ADD_H

#define BufferLenght 128
#define STRLENGHT 64

#include "string.h"
#include "dinamicArray.h"

/** 
 * @brief Introduce un libro a la db y al indice siguiendo el metodo de ordenacion
 * 
 * @file add.h
 * @author Ignacio Campos
 */
int add(DinamicArray *a, DinamicArrayDel *b, char* book_data, char* base_datos, char* delreg, int ordenacion);

#endif