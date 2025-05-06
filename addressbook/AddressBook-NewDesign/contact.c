//*Description*//
//Name:C.Lavanya
//Date:8/04/2025
//Title:Project on Addressbook
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>
void sortbyname(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)//outer loop for iterations 
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++)//inner loop for comparison
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)//compare names
            {  //do the swapping  if the names are in jumbling order
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];  
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}
void sortbyphone(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++)
        {
            if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)//compares phone
            {
                //do the swapping  if the phone numbers are in jumbling order
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}
void sortbyemail(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++)
        {
            if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)//compares email
            {
                //do the swapping  if the emails are in jumbling order
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    char name[50];
    char phone[20];
    char email[50];
    switch(sortCriteria)
    {
        case 1:
            sortbyname(addressBook);//sort the name
            printf("Name\t      Phone\t      Email\n");
            printf("-------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("%s\t    %s\t    %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("-------------------------------------------------------------\n");
            }
            break;
        case 2://sort by phone
            sortbyphone(addressBook);
            printf("Name\t      Phone\t      Email\n");
            printf("-------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)//print sorted contacts
            {
                printf("%s\t    %s\t    %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("-------------------------------------------------------------\n");
            }
            break;
        case 3://sort by email
            sortbyemail(addressBook);
            printf("Name\t      Phone\t      Email\n");
            printf("-------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)//print sorted contacts
            {
                printf("%s\t    %s\t   %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("-------------------------------------------------------------\n");
            }
            break;
    }
    
}
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int validate_name(char name[]) 
{
    int i = 0;//intialize the i value as 0
    while(name[i] != '\0') //here check the name until '\0'
    {
        if (isalpha(name[i]) || name[i] == ' ') //it will check the name having uppercase ,lowecase and space
        {
            i++;//if condition satisfies after that increment the i value
        } 
        else 
        {
            printf("Invalid name. Please enter a valid name\n");
            return 0;
        }
    }
    return 1;//name should be equal to '\0' it returns 1.
}
int  validate_phone(char phone[])
{
    int i=0;
    int count=0;
    while(phone[i]!='\0')//here check the name until '\0'
    {
        if(isdigit(phone[i]) )//it will check phone number having digits or not
        {
            i++;
            count++;
        }
        else
        {
            
            return 0;
        }
    }
    if(count==10)//it will check whether the 10 elements are present in phone or not
    {
        return 1;
    }
    else{
        printf("Invalid phone. Please enter a valid phone\n");
        return 0;
    }
}
//check the phone is unique or not
int is_unique_phone(AddressBook* addressBook, const char* phone) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone,phone) == 0) 
        {
            printf("phone already exists. Please enter a unique phone.\n");
            return 0; 
        }
    }
    return 1; 
}
int validate_email(char email[]) 
{
    int i = 0;
    int at_count = 0;
    int dot_count=0;
    if (strstr(email, ".com") == NULL) 
    {
        printf("Invalid email. Please enter a valid email\n");
        return 0;
    }
    while (email[i] != '\0') 
    {
        if (email[i] == '@') 
        {
            at_count++;
        } 
        else if (email[i] == '.') 
        {
            dot_count++;
        }
        i++;
    }
    if (at_count == 1 && email[0] != '@') //here checks email having at exactly one @ and doesn't start with @
    {
        return 1;
    } 
    else 
    {
        printf("Invalid email. Please enter a valid email\n");
        return 0;
    }
}
//check mail is unique or not
int is_unique_email(AddressBook* addressBook, const char* email) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) 
        {
            printf("Email already exists. Please enter a unique email.\n");
            return 0; 
        }
    }
    return 1; 
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];
    int result=0;
    do
    {
       printf("enter the name: ");
       scanf(" %[^\n]",name);
       result= validate_name(name); //validate the name
    } while (result==0);
    char phone[20];
    do
    {
       printf("enter the phone: ");
       scanf(" %[^\n]",phone);
       result= validate_phone(phone)&& is_unique_phone(addressBook,phone);
    } while (result==0);
    char email[50];
    do
    {
       printf("enter the email: ");
       scanf(" %[^\n]",email);
       result= validate_email(email)&& is_unique_email(addressBook,email);
    } while (result==0);

    // after completion of validation stored in data base
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    (addressBook->contactCount)++;
    printf("Contact added successfully\n");
}
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for Searchcontact */
    char name[50];
    char phone[20];
    char email[50];
    int option;
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("Enter the option: ");
    scanf("%d", &option);

    int result = 0;
    int found=0;
    switch (option)
    {
        case 1: 
            do {
                printf("Enter the name to search: ");
                scanf(" %[^\n]", name);
                result = validate_name(name);
            } while (result == 0);
            int Indexes[100];// To store indices of the matched contacts
            int count = 0;
            // Find and list all matching contacts
            printf("Matching contacts:\n");
            printf("Index\tName\t\tPhone\t\tEmail\n");
            printf("-------------------------------------------------------------\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, name)) 
                {
                    Indexes[count] = i;
                    printf("%d\t%s\t%s\t%s\n",count+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    count++;
                   
                } 
            }
            if (count == 0)
            {
                printf("No contacts found.\n");
                return;
            }
            break;
        case 2:
            do
            {
                printf("Enter the phone: ");
                scanf(" %[^\n]", phone);
                result = validate_phone(phone);
            } while (result == 0);
            
            printf("Index\tName\t      Phone\t      Email\n");
            printf("-------------------------------------------------------------\n");
            
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone, phone))
                {
                    printf("%d\t%s\t    %s\t    %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    found=1;
                }
            }
            if(found)
            {
                printf("phone found\n");  
            }
            else
            {
                printf("No phone found\n");
            }
            break;
        case 3:
            do
            {
                printf("enter the email: ");
                scanf(" %[^\n]",email);
                result = validate_email(email);
            } while (result==0);
            printf("Index\tName\t      Phone\t      Email\n");
            printf("-------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].email,email))
                {
                    printf("%d\t%s\t    %s\t    %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    found=1;
                }
            }
            if(found)
            {
                printf("Email found\n");
            }
            else
            {
                printf("No email found\n"); 
            }
            break;
        default:
             printf("Invalid choice\n");
             break;
    }
}
void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    char name[50];
    char phone[20];
    char email[50];
    int opt;
    printf("1. Name\n 2. Phone\n 3. Email\n");
    printf("Enter the option: ");
    scanf("%d", &opt);
    int result = 0;
    int found=0;
    switch(opt)
    {
        case 1:
            do
            {
                printf("Enter the name to edit: ");
                scanf(" %[^\n]", name);  // Read  with spaces
                result = validate_name(name);  // Validate the name
            } while (result == 0);  // If the name is invalid, loop again

            int Indexes[100];  // To store indices of the matched contacts
            int count = 0;
            printf("Matching contacts:\n");
            printf("index\t  Name\t    Phone\t    Email\n");
            printf("-------------------------------------------------------------\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, name)) 
                {
                    // Store index of the matched contact
                    Indexes[count] = i;
                    printf("%d. %s\t%s\t%s\n", count + 1, addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    count++;
                }
            }

            // If no contacts are found
            if (count == 0)
            {
                printf("No name found.\n");
            }
            else
            {
                printf("name found\n");
            }
            int index;
            int option;
            printf("choose the index for editing:\n");
            scanf("%d", &index);
            printf("\nWhat do you want to edit?\n");
            printf("1. Name\t 2. Phone\t 3. Email\n");
            printf("enter the option:");
            scanf("%d",&option);
            if (index < 1 || index > count) 
            {
                printf("Invalid index.\n");
                return;
            }
            int actualIndex = Indexes[index- 1];
            if(option==1)
            {
                char newName[50];
                do {
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", newName);  // Read the new name
                    result = validate_name(newName);  // Validate the new name
                } while (result == 0);  // If the new name is invalid, loop continue
                strcpy(addressBook->contacts[actualIndex].name, newName);//store new contact into previous contact
                printf("Name updated successfully.\n");
                return;   
            }
            else if(option==2)
            {
                char newPhone[20];
                do {
                    printf("Enter the new phone: ");
                    scanf(" %[^\n]", newPhone);  
                    result = validate_phone(newPhone) && is_unique_phone(addressBook,newPhone);  
                } while (result == 0);  
                strcpy(addressBook->contacts[actualIndex].phone, newPhone);
                printf("Name updated successfully.\n");
                return;   
                
            }
            else if(option==3)
            {
                char newEmail[50];
                do {
                    printf("Enter the new email: ");
                    scanf(" %[^\n]", newEmail);  
                    result = validate_email(newEmail) && is_unique_email(addressBook,newEmail);  
                } while (result == 0);  
                strcpy(addressBook->contacts[actualIndex].email,newEmail);
                printf("Email updated successfully.\n");
                return;   
            }
            else
            {
                printf("Invalid option\n");
                return;
            }
            break;
    case 2:
            char newPhone[20];
            do
            {
               printf("enter the phone:");
               scanf(" %[^\n]",phone);
               result= validate_phone(phone)&& is_unique_phone(addressBook,newPhone);
            } while (result==0);
            for(int i=0;i<addressBook->contactCount;i++)
            {
               if(strstr(addressBook->contacts[i].phone,phone))
               {
                    printf("index\tName\t    Phone\t    Email\n"); 
                    printf("-------------------------------------------------------------\n");
                    printf("%d\t%s\t    %s\t    %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    found=1;
                    do 
                    {
                        printf("enter the New phone: ");
                        scanf(" %[^\n]", newPhone);
                        result = validate_phone(newPhone);
                    } while (result == 0);
                    strcpy(addressBook->contacts[i].phone,newPhone);
                    printf("Phone updated successfully\n");
                    return;
                }
            }
            if(found)
            {
                printf("phone is found\n");
                return;
            }
            else
            {
                printf("no phone found\n");
                return;
            }
            break;
    case 3:
            char newemail[50];
            do
            {
               printf("enter the email:");
               scanf(" %[^\n]",email);
               result= validate_email(email)&& is_unique_email(addressBook,email);
            } while (result==0);
            for(int i=0;i<addressBook->contactCount;i++)
            {
               if(strstr(addressBook->contacts[i].email,email))
               {
                    printf("index\tName\t      Phone\t      Email\n");
                    printf("-------------------------------------------------------------\n");
                    printf("%d\t%s\t    %s\t    %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    found=1;
                    do 
                    {
                        printf("enter the New email: ");
                        scanf(" %[^\n]", newemail);
                        result = validate_email(newemail);
                    } while (result == 0);
                    strcpy(addressBook->contacts[i].email,newemail);
                    printf("email updated successfully\n");
                    return;
               }
            }
            if(found)
            {
                printf("email is found\n");
                return;
            }
            else
            {
                printf("no email found\n");
                return;
            }
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    char name[50];
    char phone[20];
    char email[50];
    int opt;
    printf("1.name\n 2.phone\n 3.email\n");
    printf("enter the option: ");
    scanf("%d", &opt);
    int i = 0, j = 0;
    char ch;
    switch (opt)
    {
        case 1:
            printf("enter the name: ");
            scanf(" %[^\n]", name);//reads with spaces
            int Indexes[100];//display the  matched contacts after entering the input
            int Count = 0;   //counts how many matched contacts are present

            //display only the matching contacts
            printf("index\t  Name\t    Phone\t    Email\n");
            printf("-------------------------------------------------------------\n");
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, name))
                {
                    Indexes[Count] = i;  //store the actual contact
                    printf("%d\t%s\t    %s\t    %s\n", Count + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    printf("-------------------------------------------------------------\n");
                    Count++;
                }
            }
            if (Count == 0)
            {
                printf("Name Not found\n");
                return;
            }

            int index;
            int option;
            printf("choose the index for deleting:\n");
            scanf("%d", &index);
            printf("\nWhat do you want to delete?\n");
            printf("1. Name\n2. Phone\n3. Email\n");
            printf("enter the option:");
            scanf("%d",&option);
            if (index < 1 || index > Count)
            {
                printf("Invalid index!\n");
                return;
            }
           
            printf("enter your choice(y/n):\n");
            scanf(" %c", &ch);

            if (ch == 'y') // if yes means
            {
                int actualIndex = Indexes[index - 1];
                for (int k = actualIndex; k < addressBook->contactCount - 1; k++)
                {
                    addressBook->contacts[k] = addressBook->contacts[k + 1];
                }
                addressBook->contactCount--;
                printf("contact deleted\n");
                return;
            }
            else if (ch == 'n') // if no means
            {
                printf("exit\n");
                return;
            }
            else
            {
                printf("please enter valid one!!\n");
                return;
            }

            break;

        case 2:
            
                printf("enter the phone:");
                scanf(" %[^\n]",phone);
                for( i=0;i<addressBook->contactCount-1;i++)
                {
                    if(strstr(addressBook->contacts[i].phone,phone))
                    {
                        printf("index\tName\t      Phone\t      Email\n");
                        printf("-------------------------------------------------------------\n");
                        printf("%d\t%s\t    %s\t    %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        printf("-------------------------------------------------------------\n");
                        printf("phone is found\n");
                        printf("enter your choice(y/n):");
                        scanf(" %c",&ch);
                        if(ch=='y')
                        {                     
                            for(int j=i;j<addressBook->contactCount;j++)
                            {
                                addressBook->contacts[j]=addressBook->contacts[j+1];
                        
                            }
                            addressBook->contactCount--;
                            printf("contact deleted");
                            return ;
                        }
                    
                        else if(ch=='n')
                        {
                            printf("exit\n");
                            return;
                        }
                        else
                        {
                            printf("please enter valid one!!");
                            return;
                        }
                    }

                }
                printf("Phone Not found");
                break;
        case 3:
            
                printf("enter the email:");
                scanf(" %[^\n]",email);
                for( i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].email,email))
                    {
                        printf("index\tName\t      Phone\t      Email\n");
                        printf("-------------------------------------------------------------\n");
                        printf("%d\t%s\t    %s\t    %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        printf("-------------------------------------------------------------\n");
                        printf("email is found\n");
                        printf("enter your choice(y/n):");
                        scanf(" %c",&ch);
                        if(ch=='y')
                        {                     
                            for(int j=i;j<addressBook->contactCount-1;j++)
                            {
                                addressBook->contacts[j]=addressBook->contacts[j+1];
                        
                            }
                        
                            printf("contact deleted");
                            addressBook->contactCount--;//Reducing the contacts
                            return ;
                        }
                        else if(ch=='n')
                        {
                        printf("exit\n");
                        return;
                        }
                        else
                        {
                        printf("please enter valid one!!");
                        return;
                        }
                        
                    }
                   
                }
                printf("Email Not found");
                break;
            default:
                printf("Invalid choice\n");
                break;
    }
}
               

