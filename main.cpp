//============================================================================
// Author      : Jantzen Springer
// Version     : 1.0
// Description : Course Planner - HashMap Version
//============================================================================

#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//============================================================================
// Function to print a single course
//============================================================================
static void printCourse(const Course& course) {
    std::ostringstream prereqStream;
    if (!course.prerequisites.empty()) {
        for (const auto& pre : course.prerequisites) {
            prereqStream << pre << " ";
        }
    }
    else {
        prereqStream << "None";
    }

    std::cout << std::left
        << std::setw(12) << course.courseId
        << std::setw(35) << course.title
        << std::setw(25) << prereqStream.str()
        << std::setw(20) << course.teacher
        << "\n";
}


//============================================================================
// Utility function: Split for parsing CSV strings
//============================================================================
static std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);
    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

//============================================================================
// Load Courses from file
//============================================================================
static bool loadCourses(const std::string& filename, HashMap& map) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        auto cols = split(line, ',');
        if (cols.size() < 2) continue;

        Course course;
        course.courseId = cols[0];
        course.title = cols[1];

        // Check for prerequisites
        if (cols.size() > 2) {
            auto prereqs = split(cols[2], ' ');
            for (const auto& pre : prereqs) {
                if (!pre.empty()) course.prerequisites.push_back(pre);
            }
        }

        // Check for teacher name
        if (cols.size() > 3) {
            course.teacher = cols[3];
        }

        map.insert(course);
    }
    return true;
}

//============================================================================
// Print the main menu
//============================================================================
static void printMenu() {
    std::cout << "\n+------------------------------------------+\n";
    std::cout << "|          Course Planner Menu             |\n";
    std::cout << "|------------------------------------------|\n";
    std::cout << "| 1. Load Courses from File                |\n";
    std::cout << "| 2. Print All Courses                     |\n";
    std::cout << "| 3. Search for a Course                   |\n";
    std::cout << "| 4. Display Sorted Courses                |\n";
    std::cout << "| 9. Exit                                  |\n";
    std::cout << "+------------------------------------------+\n";
}

//============================================================================
// Main Function
//============================================================================
int main() {
    HashMap courseMap;
    std::string filename = "courses.csv";
    bool dataLoaded = false;

    while (true) {
        printMenu();
        std::cout << "\nEnter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: // Load course file
            dataLoaded = loadCourses(filename, courseMap);
            std::cout << (dataLoaded ? "Courses loaded successfully!\n" : "Failed to load courses.\n");
            break;

        case 2: // Print all courses
            if (!dataLoaded) {
                std::cout << "\nPlease load course data first.\n";
                break;
            }
            std::cout << std::left << std::setw(12) << "Course ID"
                << std::setw(40) << "Title"
                << "Prerequisites | Instructor" << "\n";
            std::cout << std::string(80, '-') << "\n";
            for (const auto& course : courseMap.getAllCoursesSorted()) {
                printCourse(course);
            }
            break;

        case 3: { // Search for one course
            if (!dataLoaded) {
                std::cout << "\nPlease load course data first.\n";
                break;
            }
            std::string searchId;
            std::cout << "\nEnter a Course ID to search: ";
            std::cin >> searchId;
            Course found = courseMap.search(searchId);
            if (!found.courseId.empty()) {
                std::cout << std::left << std::setw(12) << "Course ID"
                    << std::setw(40) << "Title"
                    << "Prerequisites | Instructor" << "\n";
                std::cout << std::string(80, '-') << "\n";
                printCourse(found);
            }
            else {
                std::cout << "Course not found.\n";
            }
            break;
        }

        case 4: { // Sort and display courses
            if (!dataLoaded) {
                std::cout << "\nPlease load course data first.\n";
                break;
            }
            std::cout << "\nChoose sorting method:\n";
            std::cout << "  1. By Course ID\n";
            std::cout << "  2. By Title\n";
            std::cout << "Enter choice: ";
            int sortChoice;
            std::cin >> sortChoice;

            SortMethod method;
            switch (sortChoice) {
            case 2: method = SortMethod::BY_TITLE; break;
            default: method = SortMethod::BY_ID; break;
            }

            auto sortedCourses = courseMap.getAllCoursesSorted(method);
            std::cout << std::left << std::setw(12) << "Course ID"
                << std::setw(40) << "Title"
                << "Prerequisites | Instructor" << "\n";
            std::cout << std::string(80, '-') << "\n";
            for (const auto& course : sortedCourses) {
                printCourse(course);
            }
            break;
        }

        case 9: // Exit
            std::cout << "\nExiting...\n";
            return 0;

        default: // Invalid choice
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
