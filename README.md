# Address Book Project Documentation

**Name:** Sakshi Patil
**Date of Submission:** 10/July/2025  

## Description
This Address Book project is a C program that allows users to manage their contacts efficiently. It provides functionality to create, search, edit, delete, and list contacts. The program features robust input validation and persists data by saving contacts to a CSV file.

Key features:
- Contact management with name, phone, and email fields
- Comprehensive input validation for all fields
- Case-insensitive search functionality
- Data persistence through file I/O operations
- User-friendly menu interface

## File Structure
```
contact.h       - Header file with data structures and function declarations
contact.c       - Implementation of contact management functions
file.h          - Header for file operations
file.c          - Implementation of file I/O functions
main.c          - Main program with menu interface
populate.h      - Header for dummy data population
populate.c      - Dummy contact data for testing
contacts.csv    - Data file storing contacts in CSV format
```

Project Architecture: 
<img width="975" height="361" alt="image" src="https://github.com/user-attachments/assets/7560d57c-76d7-4fa5-982f-e93fd26e1a03" />


## Sample Input/Output

### Sample Input 1: Creating a Contact
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 1

Enter name: Jane Smith
Enter phone number (10 digits): 9876543210
Enter email: jane.smith@gmail.com
Contact added successfully!
```

### Sample Output 1: Listing Contacts
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 5

No.  Name                 Phone          Email                         
-----------------------------------------------------------
1    Sakshi Patil         7775949268     sakshipatilcom2@gmail.com          
2    Shruti Gaddi         9988559555     shruti@344micro.com            
3    Anjali Patil         8988498843     anju27@73example.com            
4    Pooja Patil          7984383473     poojapatil@yutube.com            
5    Amruta Patil         9999329998     amruta1444@gmail.com         
6    Rehan Mokashi        9988777774     rehanmokashi@32microsoft.com                    
7    Sanju Shinde         9878545541     sanju@mail.com                 
8    Kishori Patil        8877874943     kishori@gmail.com             
9    Sourabh Patil        9877478877     sonya14@micro.com         
10   Vina Sutar           8769837221     vina267@33gmail.com                 
11   Yash Koli            7868935444     1234@example.com                   
12   Sakshi Patil         9874746702     sakshi099@micro.com               
13   Jane Smith           9876543210     jane.smith@gmail.com         
-----------------------------------------------------------
Total contacts: 13
```

### Sample Input 2: Searching Contacts
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 2

Search by:
1. Name
2. Phone
3. Email
4. Back to Menu
Enter your choice (1-4): 1
Enter search term: shahid

Search results for "shahid":
-----------------------------------------------------------
Name                 Phone          Email                         
-----------------------------------------------------------
Sakshi Patil         7775949268     sakshipatilcom2@gmail.com            
Sakshi Patil         9874746702     sakshi099@micro.com          
-----------------------------------------------------------
Found 2 matches.

Search again? (y/n): n
```

### Sample Input 3: Editing a Contact
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 3

Edit by:
1. Name
2. Phone
3. Email
4. Cancel
Enter your choice: 1
Enter search term: Jane Smith

Found 1 matching contact:

Editing contact:
1. Name: Jane Smith
2. Phone: 9876543210
3. Email: jane.smith@gmail.com
4. Cancel
Select field to edit (1-4): 1
Enter new name: Jane Doe

Contact updated successfully!
```

### Sample Input 4: Deleting a Contact
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 4

Delete by:
1. Name
2. Phone
3. Email
4. Cancel
Enter your choice: 2
Enter search term: 8877874943

Found 1 matching contact:

Contact to be deleted:
Name: Kishori Patil  
Phone: 8877874943
Email: kishori@gmail.com   

Are you sure? (y/n): y

Contact deleted successfully!
```

### Sample Input 5: Exiting the Program
```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 6
Saving and Exiting...
Contacts saved to contacts.csv successfully!
