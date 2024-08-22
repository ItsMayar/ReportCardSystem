#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include "Person.h"
#include "ReportEntry.h"

class Student : public Person
{
private:
    int _currEntry = 0;                 // Keeps track of how many items in the array
    int static const MAX_ENTRIES = 6;
    ReportEntry _entries[MAX_ENTRIES];  // Array that holds the subject details

    // Sets the ReportEntry array of the Student
    void setEntries(const ReportEntry entries[]);

    // Checks if a ReportEntry with the same name exists
    bool hasReportEntry(const ReportEntry &rInput);

public:
    // Default empty constructor
    Student() {}

    // Copy constructor
    Student (const Student &s);

    // Constructor with parameters
    Student (int id, std::string fname, std::string lname, std::string fac);

    // Adds a ReportEntry to the array
    bool addReportEntry(std::string name, double score);

    // Adds a ReportEntry to the array
    bool addReportEntry(const ReportEntry r);

    // Edit a ReportEntry in the array
    bool editReportEntry(int id, std::string name, double score);

    // Edit a ReportEntry in the array
    bool editReportEntry(int id, const ReportEntry r);

    // Deletes a ReportEntry from the array
    bool deleteReportEntry(int id);

    // Gets a ReportEntry from the array
    bool getReportEntry(int id, ReportEntry &r) const;

    // Gets the number of subjects the Student is taking
    int getSubjectCount() const;

    // Gets the MAX_ENTRIES of Student
    int getMaxEntries() const;

    // Prints to console the details of a ReportEntry (1-indexed)
    void printEntry(int id) const;

    // Prints to console a formatted output of the Student's details and subjects
    void printInfo() const;

    // Prints to console a formatted output of the Student's details
    void printDetails() const;

    // Returns a formatted output of the Student's details
    std::string getDetails() const;
};
