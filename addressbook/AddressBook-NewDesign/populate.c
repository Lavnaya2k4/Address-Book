#include "contact.h"
// Dummy contact data
static Contact dummyContacts[] = {
    {"Lavanya", "9701481596", "lavanya@example.com"},
    {"Ramesh", "9652963581", "lava@gmail.com"},
    {"Vanaja", "9703496155", "vanaja@company.com"},
    {"Lakshmi", "1234567890", "lakshmi@company.com"},
    {"Pushpa", "8143095290", "pushpa@example.com"},
    {"Haritha", "9515068129", "haritha@example.com"},
    {"Radhika", "7416695275", "radhika@example.com"},
    {"Sreenu", "2223334444", "sreenu@example.com"},
    {"Upendra", "9502886153", "upendra@example.com"},
    {"Uday", "8856789123", "uday@example.com"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i) {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }
}