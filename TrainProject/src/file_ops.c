#include <stdio.h>
#include <stdlib.h>
#include "file_ops.h"
#include "train.h"
#include "wagon.h"
#include "material.h"

void train_status_to_file(Train *t, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("File cannot be opened");
        return;
    }

    // Tren bilgilerini dosyaya yaz
    fprintf(file, "TRAIN:%s:%d\n", t->train_id, t->wagon_count);

    Wagon *current_wagon = t->first_wagon;

     fprintf(file, "MATERIALS:3\n");
     fprintf(file, "M:Large Box:Steel:200.00\n");
     fprintf(file, "M:Medium Box:Aluminium:150.00\n");
     fprintf(file, "M:Small Box:Wood:100.00\n");

    // Her bir vagon için bilgileri yaz
    while (current_wagon != NULL)
    {
        fprintf(file, "WAGON:%d:%.2f:%.2f\n",
                current_wagon->wagon_id,
                current_wagon->max_weight,
                current_wagon->current_weight);

        // Vagonun yüklü malzemelerini yaz

        LoadedMaterial *current_material = current_wagon->loaded_materials;
        // DEBUG SATIRI printf("Name: %s\n", current_material->type->name);
        while (current_material != NULL)
        {
            for (int i = 0; i < current_material->type->quantity; i++)
            {
                if (current_material->type->weight == 200.00)
                {

                    fprintf(file, "L:LARGE BOX\n");
                }
                if (current_material->type->weight == 150.00)
                {

                    fprintf(file, "M:MEDIUM BOX\n");
                }
                if (current_material->type->weight == 100.00)
                {

                    fprintf(file, "S:SMALL BOX\n");
                }
            }
            current_material = current_material->next;
        }

        current_wagon = current_wagon->next;
    }

    fclose(file);

    printf("Train status succesfully written to the '%s' file.\n ", filename);
}

void print_file_contents(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File cannot be opened");
        return;
    }

    // Dosyanın boş olup olmadığını kontrol et
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        printf("File is empty.\n");
        fclose(file);
        return;
    }
    rewind(file); // Dosyanın başına dön

    char line[256];
    printf("Contents of the file '%s':\n", filename);

    // Dosyayı satır satır oku ve ekrana yazdır
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line); // Her bir satırı yazdır
    }

    fclose(file);
}
