#include "vector_test.h"
#include "../src/interface/vector.h"

#include <stdio.h>
#include <stdbool.h>


typedef struct {
    vector vector;
    size_t size;
    size_t dtype;
    char * array;

    size_t index;
}Array;


#define array_to_vector(T) _Generic((T), Array*: ((const vector*) (T)))


static void array_reset(Array * self) {
    self->index = 0;
}


static void * array_next(Array * self) {
    if(self->index < self->size) {
        return self->array + (self->dtype * (self->index ++));
    } else {
        return NULL;
    }
}


#define array(_dtype, _size, _array)                                    \
    (Array) {                                                           \
        .vector = {                                                     \
            .next = (void*(*)(const vector*)) array_next                \
            , .reset_iterator = (void(*)(const vector*)) array_reset    \
        }                                                               \
        , .size = (_size)                                               \
        , .dtype = (_dtype)                                             \
        , .array = (void*)(_array)                                      \
        , .index = 0                                                    \
    }


#define size(T) sizeof((T))/sizeof(*(T))


static bool vector_iteration_test(void) {
    int buffer[] = {1, 2, 3, 4, 5};
    Array arr = array(sizeof(int), size(buffer) , buffer);
    size_t index = 0;

    foreach(array_to_vector(&arr), value) {
        if(*(int*) value != buffer[index]) {
            return false;
        }

        index++;
    }

    return true;
}


static bool vector_repeate_iteration_test(void) {
    int buffer[] = {1, 2, 3, 4, 5};
    Array arr = array(sizeof(int), size(buffer) , buffer);

    for(size_t i = 0; i < 2; i ++) {
        size_t index = 0;

        foreach(array_to_vector(&arr), value) {
            if(*(int*) value != buffer[index]) {
                return false;
            }

            index++;
        }
    }

    return true;
}


void vector_test(void) {
    printf("#### vector_test ####\n");

    printf("\tvector_iteration_test: %s\n", vector_iteration_test() ? "PASS" : "FAIL");
    printf("\tvector_repeate_iteration_test: %s\n", vector_repeate_iteration_test() ? "PASS" : "FAIL");
}



