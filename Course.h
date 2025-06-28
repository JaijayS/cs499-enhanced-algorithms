#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

//============================================================================
// Course - holds course ID, title, and a list of prerequisites
//============================================================================
struct Course {
    std::string courseId;
    std::string title;
    std::vector<std::string> prerequisites;
    std::string teacher; 
};

#endif 