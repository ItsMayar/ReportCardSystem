#pragma once
#include <iostream>
#include <string>
#include <cstring>

class Person
{
private:
    int static const MAX_NAME_LENGTH = 50;  // Maximum length of first and last name
    int static const MAX_FAC_LENGTH = 4;    // Maximum length of faculty name

// protected:
    int _id;                                // ID of Person
    char _lastName[MAX_NAME_LENGTH + 1];    // Last name of Person
    char _firstName[MAX_NAME_LENGTH + 1];   // First name of Person
    char _faculty[MAX_FAC_LENGTH + 1];      // Faculty of Person
                                            // MAX_LENGTH + 1 because of null terminated string

public:

    // Default empty constructor
    Person() {}
    
    // Constructor with parameters
    Person(int id, std::string fname, std::string lname, std::string fac);

    // Sets ID of Person
    bool setID(int id);

    // Sets first name of Person
    bool setFirstName(std::string fname);

    // Sets last name of Person
    bool setLastName(std::string lname);

    // Sets faculty of Person
    bool setFaculty(std::string fac);

    // Gets ID of Person
    int getID() const;

    // Gets first name of Person
    std::string getFirstName() const;

    // Gets last name of Person
    std::string getLastName() const;

    // Gets faculty of Person
    std::string getFaculty() const;
};
