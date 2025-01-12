#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"
#include "wagon.h"
#include "train.h"
#include "file_ops.h"
#include "utils.h"
#define t_id "123"

#define FILE_NAME "C:\\Users\\btlbi\\file.txt"


int main()
{ // Wagon *head=(Wagon)malloc(sizeof(Wagon));//?
    Train *t = (Train *)malloc(sizeof(Train));
    t->first_wagon = NULL;
    t->wagon_count = 0;
    strcpy(t->train_id, t_id);

    int action, quantity = 0;
    char m_type;

    while (1)
    {

        interface_menu();
        scanf("%d", &action);

        switch (action)
        {
        case 1:
            print_file_contents(FILE_NAME);
            break;
        case 2:
            while (quantity != -1)
            {
                printf("\n");
                printf("Enter the quantity of material:(-1 for terminate the loading process):");
                scanf("%d", &quantity);

                if (quantity == -1 || quantity < 1)
                {
                    break;
                }

                printf("Enter the type of material:('L' for Large,'M' for Medium,'S' for Small):");
                scanf(" %c", &m_type);

                MaterialType *m = create_mtr(quantity, m_type);
                load_material(quantity, m, &(t->first_wagon), t);
                // load_material(quantity, m, head,t);

                free(m);
            }
            quantity = 0;
            m_type = '\0';
            break;
        case 3:
            int w_id;

            printf("Enter the specific wagon number to load:");
            scanf("%d", &w_id);

            printf("Enter the quantity of material: ");

            scanf("%d", &quantity);
            if (quantity == -1 || quantity < 1)
            {
                break;
            }

            printf("Enter the type of material:('L' for Large,'M' for Medium,'S' for Small):");
            scanf(" %c", &m_type);

            MaterialType *m3 = create_mtr(quantity, m_type);

            add_to_specific_wagon(w_id, quantity, m3, &(t->first_wagon), t);

            quantity = 0;
            m_type = '\0';
            free(m3);

            break;
        case 4:
            while (quantity != -1)
            {
                printf("Enter the quantity of material:(-1 for terminate the unloading process):");

                scanf("%d", &quantity);
                if (quantity == -1 || quantity < 1)
                {
                    break;
                }

                printf("Enter the type of material:('L' for Large,'M' for Medium,'S' for Small):");
                scanf(" %c", &m_type);

                MaterialType *m4 = create_mtr(quantity, m_type);
                unloadMaterial(t, m4, quantity);

                free(m4);
            }
            quantity = 0;
            m_type = '\0';
            break;
        case 5:
            int wagon_id;

            printf("Enter the specific wagon number to unload:");
            scanf("%d", &wagon_id);

            printf("Enter the quantity of material: ");

            scanf("%d", &quantity);
            if (quantity == -1 || quantity < 1)
            {
                break;
            }

            printf("Enter the type of material:('L' for Large,'M' for Medium,'S' for Small):");
            scanf(" %c", &m_type);

            MaterialType *m5 = create_mtr(quantity, m_type);

            unload_specific_material(m5, quantity, &(t->first_wagon));
            free(m5);

            quantity = 0;
            m_type = '\0';
            break;
        case 6:
            train_status(t->first_wagon, t);
            break;
        case 7:
            material_status(t);
            break;
        case 8:
            printf("Train is empty now.");
            emptyTrain(t);
            break;
        case 9:
            train_status_to_file(t, FILE_NAME);
            break;
        case 10:
            printf("Logged out.\n");
            exit(1);
            break;
        default:
            printf("Invalid transaction.\n");
        }
    }
    return 0;
}
