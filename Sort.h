#ifndef SORTUTILS_H
#define SORTUTILS_H

#include "Course.h"
#include <vector>

//============================================================================
// SortMethod - used to select sorting criteria for course list
//============================================================================
enum class SortMethod {
    BY_ID,
    BY_TITLE,
    BY_TEACHER
};

//============================================================================
// SortUtils - provides custom QuickSort functionality for Course objects
//============================================================================
class SortUtils {
public:
    static void quickSort(std::vector<Course>& courses, SortMethod method); 
private:
    static void quickSortHelper(std::vector<Course>& courses, int low, int high, SortMethod method); 
    static int partition(std::vector<Course>& courses, int low, int high, SortMethod method);         
    static bool compare(const Course& a, const Course& b, SortMethod method);                         
};

#endif
