# Address Book Management System

## Overview
This is a C program that implements an address book management system. It allows users to create, search, edit, delete, and list contacts. The contacts are stored in a CSV file and persist between program runs.

## Features
- **Create Contact**: Add new contacts with name, phone number, and email
- **Search Contact**: Search contacts by name, phone, or email (partial matches supported)
- **Edit Contact**: Modify existing contact information
- **Delete Contact**: Remove contacts from the address book
- **List Contacts**: View all contacts in a formatted table
- **Data Persistence**: Contacts are automatically saved to and loaded from a CSV file

## Data Validation
The program includes robust validation for all contact fields:
- **Name**: Must be non-empty
- **Phone Number**: Must be exactly 10 digits and unique
- **Email**: Must follow standard email format (user@domain.com) with:
  - Exactly one '@' symbol
  - Ends with '.com'
  - Only allowed characters (letters, digits, @, ., _, -)
  - No uppercase letters
  - Must be unique

## File Structure
```
address-book/
├── Addressbook.csv        # Data file storing contacts
├── contact.c             # Core contact management functions
├── contact.h             # Header file with structures and prototypes
├── file.c                # File I/O operations
├── file.h                # File operation prototypes
├── main.c                # Main program and menu
├── populate.c            # Sample contact data (unused in final version)
└── populate.h            # Header for populate functions
```

## How to Use
1. Compile the program:
   ```bash
   gcc main.c contact.c file.c -o addressbook
   ```
2. Run the executable:
   ```bash
   ./addressbook
   ```
3. Use the menu to manage your contacts:
   ```
   1. Create contact
   2. Search contact
   3. Edit contact
   4. Delete contact
   5. List all contacts
   6. Exit
   ```

## Data File Format
Contacts are stored in `Addressbook.csv` with the following format:
```
Name, Phone, Email
John Doe, 1234567890, john@example.com
Alice Smith, 0987654321, alice@example.com
```

## Notes
- The program handles up to 100 contacts (configurable in `contact.h`)
- All data is case-sensitive except for email searches
- The program automatically loads existing contacts on startup and saves on exit

## Author
Sakshi Patil

