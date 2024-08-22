#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdexcept>

#include "Person.h"
#include "Student.h"
#include "ReportEntry.h"
#include "Util.h"
#include "Queue.h"

class ReportCardSystem
{
private:
    // Delete copy constructor, assignment, and new operator
    ReportCardSystem(const ReportCardSystem&) = delete;
    ReportCardSystem& operator=(const ReportCardSystem&) = delete;
    void* operator new(size_t size) = delete;

    // File name of data file
    static const std::string _STUDENT_FILE;
    // Vector to store Student objects
    std::vector<Student> vec;
    std::ofstream outFile;
    std::ifstream inFile;

    // Main functions

    void mainMenu();
    void addStud();
    void addSub();
    void editStud();
    void editSub();
    void removeStud();
    void removeSub();
    void searchStud();
    void printStudMul();

    // Internal functions

    int search(int id);
    void sort();
    void write_file(std::string filename);
    void read_file(std::string filename);
    char menu_prompt(char first, char last);
    bool exit_internal();

    // Debugging functions

    void printVec();
    
public:
    ReportCardSystem();
    ~ReportCardSystem();
};
