#include "train.h"
#include "wagon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void train_status(Wagon *head, Train *t)
{
    Wagon *temp = head;
    printf("\n");
    printf("Train status:\n");
    printf("TRAIN:%s\n", t->train_id);

    while (temp != NULL)
    {

        printf("WAGON ID:%d\n", temp->wagon_id);
        printf("WAGON CAPACITY:1000\n");
        // sum_weight += temp->current_weight;
        printf("CURRENT WEIGHT:%.2f\n", temp->current_weight);
        temp = temp->next;
    }

    printf("\n");
}

void emptyTrain(Train *t)
{
    Wagon *temp = t->first_wagon;

    // vagonlar bittiğinde duracak(temp null olduğunda)
    while (temp)
    {
        Wagon *next = temp->next; // temp = temp->next yapamam çünkü temp aşağıda freeleniyor

        if (temp->loaded_materials != NULL)
        {
            free(temp->loaded_materials);
        }

        free(temp);  // Vagonu hafızadan serbest bırakıyoruz
        temp = next; // Sonraki vagona geçiyoruz
    }
    t->wagon_count = 0;
    t->first_wagon = NULL;
}
