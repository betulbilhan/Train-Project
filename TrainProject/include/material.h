#ifndef MATERIAL_H
#define MATERIAL_H
// #include "train.h"

typedef struct Train Train; // Forward declaration
typedef struct Wagon Wagon; // Forward declaration

typedef struct
{
    char name[50]; // e.g., "Large Box"
    float weight;  // Weight in kg
    int quantity;  // Total available
    int loaded;    // Currently on train
} MaterialType;

// typdef struct LoadedM
typedef struct LoadedMaterial
{
    MaterialType *type; // Type of box
    struct LoadedMaterial *next, *prev;
} LoadedMaterial;

void load_material(int quantity, MaterialType *m_type, Wagon **head, Train *t);
void add_to_specific_wagon(int wagon_id, int quantity, MaterialType *m_type, Wagon **head, Train *t);
MaterialType *create_mtr(int quantity, char type);
void unload_specific_material(MaterialType *m_type, int quantity, Wagon **head);
void material_status(Train *train);
void unloadMaterial(Train *train, MaterialType *material, int quantity);

#endif