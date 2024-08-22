#pragma once
#include <iostream>
#include <string>
#include <cstring>

class ReportEntry
{
private:
    int static const MAX_NAME_LENGTH = 50;  // Maximum length of name

    char _name[MAX_NAME_LENGTH + 1];    // Name of ReportEntry
                                        // MAX_LENGTH + 1 because of null terminated string
    double _score;                      // Score of ReportEntry
    char _grade;                        // Grade of ReportEntry (auto-generated)

    // Sets grade of ReportEntry based on score
    void setGrade();

public:
    // Default empty constructor
    ReportEntry() {}

    // Copy constructor
    ReportEntry(const ReportEntry &r);

    // Constructor with parameters
    ReportEntry(std::string name, double score);

    // Sets name of ReportEntry
    bool setName(std::string name);

    // Sets score of ReportEntry
    bool setScore(double score);

    // Gets name of ReportEntry
    std::string getName() const;

    // Gets score of ReportEntry
    double getScore() const;

    // Gets grade of ReportEntry
    char getGrade() const;

    // Prints to console a formatted output of the ReportEntry's details
    void printEntry() const;

    // Returns a formatted output of the ReportEntry's details
    std::string getDetails() const;
};
