#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>
#include <alloc/alloc.h>


typedef struct vector{
    void * (*next)(const struct vector *);
} vector;


#define vector_next(T) ((T)->next((T)))


#define fold(T, iter_var, init,  expr) \
    init; for(void * iter_var = vector_next((T)); iter_var != NULL; iter_var = vector_next((T))) expr


#endif



