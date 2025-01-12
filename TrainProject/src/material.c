#include <stdio.h>
#include <stdlib.h>
#include "material.h"
#include "train.h" // Train türünün tam tanımı için.
#include "wagon.h" // Wagon türünün tam tanımı için.
#include <ctype.h>
#include <string.h>

// TRAIN T WAGON COUNTU ARTTIRS
void load_material(int quantity, MaterialType *m_type, Wagon **head, Train *t) {
    Wagon *temp = *head;
    int remaining_quantity = quantity;

    // Mevcut vagonlara yükleme
    while (remaining_quantity > 0 && temp != NULL) {
        // Hafif üstüne ağır konamaz kontrolü
        if (temp->loaded_materials == NULL || temp->loaded_materials->type->weight >= m_type->weight) {
            int available_space = (temp->max_weight - temp->current_weight) / m_type->weight;
            if (available_space > 0) {
                int to_load = (remaining_quantity < available_space) ? remaining_quantity : available_space;
                temp->current_weight += to_load * m_type->weight;
                temp->box_count += to_load;
                remaining_quantity -= to_load;

                // Malzeme ekle
                LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
                new_material->type = m_type;
                new_material->next = temp->loaded_materials;
                temp->loaded_materials = new_material;

                m_type->loaded += to_load;

                printf("Vagon %d: %s tipi %d adet malzeme yüklendi. (Toplam yüklü: %d)\n",
                       temp->wagon_id, m_type->name, to_load, m_type->loaded);
            }
        }
        temp = temp->next;
    }

    // Yeni vagon oluşturma ve kalan malzemeyi yükleme
    while (remaining_quantity > 0) {
        Wagon *new_wagon = (Wagon *)malloc(sizeof(Wagon));
        new_wagon->wagon_id = (t->wagon_count == 0) ? 1 : t->wagon_count + 1;
        new_wagon->max_weight = 1000;
        new_wagon->current_weight = 0;
        new_wagon->box_count = 0;
        new_wagon->loaded_materials = NULL;
        new_wagon->next = NULL;

        if (*head == NULL) {
            *head = new_wagon;
            new_wagon->prev = NULL;
        } else {
            Wagon *last = *head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_wagon;
            new_wagon->prev = last;
        }

        t->wagon_count++;

        int to_load = (remaining_quantity < 1000 / m_type->weight) ? remaining_quantity : 1000 / m_type->weight;
        new_wagon->current_weight += to_load * m_type->weight;
        new_wagon->box_count += to_load;
        remaining_quantity -= to_load;

        LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
        new_material->type = m_type;
        new_material->next = new_wagon->loaded_materials;
        new_wagon->loaded_materials = new_material;

        m_type->loaded += to_load;

        printf("Yeni Vagon %d eklendi ve %s tipi %d adet malzeme yüklendi. (Toplam yüklü: %d)\n",
               new_wagon->wagon_id, m_type->name, to_load, m_type->loaded);
    }
}



void add_to_specific_wagon(int wagon_id, int quantity, MaterialType *m_type, Wagon **head, Train *t)
{
    Wagon *temp = *head;

    // Eğer hiç vagon yoksa baştan başla
    if (*head == NULL)
    {
        printf("Hiç vagon bulunamadı. ID %d'ye kadar vagon oluşturulacak...\n", wagon_id);
        for (int id = 1; id <= wagon_id; id++)
        {
            Wagon *new_wagon = create_wagon(id);

            // Yeni vagonu trenin sonuna ekle
            if (*head == NULL)
            {
                *head = new_wagon;
                t->first_wagon = *head;
            }
            else
            {
                Wagon *temp_last = *head;
                while (temp_last->next != NULL)
                {
                    temp_last = temp_last->next;
                }
                temp_last->next = new_wagon;
                new_wagon->prev = temp_last;
            }

            t->wagon_count++; // Vagon sayısını artır
        }

        // Belirtilen vagona git
        temp = *head;
        while (temp->wagon_id != wagon_id)
        {
            temp = temp->next;
        }
    }
    else
    {
        // Vagon zincirini kontrol et, eksik vagon varsa oluştur
        while (temp->next != NULL && temp->wagon_id < wagon_id)
        {
            temp = temp->next;
        }

        // Eksik vagonları doldur
        while (temp->wagon_id < wagon_id)
        {
            Wagon *new_wagon = create_wagon(temp->wagon_id + 1);
            temp->next = new_wagon;
            new_wagon->prev = temp;

            t->wagon_count++;
            temp = new_wagon;
        }
    }

    // Şimdi belirtilen vagon yükleme için hazır
    if (temp->loaded_materials != NULL && temp->loaded_materials->type->weight < m_type->weight)
    {
        printf("Vagon %d mevcut malzeme türü ile uyumlu değil. Yükleme yapılmadı.\n", wagon_id);
        return;
    }

    // Vagonun kapasitesini hesapla
    int available_space = (temp->max_weight - temp->current_weight) / m_type->weight;
    int to_load = (quantity < available_space) ? quantity : available_space;

    // Malzeme yükleme
    temp->current_weight += to_load * m_type->weight;
    temp->box_count += to_load;
    quantity -= to_load;

    LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
    if (new_material == NULL)
    {
        printf("Bellek tahsis edilemedi.\n");
        exit(1);
    }
    new_material->type = m_type;
    new_material->next = temp->loaded_materials;
    temp->loaded_materials = new_material;

    printf("Vagon %d: %s tipi %d adet malzeme yüklendi.\n", wagon_id, m_type->name, to_load);

    // Eğer hala kalan malzeme varsa bir sonraki vagonu oluştur
    if (quantity > 0)
    {
        add_to_specific_wagon(temp->wagon_id + 1, quantity, m_type, head, t);
    }
}

void material_status(Train *train)
{
    Wagon *temp = train->first_wagon; // first wagon train.h de var

    printf("== Material Status ==\n");

    if (temp == NULL)
    {
        printf("No wagons available.\n");
        return;
    }
    printf("Train ID: %s\n", train->train_id);
    printf("Total wagons: %d\n", train->wagon_count);
    while (temp != NULL)
    {
        printf("WAGON:%d:1000.00:%.2f\n", temp->wagon_id, temp->current_weight);

        LoadedMaterial *loaded = temp->loaded_materials;

        if (temp->loaded_materials == NULL) {
    printf("Wagon ID %d: No materials loaded.\n", temp->wagon_id);
}
 printf("while ustu\n");
        while (loaded != NULL)
        {
          
            for(int i=0;i<loaded->type->quantity;i++){
               
                if (loaded->type->weight == 200.00)
                {
                    printf("LARGE\n");
                }
                else if (loaded->type->weight == 150.00)
                {
                    printf("MEDIUM\n");
                }
                else if (loaded->type->weight == 100.00)
                {
                    printf("SMALL\n");
                }


            }
            
            loaded = loaded->next;
        }
        temp = temp->next;
    }
    printf("\n");
}

MaterialType *create_mtr(int quantity, char type)
{

    MaterialType *m = (MaterialType *)malloc(sizeof(MaterialType));
    if (m == NULL)
    {
        printf("Lack of memory!");
        exit(1);
    }
    
    m->loaded = 0;
    
    if (toupper(type) == 'L')
    {

        m->weight = 200.00;
        strcpy(m->name, "LARGE");
        m->quantity = quantity;
    }

    if (toupper(type) == 'M')
    {

        m->weight = 150.00;
        strcpy(m->name, "MEDIUM");
        m->quantity = quantity;
    }

    if (toupper(type) == 'S')
    {

        m->weight = 100.00;
        strcpy(m->name, "SMALL");
        m->quantity = quantity;
    }

    return m;
}

// Materyali silme fonksiyonu
void unload_specific_material(MaterialType *m_type, int quantity, Wagon **head)
{
    if (*head == NULL)
    {
        printf("Train is empty.\n");
        return;
    }

    Wagon *temp = *head; // Baştan başlayarak kontrol et

    while (temp != NULL) // Tüm vagonları sırayla gez
    {
        LoadedMaterial *material = temp->loaded_materials;

        while (material != NULL) // Malzeme listesini kontrol et
        {
            if (strcmp(material->type->name, m_type->name) == 0) // Tür eşleşmesi
            {
                if (material->type->quantity >= quantity) // Yeterli miktar var mı?
                {
                    material->type->quantity -= quantity;
                    printf("Removed %d of %s from Wagon %d.\n", quantity, m_type->name, temp->wagon_id);

                    if (material->type->quantity == 0) // Miktar sıfırsa malzemeyi sil
                    {
                        if (material->prev != NULL)
                        {
                            material->prev->next = material->next;
                        }
                        else
                        {
                            temp->loaded_materials = material->next; // Baş malzemeyse güncelle
                        }

                        if (material->next != NULL)
                        {
                            material->next->prev = material->prev;
                        }

                        free(material);
                        printf("%s material removed completely from Wagon %d.\n", m_type->name, temp->wagon_id);
                    }
                    return;
                }
                else
                {
                    printf("Not enough %s material in Wagon %d.\n", m_type->name, temp->wagon_id);
                    return;
                }
            }
            material = material->next;
        }

        temp = temp->next; // Bir sonraki vagona geç
    }
    printf("Material of type %s not found in the train.\n", m_type->name);
}
void unloadMaterial(Train *train, MaterialType *material, int quantity)
{
    Wagon *temp = train->first_wagon;
    int remaining_quantity = quantity;

    while (temp != NULL && remaining_quantity > 0)
    {
        LoadedMaterial *current_material = temp->loaded_materials;
        while (current_material != NULL && remaining_quantity > 0)
        {
            // Eğer uygun malzeme bulunursa
            if (current_material->type == material)
            {
                int to_unload = (current_material->type->weight <= remaining_quantity) ? remaining_quantity : current_material->type->weight;

                // Yükün boşaltılması işlemleri
                printf("Unloading %d of %s from wagon %d.\n", to_unload, current_material->type->name, temp->wagon_id);
                temp->current_weight -= to_unload * current_material->type->weight;
                temp->box_count -= to_unload;
                remaining_quantity -= to_unload;

                // Eğer malzeme tamamen boşaltıldıysa, listeden çıkar
                if (remaining_quantity == 0)
                {
                    printf("Material %s is completely unloaded. Removing it from the list.\n", current_material->type->name);
                    // Malzemenin tamamen boşaltılmasını sağlamak için uygun işlemleri yapın.
                    if (current_material->next != NULL)
                    {
                        current_material = current_material->next; // Listedeki sonraki malzemeye geç
                    }
                    else
                    {
                        temp->loaded_materials = NULL; // Liste boşaltıldıysa, vagonun malzeme listesine NULL ata
                    }
                }
            }
            else
            {
                current_material = current_material->next; // Farklı bir malzeme varsa, bir sonraki malzemeye geç
            }
        }
        temp = temp->next;  // Bir sonraki vagona geç
    }

    // Eğer hala boşaltılacak malzeme kaldıysa
    if (remaining_quantity > 0)
    {
        printf("Remaining quantity of %s could not be unloaded: %d\n", material->name, remaining_quantity);
    }
    else
    {
        printf("Unloading process completed for %s.\n", material->name);
    }
}
