#include "Util.h"

static int quicksort_partition(std::vector<Student> &vec, int low, int high)
{
    std::vector<Student> &arr = vec;
    int i = (low - 1); int j = low;
    int pivot = arr[high].getID();
    for (int j = low; j < high; ++j)
    {
        if (arr[j].getID() < pivot)
            std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void Util::quicksort(std::vector<Student> &vec, int low, int high)
{
    if (low < high)
    {
        int pivot = quicksort_partition(vec, low, high);
        quicksort(vec, low, pivot - 1);
        quicksort(vec, pivot + 1, high);
    }
}

// Searches for student in the array, returns index of student in array
int Util::binarysearch(const std::vector<Student> &vec, int low, int high, int query)
{
    if (low > high) return -1;
    else
    {
        int midpoint = (low + high) / 2;
        if (query == vec[midpoint].getID())
            return midpoint;
        else if (query < vec[midpoint].getID())
            return binarysearch(vec, low, midpoint - 1, query);
        else
            return binarysearch(vec, midpoint + 1, high, query);
    }
}

void Util::pause()
{
    std::string temp;
    std::cout << "Press Enter to continue . . .";
    std::getline(std::cin, temp);
}

void Util::clear()
{
    for (int i = 0; i < 50; ++i)
        std::cout << "\n";
}
