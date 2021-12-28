#ifndef DEL_H
#define DEL_H

#include "dinamicArray.h"

/** 
 * @brief Borra un libro del indice y lo introduce el el array de libros borrados.
 * @file del.h
 * @author Alberto Castro
 */
int delete(DinamicArray *a, DinamicArrayDel *b, int key, int ordenacion);

#endif