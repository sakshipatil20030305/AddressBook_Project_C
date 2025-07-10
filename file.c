#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include "file.h"   // Include custom header for AddressBook structure

// Saves contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *file = fopen("Addressbook.csv", "w"); // Open file for writing
    if (file == NULL)  // Check if file opened successfully
    {
        printf("Error opening file for writing.\n"); 
        return; // Exit function on error
    }

    // Loop through all contacts
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Create buffers for CSV-safe data
        char csvName[50], csvPhone[20], csvEmail[50];

        // Copy original name to buffer
        strcpy(csvName, addressBook->contacts[i].name);

        // Copy original phone to buffer
        strcpy(csvPhone, addressBook->contacts[i].phone);
        
        // Copy original email to buffer
        strcpy(csvEmail, addressBook->contacts[i].email);

        // Sanitize name: replace commas with spaces
        for(char *p = csvName; *p; p++)
        {
            if(*p == ',') // Check for comma
            {
                *p = ' '; // Replace comma with space
            }     
        }
        // Sanitize phone: replace commas with spaces
        for(char *p = csvPhone; *p; p++)
        {
            if(*p == ',') 
            {
                *p = ' '; 
            }     
        }
        // Sanitize email: replace commas with spaces
        for(char *p = csvEmail; *p; p++)
        {
            if(*p == ',') 
            {
                *p = ' '; 
            }     
        }
        // Write sanitized data to file
        fprintf(file, "%s, %s, %s\n", csvName, csvPhone, csvEmail);       
    }

    fclose(file); // Close the file
    printf("Contacts saved to file.\n"); // Confirm save completion
}

// Loads contacts from a CSV file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *file = fopen("Addressbook.csv", "r"); // Open file for reading
    if (file == NULL)  // Check if file exists
    {
        // Notify if file doesn't exist
        printf("No existing contacts file found. Starting fresh.\n");
        return; 
    }

    addressBook->contactCount = 0; // Reset contact counter

    // Read records until EOF or max contacts reached
    while (fscanf(file, " %49[^,], %19[^,], %49[^\n]\n", 
                 addressBook->contacts[addressBook->contactCount].name,
                 addressBook->contacts[addressBook->contactCount].phone,
                 addressBook->contacts[addressBook->contactCount].email) == 3) 
                 {
                    addressBook->contactCount++; // Increment contact count
                    // Stop if maximum capacity reached
                    if (addressBook->contactCount >= MAX_CONTACTS)
                    {
                        break; // Exit loop
                    } 
                 }
    fclose(file); // Close the file
    printf("Contacts loaded from file.\n"); // Confirm load completion
}