#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to save.\n");
        return;
    }

    FILE *fptr = fopen("contacts.txt", "w");
    if (fptr == NULL)
    {
        printf("Sorry: Unable to open file for saving contacts.\n");
        return;
    }
    fprintf(fptr, "%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("Contacts saved successfully to contact.txt.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL)
    {
        printf("Sorry: Unable to open contacts.\n");
        return;
    }
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
    // printf("Contacts loaded successfully from contacts.txt.\n");
}
