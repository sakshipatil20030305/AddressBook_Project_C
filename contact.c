#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // New

#include "contact.h"
#include "file.h"
#include "populate.h"

/*
Name: Sakshi Sharad Patil.
Date: 08/07/2025
Project: AddressBook Project_01
*/

void listContacts(AddressBook *addressBook) 
{
    // Check if address book is empty
    if (addressBook->contactCount == 0) 
    {
        // Notify user no contacts exist
        printf("No contacts found.\n");
        return;
    }
    // Print table header with formatted columns
    printf("\n%-5s %-20s %-15s %-30s\n","No.", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------\n");
    
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Print formatted contact information
        printf("%-5d %-20s %-15s %-30s\n", i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    
    printf("-----------------------------------------------------------\n");
    // Display total contact count
    printf("Total contacts: %d\n", addressBook->contactCount);
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf("Address book is full!\n");
        return;
    }

    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // ---------- NAME VALIDATION ----------
    char name[50];
    int valid = 0;
    
    printf("Enter name: ");
    if (fgets(name, 50, stdin) == NULL) {
        printf("Error reading name.\n");
        return;
    }
    name[strcspn(name, "\n")] = '\0';
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    // ---------- PHONE NUMBER VALIDATION ----------
    char number[20];
    valid = 0;
    while (!valid) {
        printf("Enter phone number (10 digits): ");
        if (fgets(number, 20, stdin) == NULL) {
            printf("Error reading input!\n");
            continue;
        }
        number[strcspn(number, "\n")] = '\0';

        // Check length
        if (strlen(number) != 10) 
        {
            printf("Phone number must be exactly 10 digits!\n");
            continue;
        }

        // Check digits only
        valid = 1;
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit(number[i])) 
            {
                printf("Phone number must contain only digits!\n");
                valid = 0;
                break;
            }
        }

        // Check uniqueness
        if (valid)
        {
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, number) == 0) 
                {
                    printf("This phone number already exists in contacts!\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].phone, number);

    // ---------- EMAIL VALIDATION ----------
    char mail[50];
    valid = 0;
    while (!valid) 
    {
        printf("Enter email: ");
        if (fgets(mail, 50, stdin) == NULL)
        {
            printf("Error reading input!\n");
            continue;
        }
        mail[strcspn(mail, "\n")] = '\0'; // Finds the newline (\n) character in the string mail | Replaces it with a null terminator (\0)

        int hasUppercase = 0;
        for (int i = 0; mail[i]; i++)
        {
            if (isupper(mail[i]))
            {
                hasUppercase = 1;
                break;
            }
        }

        if (hasUppercase)
        {
            printf("Email must be in lowercase! Do not use capital letters.\n");
            continue;
        }

        // Check @ count
        int atCount = 0;
        for (int i = 0; mail[i]; i++) 
        {
            if (mail[i] == '@') atCount++;
        }
        if (atCount != 1) // True if more than 1
        {
            printf("Email must contain exactly one '@'\n");
            continue;
        }

        char *atPos = strchr(mail, '@');
        char *dotComPos = strstr(mail, ".com");

        // Check @ position and .com placement
        if (atPos == NULL || atPos == mail || *(atPos + 1) == '\0')
        {
            printf("Email must contain '@' with characters before and after it!\n");
            continue;
        }

        if (dotComPos == NULL || (dotComPos != mail + strlen(mail) - 4))
        {
            printf("Email must end with '.com'!\n");
            continue;
        }

        if (dotComPos - atPos <= 1) 
        {
            printf("Must have at least 1 character between '@' and '.com'!\n");
            continue;
        }

        // Allowed characters check
        valid = 1;
        for (int i = 0; mail[i]; i++)
        {
            char c = mail[i];
            if (!(isalnum(c) || c == '@' || c == '.' || c == '_' || c == '-'))
            {
                printf("Invalid character '%c' in email! Only letters, digits, @ . _ - allowed.\n", c);
                valid = 0;
                break;
            }
        }

        // Check uniqueness
        if (valid)
        {
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, mail) == 0) 
                {
                    printf("This email already exists in contacts!\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    // Final step
    addressBook->contactCount++;
    printf("Contact added successfully!\n");
}


void searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("\nNo contacts to search.\n");
        return;
    }

    int searchChoice;
    char searchTerm[50];
    int found = 0;

    // Search method selection with validation
    while (1) 
    {
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Back to Menu\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &searchChoice) != 1) 
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (searchChoice == 4) 
        {
            return; // Return to main menu
        }

        if (searchChoice < 1 || searchChoice > 3) 
        {
            printf("Invalid choice! Please select 1-4.\n");
            continue;
        }
        break;
    }

    // Get search term
    printf("Enter search term: ");
    scanf(" %49[^\n]", searchTerm);
    while (getchar() != '\n');

    // Prepare for case-insensitive search
    char lowercaseTerm[50];
    strcpy(lowercaseTerm, searchTerm);
    for (int i = 0; lowercaseTerm[i]; i++) 
    {
        lowercaseTerm[i] = tolower(lowercaseTerm[i]);
    }

    printf("\nSearch results for \"%s\":\n", searchTerm);
    printf("-----------------------------------------------------------\n");
    printf("%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------\n");

    // Search through contacts
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;
        char lowercaseName[50];
        char lowercaseEmail[50];

        switch (searchChoice) 
        {
            case 1: // Name search (partial match)
                strcpy(lowercaseName, addressBook->contacts[i].name);
                for (int j = 0; lowercaseName[j]; j++) 
                {
                    lowercaseName[j] = tolower(lowercaseName[j]);
                }
                match = (strstr(lowercaseName, lowercaseTerm) != NULL);
                break;

            case 2: // Phone search (exact match)
                match = (strcmp(addressBook->contacts[i].phone, searchTerm) == 0);
                break;

            case 3: // Email search (partial match, case-insensitive)
                strcpy(lowercaseEmail, addressBook->contacts[i].email);
                for (int j = 0; lowercaseEmail[j]; j++) 
                {
                    lowercaseEmail[j] = tolower(lowercaseEmail[j]);
                }
                match = (strstr(lowercaseEmail, lowercaseTerm) != NULL);
                break;
        }

        if (match) 
        {
            printf("%-20s %-15s %-30s\n", 
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found++;
        }
    }

    printf("-----------------------------------------------------------\n");
    
    if (found > 0) 
    {
        printf("Found %d %s.\n", found, (found == 1) ? "match" : "matches");
    } else 
    {
        printf("No contacts found matching \"%s\"\n", searchTerm);
    }

    // Option to search again
    char choice;
    printf("\nSearch again? (y/n): ");
    scanf(" %c", &choice);
    while (getchar() != '\n');
    
    if (tolower(choice) == 'y') 
    {
        searchContact(addressBook); // Recursive call
    }
}

void editContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts to edit.\n");
        return;
    }

    int searchChoice, fieldChoice;
    char searchTerm[50];
    int matches[MAX_CONTACTS];
    int matchCount = 0;

    // Search method selection with validation
    while (1) 
    {
        printf("\nEdit by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Cancel\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &searchChoice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        if (searchChoice == 4) 
        {
            printf("Edit cancelled.\n");
            return;
        }

        if (searchChoice < 1 || searchChoice > 3) 
        {
            printf("Invalid choice! Please select 1-4.\n");
            continue;
        }
        break;
    }

    // Get search term
    printf("Enter search term: ");
    scanf(" %49[^\n]", searchTerm);
    while (getchar() != '\n'); // Clear buffer

    // Find matching contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        int match = 0;
        switch (searchChoice) {
            case 1: match = (strstr(addressBook->contacts[i].name, searchTerm) != NULL); break;
            case 2: match = (strcmp(addressBook->contacts[i].phone, searchTerm) == 0); break;
            case 3: match = (strcmp(addressBook->contacts[i].email, searchTerm) == 0); break;
        }
        if (match) matches[matchCount++] = i;
    }

    if (matchCount == 0)
    {
        printf("No contacts found matching '%s'\n", searchTerm);
        return;
    }

    // Handle single match automatically
    int selectedIndex;
    if (matchCount == 1)
    {
        selectedIndex = matches[0];
        printf("\nFound 1 matching contact:\n");
    } 
    else 
    {
        // Display multiple matches
        printf("\nFound %d matching contacts:\n", matchCount);
        printf("-----------------------------------------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < matchCount; i++)
        {
            int idx = matches[i];
            printf("%-5d %-20s %-15s %-30s\n", 
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }
        printf("-----------------------------------------------------------\n");

        // Contact selection with validation
        while (1) {
            printf("Select contact to edit (1-%d, 0 to cancel): ", matchCount);
            if (scanf("%d", &selectedIndex) != 1)
            {
                printf("Invalid input! Please enter a number.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (selectedIndex == 0) {
                printf("Edit cancelled.\n");
                return;
            }

            if (selectedIndex < 1 || selectedIndex > matchCount)
            {
                printf("Invalid selection! Please choose between 1-%d.\n", matchCount);
                continue;
            }
            break;
        }
        selectedIndex = matches[selectedIndex - 1];
    }

    Contact *selected = &addressBook->contacts[selectedIndex];

    // Field selection with validation
    while (1) 
    {
        printf("\nEditing contact:\n");
        printf("1. Name: %s\n", selected->name);
        printf("2. Phone: %s\n", selected->phone);
        printf("3. Email: %s\n", selected->email);
        printf("4. Cancel\n");
        printf("Select field to edit (1-4): ");
        
        if (scanf("%d", &fieldChoice) != 1)
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (fieldChoice == 4)
        {
            printf("Edit cancelled.\n");
            return;
        }

        if (fieldChoice < 1 || fieldChoice > 3)
        {
            printf("Invalid choice! Please select 1-4.\n");
            continue;
        }
        break;
    }

    // Field editing with validation
    char newValue[50];
    int valid;

    switch (fieldChoice)
    {
        case 1: // Edit name
            printf("Enter new name: ");
            if (fgets(newValue, 50, stdin) != NULL)
            {
                newValue[strcspn(newValue, "\n")] = '\0'; // Remove newline
                strcpy(selected->name, newValue);
                printf("Name updated successfully.\n");
            } 
            else
            {
                printf("Error reading name input.\n");
            }
            break;

        case 2: // Edit phone
            do {
                valid = 1;
                printf("Enter new phone (10 digits): ");
                fgets(newValue, 20, stdin);
                newValue[strcspn(newValue, "\n")] = '\0';

                if (strlen(newValue) != 10)
                {
                    printf("Phone must be exactly 10 digits!\n");
                    valid = 0;
                    continue;
                }

                for (int i = 0; i < 10; i++)
                {
                    if (!isdigit(newValue[i]))
                    {
                        printf("Phone must contain only digits!\n");
                        valid = 0;
                        break;
                    }
                }

                if (valid)
                {
                    for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                        if (i != selectedIndex && strcmp(addressBook->contacts[i].phone, newValue) == 0) {
                            printf("This phone number already exists!\n");
                            valid = 0;
                            break;
                        }
                    }
                }
            } while (!valid);
            strcpy(selected->phone, newValue);
            break;

        case 3: // Edit email
            do {
                valid = 1;
                printf("Enter new email: ");
                fgets(newValue, 50, stdin);
                newValue[strcspn(newValue, "\n")] = '\0';

                int hasUppercase = 0;
                for (int i = 0; newValue[i]; i++)
                {
                    if (isupper(newValue[i]))
                    {
                        hasUppercase = 1;
                        break;
                    }
                }

                if (hasUppercase)
                {
                    printf("Email must be in lowercase! Do not use capital letters\n");
                    valid = 0;
                    continue;
                }

                // Validate email format (same as createContact)
                int atCount = 0;
                for (int i = 0; newValue[i]; i++) 
                {
                    if (newValue[i] == '@') atCount++;
                }
                if (atCount != 1) 
                {
                    printf("Email must contain exactly one '@'\n");
                    valid = 0;
                    continue;
                }

                char *atPos = strchr(newValue, '@');
                char *dotComPos = strstr(newValue, ".com");

                if (atPos == NULL || atPos == newValue || *(atPos + 1) == '\0') 
                {
                    printf("Invalid email format! Must have text before and after '@'\n");
                    valid = 0;
                    continue;
                }

                if (dotComPos == NULL || (dotComPos != newValue + strlen(newValue) - 4))
                {
                    printf("Email must end with '.com'\n");
                    valid = 0;
                    continue;
                }

                if (dotComPos - atPos <= 1)
                {
                    printf("Must have at least 1 character between '@' and '.com'\n");
                    valid = 0;
                    continue;
                }

                for (int i = 0; newValue[i]; i++) 
                {
                    char c = newValue[i];
                    if (!(isalnum(c) || c == '@' || c == '.' || c == '_' || c == '-'))
                    {
                        printf("Invalid character '%c'! Only letters, digits, @ . _ - allowed.\n", c);
                        valid = 0;
                        break;
                    }
                }

                if (valid) 
                {
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (i != selectedIndex && strcmp(addressBook->contacts[i].email, newValue) == 0)
                        {
                            printf("This email already exists!\n");
                            valid = 0;
                            break;
                        }
                    }
                }
            } while (!valid);
            strcpy(selected->email, newValue);
            break;
    }

    printf("\nContact updated successfully!\n");
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts to delete.\n");
        return;
    }

    int searchChoice, selection;
    char searchTerm[50];
    int matches[MAX_CONTACTS];
    int matchCount = 0;

    // Search method selection with validation
    while (1) {
        printf("\nDelete by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Cancel\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &searchChoice) != 1) 
        {
            printf("Invalid input! Please enter a number (1-4).\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (searchChoice == 4) 
        {
            printf("Deletion cancelled.\n");
            return;
        }

        if (searchChoice < 1 || searchChoice > 3) 
        {
            printf("Invalid choice! Please select 1-4.\n");
            continue;
        }
        break;
    }

    // Get search term
    printf("Enter search term: ");
    scanf(" %49[^\n]", searchTerm);
    while (getchar() != '\n');

    // Find matching contacts
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int match = 0;
        switch (searchChoice)
        {
            case 1: match = (strstr(addressBook->contacts[i].name, searchTerm) != NULL); break;
            case 2: match = (strcmp(addressBook->contacts[i].phone, searchTerm) == 0); break;
            case 3: match = (strcmp(addressBook->contacts[i].email, searchTerm) == 0); break;
        }
        if (match) matches[matchCount++] = i;
    }

    if (matchCount == 0)
    {
        printf("\nNo contacts found matching '%s'\n", searchTerm);
        return;
    }

    // Handle single match automatically
    int selectedIndex;
    if (matchCount == 1)
    {
        selectedIndex = matches[0];
        printf("\nFound 1 matching contact:\n");
    } 
    else
    {
        // Display multiple matches
        printf("\nFound %d matching contacts:\n", matchCount);
        printf("-----------------------------------------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < matchCount; i++)
        {
            int idx = matches[i];
            printf("%-5d %-20s %-15s %-30s\n", 
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }
        printf("-----------------------------------------------------------\n");

        // Contact selection with validation
        while (1) 
        {
            printf("Select contact to delete (1-%d, 0 to cancel): ", matchCount);
            if (scanf("%d", &selection) != 1) 
            {
                printf("Invalid input! Please enter a number.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (selection == 0)
            {
                printf("Deletion cancelled.\n");
                return;
            }

            if (selection < 1 || selection > matchCount)
            {
                printf("Invalid selection! Please choose between 1-%d.\n", matchCount);
                continue;
            }
            break;
        }
        selectedIndex = matches[selection - 1];
    }

    // Confirmation
    Contact *selected = &addressBook->contacts[selectedIndex];
    char confirm;
    printf("\nContact to be deleted:\n");
    printf("Name: %s\n", selected->name);
    printf("Phone: %s\n", selected->phone);
    printf("Email: %s\n", selected->email);
    
    while (1)
    {
        printf("\nAre you sure? (y/n): ");
        scanf(" %c", &confirm);
        while (getchar() != '\n');
        
        confirm = tolower(confirm);
        if (confirm == 'n') 
        {
            printf("Deletion cancelled.\n");
            return;
        }
        else if (confirm == 'y')
        {
            break;
        }
        else
        {
            printf("Invalid input! Please enter 'y' or 'n'.\n");
        }
    }

    // Perform deletion
    for (int i = selectedIndex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("\nContact deleted successfully!\n");
}