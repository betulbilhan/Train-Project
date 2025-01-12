#include "wagon.h"
#include "train.h"
// #include "material.h"
#include <stdlib.h>
#include <stdio.h>

Wagon *create_wagon(int id)
{

    Wagon *new_wagon = (Wagon *)malloc(sizeof(Wagon));
    Train *t = (Train *)malloc(sizeof(Train));

    if (new_wagon == NULL || t == NULL)
    {
        printf("Lack of memory!\n");
        exit(1);
    }
    new_wagon->wagon_id = id;
    new_wagon->box_count = 0;
    new_wagon->next = NULL;
    new_wagon->prev = NULL;
    new_wagon->max_weight = 1000;
    new_wagon->current_weight = 0;
    new_wagon->loaded_materials = NULL;
    t->wagon_count++;
    return new_wagon;
}
