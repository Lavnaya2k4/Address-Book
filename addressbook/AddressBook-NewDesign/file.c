#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;//declare the file ponter
    fp=fopen("contacts.csv","w");//open the file contact.csv in write mode
    if(fp==NULL)//check if the file couldnot be opened
    {
        printf("contacts.csv is not found\n");//if the file is not opened it prints this error msg
        return;//exit the function if the file is not available
    }
    for(int i=0;i<addressBook->contactCount;i++)//loop through for each contact in addressbook
    {
        //write contacts name,phone,email in csv format
       fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);//close the file after writing all contacts
}
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;//declare the file ponter
    fp=fopen("contacts.csv","r");//open the file contact.csv in read mode
    if(fp==NULL)//check if the file couldnot be opened
    {
        printf("contacts.csv is not found\n");//if the file is not opened it prints this error msg
        return;//exit the function if the file is not available
    }
    int i;// here i declared as variable
    for (i = 0; ;i++)//loop through for each contact in addressbook
    {
        //read contacts name,phone,email in csv format
        if (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email) != 3)//Check if fscanf successfully reads all three fields (name, phone, email)
        {
            break; // stop if fscanf fails 
        }
    }
    addressBook->contactCount = i;//here 'i'-->number of successfully read contacts
    fclose(fp);//close the file after reading all contacts 
}
