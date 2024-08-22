#include "Student.h"

Student::Student(const Student &s)
    : Person(s.getID(), s.getFirstName(), s.getLastName(), s.getFaculty()), _currEntry(s._currEntry)
{
    this->setEntries(s._entries);
}

Student::Student(int id, std::string fname, std::string lname, std::string fac)
    : Person(id, fname, lname, fac) {}

bool Student::addReportEntry(std::string name, double score)
{
    ReportEntry r(name, score);
    return addReportEntry(r);
}

bool Student::addReportEntry(const ReportEntry r)
{
    if (hasReportEntry(r))
    {
        std::cout << "Subject already exist!\n";
        return false;
    }
    if (_currEntry < MAX_ENTRIES)
    {
        _entries[_currEntry] = r;
        _currEntry++;
        return true;
    }
    else
    {
        std::cout << "Max entries exceeded!" << std::endl;
        return false;
    }
}

bool Student::editReportEntry(int id, std::string name, double score)
{
    ReportEntry r(name, score);
    return editReportEntry(id, r);
}

bool Student::editReportEntry(int id, const ReportEntry r)
{
    if (_currEntry == 0)
    {
        std::cout << "No entries to edit!\n";
        return false;
    }
    else if (id <= 0 | id >= MAX_ENTRIES | id > _currEntry)
    {
        std::cout << "Please enter a valid ID!\n";
        return false;
    }
    else
    {
        _entries[id - 1] = r;
        return true;
    }
}

bool Student::deleteReportEntry(int id)
{
    if (_currEntry == 0)
    {
        std::cout << "No entries to delete!\n";
        return false;
    }
    else if (id <= 0 | id >= MAX_ENTRIES | id > _currEntry)
    {
        std::cout << "Please enter a valid ID!\n";
        return false;
    }
    else
    {
        for (int i = id; i < _currEntry; i++)
        {
            _entries[i - 1] = _entries[i];
        }
        --_currEntry;
        return true;
    }
}

bool Student::getReportEntry(int id, ReportEntry &r) const
{
    if (_currEntry == 0)
    {
        std::cout << "No entries to get!\n";
        return false;
    }
    else if (id <= 0 | id >= MAX_ENTRIES | id > _currEntry)
    {
        std::cout << "Please enter a valid ID!\n";
        return false;
    }
    else
    {
        r = _entries[id - 1];
        return true;
    }
}

int Student::getSubjectCount() const { return _currEntry; }

int Student::getMaxEntries() const { return MAX_ENTRIES; }

void Student::printEntry(int id) const
{
    if (_currEntry == 0)
        std::cout << "No subjects!\n";
    else if (id <= 0 | id >= MAX_ENTRIES | id > _currEntry)
        std::cout << "Please enter a valid ID!\n";
    else
    {
        std::cout << "\n--- Subject " << id << " ---";
        _entries[id - 1].printEntry();
    }
}

void Student::printInfo() const
{
    std::cout << "\nID             : " << getID();
    std::cout << "\nFirst name     : " << getFirstName();
    std::cout << "\nLast name      : " << getLastName();
    std::cout << "\nFaculty        : " << getFaculty();
    std::cout << "\nSubjects taken : " << getSubjectCount();
    std::cout << "\n";
    if (_currEntry > 0)
    {
        for (int i = 0; i < _currEntry; i++)
            printEntry(i + 1);
    }
    std::cout << std::endl;
}

void Student::printDetails() const
{
    std::cout << "\nID             : " << getID();
    std::cout << "\nFirst name     : " << getFirstName();
    std::cout << "\nLast name      : " << getLastName();
    std::cout << "\nFaculty        : " << getFaculty();
    std::cout << "\nSubjects taken : " << getSubjectCount();
    std::cout << std::endl;
}

std::string Student::getDetails() const
{
    std::string value;
    value = "ID             : " + std::to_string(getID())
            + "\nFirst name     : " + getFirstName()
            + "\nLast name      : " + getLastName()
            + "\nFaculty        : " + getFaculty()
            + "\nSubjects taken : " + std::to_string(getSubjectCount())
            + "\n";

    if (_currEntry > 0)
    {
        for (int i = 0; i < _currEntry; ++i)
        {
            value += "\n--- Subject " + std::to_string(i + 1) + " ---"
                    + _entries[i].getDetails();
        }
    }

    return value;
}

void Student::setEntries(const ReportEntry entries[])
{
    for (int i = 0; i < _currEntry; ++i)
        _entries[i] = entries[i];
}

bool Student::hasReportEntry(const ReportEntry &rInput)
{
    for (int i = 0; i < _currEntry; ++i)
    {
        if (rInput.getName() == _entries[i].getName())
            return true;
    }
    return false;
}
