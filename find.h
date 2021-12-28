#ifndef FIND_H
#define FIND_H

#include "dinamicArray.h"
#define BufferLenght 128
#define STRLENGHT 64

/** 
 * @brief Escribe por pantalla los datos del libro buscado (si existe).
 * @file find.h
 * @author Ignacio Campos
 */
int find(DinamicArray *a, char *base_datos, int key);
#endif