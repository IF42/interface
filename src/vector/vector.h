#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>


typedef struct vector {
    void (*reset_iterator)(const struct vector*);
    void * (*next)(const struct vector *);
} vector;


#define vector_reset_iterator(T) ((T)->reset_iterator((T)))

#define vector_next(T) ((T)->next((T)))


#define foreach(T, iter_var)     \
    vector_reset_iterator((T));  \
    for(void * iter_var = vector_next((T)); iter_var != NULL; iter_var = vector_next((T)))


#endif



