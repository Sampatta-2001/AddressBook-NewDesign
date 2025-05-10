#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    printf("----------------------------------------------------------------\n");
    printf("\t\tLIST OF CONTACTS\t\n");
    printf("----------------------------------------------------------------\n");
    printf("| Name\t\t| Phonenumber\t | Email\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) // this loop will list the all contacts
    {
        printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("----------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    char Name[50], Phone_no[50], emailid[50]; // declaration of variables
    char ch;
    printf("Enter the Name : "); // read input from user
    getchar();
    scanf(" %[^\n]", Name);

    do
    {
        int duplicate = 0;
        printf("Enter Phone no. : "); // read phone no. and validate
        getchar();
        scanf("%s", Phone_no);
        if (strlen(Phone_no) != 10 || strspn(Phone_no, "0123456789") != strlen(Phone_no))
        {
            printf("Invalid phone number.\n");
            return;
        }
        // Check if phone no. is already present
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(Phone_no, addressBook->contacts[i].phone) == 0)
            {
                duplicate = 1;
                printf("Phone number is present in the list\n");
                printf("Do you want to Re-Enter the Phone number ? (y or n) : ");
                getchar();
                scanf(" %c", &ch);
                break;
            }
        }
        if (!duplicate)
            break;

    } while (ch == 'y' || ch == 'Y');

    do
    {
        int duplicate = 0;
        printf("Enter Email ID : "); // read email
        getchar();
        scanf("%s", emailid);
        if (strchr(emailid, '@') == NULL || strstr(emailid, ".com") == NULL)
        {
            printf("Invalid email ID.\n");
            return;
        }
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(emailid, addressBook->contacts[i].email) == 0) // validate email
            {
                duplicate = 1;
                printf("Email ID is already present in the list\n");
                printf("Do you want to Re-Enter the Email ID ? (y or n) : ");
                getchar();
                scanf(" %c", &ch);
                break;
            }
        }
        if (!duplicate)
            break;

    } while (ch == 'y' || ch == 'Y');

    // store the contact details
    strcpy(addressBook->contacts[addressBook->contactCount].name, Name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, Phone_no);
    strcpy(addressBook->contacts[addressBook->contactCount].email, emailid);

    // increament contact count
    addressBook->contactCount++;
    printf("Contact added successfully.\n");
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int searchOption;
    char str[50];
    int flag = 0;
    printf("----------------------------------------------------------------\n");
    printf("\t\t\tSEARCH THE CONTACT\t\n");
    printf("----------------------------------------------------------------\n");
    printf("Search By: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar();

    switch (searchOption)
    {
    case 1:
        printf("Enter the name you want to search : ");
        scanf(" %[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, str) != NULL)
            {
                printf("----------------------------------------------------------------\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("----------------------------------------------------------------\n");
                flag = 1;
            }
        }
        break;

    case 2:
        printf("Enter the phone number  you want to search : ");
        scanf("%10[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("----------------------------------------------------------------\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("----------------------------------------------------------------\n");
                flag = 1;
            }
        }
        break;

    case 3:
        printf("Enter the email you want to search : ");
        scanf("%[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("----------------------------------------------------------------\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("----------------------------------------------------------------\n");
                flag = 1;
            }
        }
        break;
    default:
        printf("Invalid option.\n");
        return;
    }
    if (flag == 0)
    {
        printf("Contact not found.\n");
    }
}

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to edit.\n");
        return;
    }

    printf("----------------------------------------------------------------\n");
    printf("\t\t\tEDIT THE CONTACT\t\n");
    printf("----------------------------------------------------------------\n");

    int searchOption, pos, i;
    char str[50];
    int foundIndexes[MAX_CONTACTS];
    int matchCount = 0;

    printf("Search By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar(); // Clear newline

    switch (searchOption)
    {
    case 1:
        printf("Enter the name you want to search: ");
        scanf(" %[^\n]", str);
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, str) != NULL)
            {
                printf("%d. %s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundIndexes[matchCount++] = i;
            }
        }
        break;

    case 2:
        printf("Enter the phone number you want to search: ");
        scanf(" %[^\n]", str);
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("%d. %s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundIndexes[matchCount++] = i;
            }
        }
        break;

    case 3:
        printf("Enter the email you want to search: ");
        scanf(" %[^\n]", str);
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("%d. %s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundIndexes[matchCount++] = i;
            }
        }
        break;

    default:
        printf("Invalid option.\n");
        return;
    }

    if (matchCount == 0)
    {
        printf("Contact not found.\n");
        return;
    }

    int found;
    if (matchCount == 1)
    {
        found = foundIndexes[0];
    }
    else
    {
        printf("Enter the position you want to edit: ");
        scanf("%d", &pos);

        if (pos < 1 || pos > matchCount)
        {
            printf("Invalid position selected.\n");
            return;
        }
        found = foundIndexes[pos - 1];
    }

    int editOption;
    printf("What do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &editOption);
    getchar(); // Clear newline after scanf

    switch (editOption)
    {
    case 1:
    {
        char newName[50];
        printf("Enter new name: ");
        scanf(" %[^\n]", newName);

        // Check if name already exists
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (i != found && strcmp(addressBook->contacts[i].name, newName) == 0)
            {
                printf("Name already exists.\n");
                return;
            }
        }
        strcpy(addressBook->contacts[found].name, newName);
        printf("Name updated successfully.\n");
        break;
    }
    case 2:
    {
        char newPhone[20];
        printf("Enter new phone: ");
        scanf(" %[^\n]", newPhone);

        // Validate phone
        if (strlen(newPhone) != 10 || strspn(newPhone, "0123456789") != strlen(newPhone))
        {
            printf("Invalid phone number.\n");
            return;
        }

        // Check if phone already exists
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (i != found && strcmp(addressBook->contacts[i].phone, newPhone) == 0)
            {
                printf("Phone number already exists.\n");
                return;
            }
        }
        strcpy(addressBook->contacts[found].phone, newPhone);
        printf("Phone updated successfully.\n");
        break;
    }
    case 3:
    {
        char newEmail[50];
        printf("Enter new email: ");
        scanf(" %[^\n]", newEmail);

        // Validate email
        if (strchr(newEmail, '@') == NULL || strstr(newEmail, ".com") == NULL)
        {
            printf("Invalid email format.\n");
            return;
        }

        // Check if email already exists
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (i != found && strcmp(addressBook->contacts[i].email, newEmail) == 0)
            {
                printf("Email already exists.\n");
                return;
            }
        }
        strcpy(addressBook->contacts[found].email, newEmail);
        printf("Email updated successfully.\n");
        break;
    }
    default:
        printf("Invalid choice.\n");
        return;
    }
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    printf("----------------------------------------------------------------\n");
    printf("\t\tDELETE THE CONTACT\t\n");
    printf("----------------------------------------------------------------\n");
    int searchOption;
    char str[50];
    int flag = 0;
    char ch;
    int index;
    printf("Search to delete contact by: \n"); // Give menu for searching the contact
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar();
    switch (searchOption) // Read the value to search
    {
    case 1:
        printf("Enter the name : ");
        scanf(" %[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].name) == 0)
            {
                printf("Name is prsent in the List\n");
                printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull\n");
                    break;
                }
                else if (ch == 'n')
                {
                    ("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!\n");
                    break;
                }
            }
        }
        break;

    case 2:
        printf("Enter the Phonenumber : ");
        scanf(" %10[^\n]", str);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("phone number is prsent in the List\n");
                printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull\n");
                    break;
                }
                else if (ch == 'n')
                {
                    ("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!\n");
                    break;
                }
            }
        }
        break;

    case 3:
        printf("Enter the Email id : ");
        scanf(" %[^\n]", str);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("Email id is prsent in the List\n");
                printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull\n");
                    break;
                }
                else if (ch == 'n')
                {
                    ("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!\n");
                    break;
                }
            }
        }
        break;

    default:
        printf("Invalid option.\n");
        return;
    }
    if (flag == 0) // If contact is not found
    {
        printf("Contact not found.\n");
        return;
    }
}
