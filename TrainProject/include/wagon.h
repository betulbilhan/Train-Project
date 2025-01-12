#ifndef WAGON_H
#define WAGON_H
#include "material.h"

typedef struct Wagon
{
    int wagon_id;
    int box_count;
    float max_weight;
    float current_weight;
    LoadedMaterial *loaded_materials;
    struct Wagon *next, *prev;
} Wagon;

Wagon *create_wagon(int id);

// void add_wagon(Wagon **head, int id);

#endif
