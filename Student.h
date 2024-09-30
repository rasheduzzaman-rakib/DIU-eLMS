#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <bits/stdc++.h>
using namespace std;

class Student : public User
{
private:
    int roll;
    int studentID;
    string batch;
    string shift;
    string nid;
    string department;
    string bloodGroup;
    string presentAddress;
    vector<string> courses;
    vector<string> enrolledCourses;

    // Utility function to trim whitespace from both ends of a string
    std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos)
            return ""; // no content
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Utility function to write student data to the temporary file
    void writeToTempFile(ofstream &tempFile)
    {
        tempFile << name << "," << username << "," << roll << "," << studentID << "," << batch << ","
                 << shift << "," << contactNumber << "," << nid << "," << department << ","
                 << bloodGroup << "," << presentAddress << "," << password << ",";
        for (const auto &course : courses)
        {
            tempFile << course << ",";
        }
        tempFile << "\n";
    }

    // Utility function to update student information in the file
    void updateStudentFile()
    {
        ifstream file("student.txt");
        ofstream tempFile("temp.txt");
        string line;

        if (!file.is_open() || !tempFile.is_open())
        {
            cerr << "Unable to open file for reading or writing." << endl;
            return;
        }

        while (getline(file, line))
        {
            stringstream ss(line);
            string fileUsername;
            getline(ss, fileUsername, ',');

            if (fileUsername == username)
            {
                writeToTempFile(tempFile);
            }
            else
            {
                tempFile << line << "\n";
            }
        }

        file.close();
        tempFile.close();
        remove("student.txt");
        rename("temp.txt", "student.txt");
        cout << "Profile updated successfully!" << endl;
    }

    // Utility function to validate student ID
    bool validateStudentID(int id)
    {
        return (id >= 100000 && id <= 999999); // Ensure it's a 6-digit number
    }

public:
    void registerUser()
    {
        cout << endl
             << "    [Student Registration Menu]     \n";
        cout << "------------------------------------\n";

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Roll: ";
        cin >> roll;

        cout << "Enter Student ID (6 digits): ";
        cin >> studentID;

        // Validate Student ID
        while (!validateStudentID(studentID))
        {
            cout << "Invalid Student ID. Please enter a 6-digit ID: ";
            cin >> studentID;
        }

        cout << "Enter Batch: ";
        cin >> batch;

        cout << "Enter Shift: ";
        cin.ignore();
        getline(cin, shift);

        cout << "Enter Contact Number: ";
        getline(cin, contactNumber);

        cout << "Enter NID: ";
        getline(cin, nid);

        cout << "Enter Department: ";
        getline(cin, department);

        cout << "Enter Blood Group: ";
        getline(cin, bloodGroup);

        cout << "Enter Present Address: ";
        getline(cin, presentAddress);

        cout << "Enter Password: ";
        getline(cin, password);

        ofstream file("student.txt", ios::app);
        if (!file.is_open())
        {
            cerr << "Unable to open file for writing." << endl;
            return;
        }

        file << name << "," << username << "," << roll << "," << studentID << "," << batch << ","
             << shift << "," << contactNumber << "," << nid << "," << department << ","
             << bloodGroup << "," << presentAddress << "," << password << "\n";
        file.close();
        cout << "Student Registration Successful!" << endl;
    }

    void login()
    {
        string inputUsername, inputPassword;
        cout << endl
             << "       [Student Log in Menu]        \n";
        cout << "------------------------------------\n";
        cout << "Enter Username: ";
        getline(cin, inputUsername);

        cout << "Enter Password: ";
        getline(cin, inputPassword);

        // Trim inputs
        inputUsername = trim(inputUsername);
        inputPassword = trim(inputPassword);

        ifstream file("student.txt");
        if (!file.is_open())
        {
            cerr << "Unable to open file." << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string fileUsername, filePassword;

            // Read fields from the file
            getline(ss, name, ',');
            getline(ss, fileUsername, ',');
            ss >> roll;
            ss.ignore();
            ss >> studentID;
            ss.ignore();
            getline(ss, batch, ',');
            getline(ss, shift, ',');
            getline(ss, contactNumber, ',');
            getline(ss, nid, ',');
            getline(ss, department, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, presentAddress, ',');
            getline(ss, filePassword, ',');

            // Load courses
            courses.clear();
            string course;
            while (getline(ss, course, ','))
            {
                courses.push_back(course);
            }

            // Trim the file username and password
            fileUsername = trim(fileUsername);
            filePassword = trim(filePassword);

            // Check if the username and password match
            if (inputUsername == fileUsername && inputPassword == filePassword)
            {
                username = fileUsername;
                password = filePassword;
                found = true;
                break;
            }
        }
        file.close();

        if (found)
        {
            string email = to_string(studentID) + "@cse.diu.ac.bd";
            cout << endl
                 << "          [Student Data]            \n";
            cout << "------------------------------------\n";
            cout << "Name: " << name << endl;
            cout << "Roll: " << roll << endl;
            cout << "ID: " << studentID << endl;
            cout << "Batch: " << batch << endl;
            cout << "Shift: " << shift << endl;
            cout << "Blood Group: " << bloodGroup << endl;
            cout << "Department: " << department << endl;
            cout << "Address: " << presentAddress << endl;
            cout << "Contact Number: " << contactNumber << endl;
            cout << "Email: " << email << endl;
            cout << "------------------------------------\n";

            // Display additional student options
            displayStudentMenu();
        }
        else
        {
            cout << "Invalid username or password." << endl;
        }
    }

    void updateProfile()
    {
        cout << endl
             << "       [Profile Update Menu]        \n";
        cout << "------------------------------------\n";

        cout << "Enter new Name: ";
        getline(cin, name);

        cout << "Enter new Contact Number: ";
        getline(cin, contactNumber);

        updateStudentFile(); // Update the student information in the file
    }

    void addCourse()
    {
        int courseCount;
        cout << endl
             << "How Many Courses You Want to Add (maximum 5): ";
        cin >> courseCount;

        while (cin.fail() || courseCount < 1 || courseCount > 5)
        {
            cout << "Invalid number of courses. Please choose between 1 and 5: ";
            cin.clear();                                         // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cin >> courseCount;
        }
        cin.ignore(); // Ignore the newline character after reading the number

        for (int i = 0; i < courseCount; i++)
        {
            string courseCode;
            cout << "Enter Course Code: ";
            getline(cin, courseCode);
            courses.push_back(courseCode);
            cout << "Course " << courseCode << " added!" << endl;
        }

        // Update the student courses in the file
        updateStudentFile();
    }

    void viewAllCourses()
    {
        if (courses.empty())
        {
            cout << "No courses added yet." << endl;
        }
        else
        {
            cout << "Enrolled Courses:" << endl;
            for (const auto &course : courses)
            {
                cout << course << endl;
            }
        }
    }

    void viewMeetings()
    {
        ifstream file("student_meetings.txt");
        string line;

        if (file.is_open())
        {
            cout << endl;
            cout << "Scheduled Meetings for " << name << ":\n";
            while (getline(file, line))
            {
                stringstream ss(line);
                string date, time, agenda;
                getline(ss, date, ',');
                getline(ss, time, ',');
                getline(ss, agenda, ',');

                cout << "Date: " << date << ", Time: " << time << ", Agenda: " << agenda << endl;
                cout << "--------------------------" << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open student meetings file." << endl;
        }
    }

    void addMeetingToProfile(const string &date, const string &time, const string &agenda)
    {
        ofstream file("student_meetings.txt", ios::app);
        if (file.is_open())
        {
            file << date << "," << time << "," << agenda << "\n"; // Store meeting details
            file.close();
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    // Display
    void displayStudentMenu()
    {
        int choice;
        do
        {
            cout << endl
                 << "       [Student Menu]        \n";
            cout << "------------------------------------\n";
            cout << "Option 1. Profile Update\n";
            cout << "Option 2. Add Course\n";
            cout << "Option 3. View All Courses \n";
            cout << "Option 4. View Meetings\n";
            cout << "Option 5. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore(); // Ignore the newline character

            switch (choice)
            {
            case 1:
                updateProfile();
                break;
            case 2:
                addCourse();
                break;
            case 3:
                viewAllCourses();
                break;
            case 4:
                viewMeetings(); // Call to view meetings
                break;
            case 5:
                cout << "Exiting to main menu..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        } while (choice != 5);
    }
};

#endif // STUDENT_H
