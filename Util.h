#pragma once
#include <vector>

#include "Student.h"
class Util
{
public:
    static void quicksort(std::vector<Student> &vec, int low, int high);
    static int binarysearch(const std::vector<Student> &vec, int low, int high, int query);
    static void pause();
    static void clear();
};
