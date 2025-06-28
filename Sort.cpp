#include "Sort.h"
#include <algorithm>

//============================================================================
// Perform QuickSort on course list based on selected sorting method
//============================================================================
void SortUtils::quickSort(std::vector<Course>& courses, SortMethod method) {
    if (!courses.empty()) {
        quickSortHelper(courses, 0, courses.size() - 1, method);
    }
}

//============================================================================
// Recursive QuickSort helper
//============================================================================
void SortUtils::quickSortHelper(std::vector<Course>& courses, int low, int high, SortMethod method) {
    if (low < high) {
        int pi = partition(courses, low, high, method);
        quickSortHelper(courses, low, pi - 1, method);
        quickSortHelper(courses, pi + 1, high, method);
    }
}

//============================================================================
// Partition logic for QuickSort
//============================================================================
int SortUtils::partition(std::vector<Course>& courses, int low, int high, SortMethod method) {
    Course pivot = courses[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (compare(courses[j], pivot, method)) {
            std::swap(courses[++i], courses[j]);
        }
    }
    std::swap(courses[i + 1], courses[high]);
    return i + 1;
}

//============================================================================
// Comparison logic based on selected SortMethod
//============================================================================
bool SortUtils::compare(const Course& a, const Course& b, SortMethod method) {
    switch (method) {
    case SortMethod::BY_TITLE:
        return a.title < b.title;
    case SortMethod::BY_TEACHER:
        return a.teacher < b.teacher;
    default:
        return a.courseId < b.courseId;
    }
}
