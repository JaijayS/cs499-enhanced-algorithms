#include "HashMap.h"
#include "Sort.h"
#include <algorithm>

//============================================================================
// Constructor - initializes table with given size
//============================================================================
HashMap::HashMap(unsigned int size) : tableSize(size), table(size) {}

//============================================================================
// Hash function for string keys
//============================================================================
unsigned int HashMap::hash(const std::string& key) const {
    return std::hash<std::string>{}(key) % tableSize;
}

//============================================================================
// Insert a course into the hashmap
//============================================================================
void HashMap::insert(const Course& course) {
    unsigned int index = hash(course.courseId);
    for (auto& c : table[index]) {
        if (c.courseId == course.courseId) {
            c = course;
            return;
        }
    }
    table[index].push_back(course);
}

//============================================================================
// Search for a course by ID
//============================================================================
Course HashMap::search(const std::string& courseId) const {
    unsigned int index = hash(courseId);
    for (const auto& c : table[index]) {
        if (c.courseId == courseId) return c;
    }
    return Course();
}

//============================================================================
// Retrieve all courses and sort them based on user selection
//============================================================================
std::vector<Course> HashMap::getAllCoursesSorted(SortMethod method) const {
    std::vector<Course> allCourses;
    for (const auto& bucket : table) {
        for (const auto& course : bucket) {
            allCourses.push_back(course);
        }
    }

    SortUtils::quickSort(allCourses, method);
    return allCourses;
}
