#include "ReportEntry.h"

void ReportEntry::setGrade()
{
    if (_score >= 80)
        _grade = 'A';
    else if (_score >= 70)
        _grade = 'B';
    else if (_score >= 60)
        _grade = 'C';
    else if (_score >= 50)
        _grade = 'D';
    else if (_score >= 40)
        _grade = 'E';
    else
        _grade = 'F';
}

ReportEntry::ReportEntry(const ReportEntry &r) : _score{r._score}, _grade{r._grade}
{
    this->setName(r.getName());
}

ReportEntry::ReportEntry(std::string name, double score)
{
    this->setName(name);
    this->setScore(score);
    this->setGrade();
}

bool ReportEntry::setName(std::string name)
{
    int length = name.length();
    if (length == 0)
    {
        std::cout << "Subject name cannot be empty!\n\n";
        return false;
    }
    else if (length > MAX_NAME_LENGTH)
    {
        std::cout << "Subject name must not exceed 20 chars!\n\n";
        return false;
    }
    else
    {
        strcpy(_name, name.c_str());
        return true;
    }
}

bool ReportEntry::setScore(double score)
{
    if (score >= 0 && score <= 100)
    {
        _score = score;
        setGrade();
        return true;
    }
    else
    {
        std::cout << "Invalid score!\n\n";
        return false;
    }
}

std::string ReportEntry::getName() const { return _name; }

double ReportEntry::getScore() const { return _score; }
    
char ReportEntry::getGrade() const { return _grade; }

void ReportEntry::printEntry() const
{
    std::cout << "\nName  : " << _name;
    std::cout << "\nScore : " << _score;
    std::cout << "\nGrade : " << _grade;
    std::cout << std::endl;
}

std::string ReportEntry::getDetails() const
{
    std::string value;
    value = "\nName  : " + getName()
            + "\nScore : " + std::to_string(getScore())
            + "\nGrade : " + std::to_string(getGrade())
            + "\n";
    return value;
}
