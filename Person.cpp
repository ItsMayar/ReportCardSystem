#include "Person.h"

Person::Person(int id, std::string fname, std::string lname, std::string fac)
{
    setID(id);
    setFirstName(fname);
    setLastName(lname);
    setFaculty(fac);
}

bool Person::setID(int id)
{
    if (id < 1000000000 || id > 1999999999 )
    {
        std::cout << "Invalid ID! (Range: 1000000000 - 1999999999)\n\n";
        return false;
    }
    else
    {
        _id = id;
        return true;
    }
}

bool Person::setFirstName(std::string fname)
{
    int length = fname.length();
    if (fname.empty())
    {
        std::cout << "First name cannot be empty!\n";
        return false;
    }
    else if (length > MAX_NAME_LENGTH)
    {
        std::cout << "First name must not exceed 50 chars!\n";
        return false;
    }
    else
    {
        strcpy(_firstName, fname.c_str());
        return true;
    }
}

bool Person::setLastName(std::string lname)
{
    int length = lname.length();
    if (lname.empty())
    {
        std::cout << "Last name cannot be empty!\n";
        return false;
    }
    else if (length > MAX_NAME_LENGTH)
    {
        std::cout << "Last name must not exceed 50 chars!\n";
        return false;
    }
    else
    {
        strcpy(_lastName, lname.c_str());
        return true;
    }
}

bool Person::setFaculty(std::string fac)
{
    int length = fac.length();
    if (fac.empty())
    {
        std::cout << "Faculty name cannot be empty!\n";
        return false;
    }
    else if (length > MAX_FAC_LENGTH)
    {
        std::cout << "Faculty name must not exceed 4 chars!\n";
        return false;
    }
    else
    {
        strcpy(_faculty, fac.c_str());
        return true;
    }
}

int Person::getID() const { return _id; }

std::string Person::getFirstName() const
{
    return _firstName;
}

std::string Person::getLastName() const
{
    return _lastName;
}

std::string Person::getFaculty() const
{
    return _faculty;
}
