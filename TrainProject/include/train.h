#ifndef TRAIN_H
#define TRAIN_H
#include "wagon.h"

// hoca wagon için de böyle yapmış
typedef struct Train
{
    char train_id[20];
    Wagon *first_wagon;
    int wagon_count;
} Train;

void train_status(Wagon *head, Train *t);
void emptyTrain(Train *t);
#endif