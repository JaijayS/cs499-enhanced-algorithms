#ifndef HASHMAP_H
#define HASHMAP_H

#include "Course.h"
#include "Sort.h" 

#include <vector>
#include <string>
#include <list>
#include <functional>

//============================================================================
// HashMap - stores and manages Course objects using a hash table
//============================================================================
class HashMap {
private:
    std::vector<std::list<Course>> table;
    unsigned int tableSize;

    unsigned int hash(const std::string& key) const;

public:
    HashMap(unsigned int size = 179);
    void insert(const Course& course);
    Course search(const std::string& courseId) const;
    std::vector<Course> getAllCoursesSorted(SortMethod method = SortMethod::BY_ID) const;
};

#endif 
