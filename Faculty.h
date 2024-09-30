#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include "Student.h"
#include "Meeting.h"
#include <bits/stdc++.h>
using namespace std;

class Faculty : public User
{
private:
    string designation;
    string bachelorDegreeInstitute;

public:
    void registerUser() override
    {
        cout << "     [Faculty Registration Menu]    \n";
        cout << "------------------------------------\n";
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Username: ";
        getline(cin, username);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Contact Number: ";
        getline(cin, contactNumber);
        cout << "Enter Bachelor Degree Institute: ";
        getline(cin, bachelorDegreeInstitute);
        cout << "Enter Password: ";
        getline(cin, password);

        ofstream file("faculty.txt", ios::app);
        if (file.is_open())
        {
            file << name << "," << username << "," << designation << "," << contactNumber << "," << bachelorDegreeInstitute << "," << password << "\n";
            file.close();
            cout << "Faculty Registration Successful!" << endl;
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void login() override
    {
        string inputUsername, inputPassword;
        cout << endl;
        cout << "        [Faculty Login Menu]        \n";
        cout << "------------------------------------\n";
        cout << "Enter Username: ";
        getline(cin, inputUsername);
        cout << "Enter Password: ";
        getline(cin, inputPassword);
        cout << endl;

        ifstream file("faculty.txt");
        if (file.is_open())
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {
                stringstream ss(line);
                string fileUsername, filePassword;

                // Read fields from the file
                getline(ss, name, ',');
                getline(ss, fileUsername, ',');
                getline(ss, designation, ',');
                getline(ss, contactNumber, ',');
                getline(ss, bachelorDegreeInstitute, ',');
                getline(ss, filePassword, ',');

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
                string email = username + "@cse.diu.ac.bd";
                cout << endl;
                cout << "Name: " << name << endl;
                cout << "Designation: " << designation << endl;
                cout << "Contact Number: " << contactNumber << endl;
                cout << "Email: " << email << endl;
                displayFacultyMenu();
            }
            else
            {
                cout << "Invalid username or password." << endl;
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void updateProfile()
    {
        cout << "Enter new Contact Number: ";
        getline(cin, contactNumber);

        ifstream file("faculty.txt");
        ofstream tempFile("temp.txt");
        string line;

        if (file.is_open() && tempFile.is_open())
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                string fileUsername;
                getline(ss, fileUsername, ',');

                if (fileUsername == username)
                {
                    tempFile << name << "," << username << "," << designation << "," << contactNumber << "," << bachelorDegreeInstitute << "," << password << "\n";
                }
                else
                {
                    tempFile << line << "\n";
                }
            }
            file.close();
            tempFile.close();
            remove("faculty.txt");
            rename("temp.txt", "faculty.txt");
            cout << "Contact Number updated successfully!" << endl;
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void listAllStudents()
    {
        ifstream file("student.txt");
        string line;

        if (file.is_open())
        {
            cout << "List of all students:" << endl;
            while (getline(file, line))
            {
                stringstream ss(line);
                string studentName;
                getline(ss, studentName, ',');
                cout << studentName << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void viewEnrolledStudentsInCourse()
    {
        string courseCode;
        cout << "Enter Course Code to view enrolled students: ";
        getline(cin, courseCode);

        ifstream file("student.txt");
        string line;
        bool found = false;

        cout << "Students enrolled in course " << courseCode << ":" << endl;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                string studentName, studentUsername, studentCourse;
                int roll, studentID;

                getline(ss, studentName, ',');
                getline(ss, studentUsername, ',');
                ss >> roll;
                ss.ignore();
                ss >> studentID;
                ss.ignore();

                // Load courses for each student
                vector<string> courses;
                string course;
                while (getline(ss, course, ','))
                {
                    if (!course.empty())
                        courses.push_back(course);
                }

                // Check if the student is enrolled in the specified course
                if (find(courses.begin(), courses.end(), courseCode) != courses.end())
                {
                    found = true;
                    cout << "ID: " << studentID << ", Name: " << studentName << endl;
                }
            }
            file.close();

            if (!found)
            {
                cout << "No students are enrolled in this course." << endl;
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void scheduleMeeting()
    {
        cout << "Enter meeting date (YYYY-MM-DD): ";
        string date;
        getline(cin, date);

        cout << "Enter meeting time (HH:MM): ";
        string time;
        getline(cin, time);

        cout << "Enter agenda for the meeting: ";
        string agenda;
        getline(cin, agenda);

        cout << "Enter usernames of participants (separated by spaces): ";
        string participantsInput;
        getline(cin, participantsInput);
        stringstream ss(participantsInput);
        vector<string> participants;
        string participant;

        while (ss >> participant)
        {
            participants.push_back(participant);
        }

        // Create a new Meeting object
        Meeting newMeeting(date, time, participants, agenda);

        // Save to meetings.txt
        ofstream file("meetings.txt", ios::app);
        if (file.is_open())
        {
            file << newMeeting.date << "," << newMeeting.time << "," << agenda;
            for (const auto &p : participants)
            {
                file << "," << p;
            }
            file << "\n"; // New line for next meeting
            file.close();
            cout << "Meeting scheduled successfully!" << endl;

            // Add meeting details to each student's profile
            for (const auto &studentUsername : participants)
            {
                Student student;                                 // Create a Student object
                student.addMeetingToProfile(date, time, agenda); // Add meeting details to the student's profile
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void viewScheduledMeetings()
    {
        ifstream file("meetings.txt");
        string line;

        if (file.is_open())
        {
            cout << "Scheduled Meetings:" << endl;
            while (getline(file, line))
            {
                stringstream ss(line);
                string date, time, agenda;
                getline(ss, date, ',');
                getline(ss, time, ',');
                getline(ss, agenda, ',');

                vector<string> participants;
                string participant;
                while (getline(ss, participant, ','))
                {
                    participants.push_back(participant);
                }

                Meeting meeting(date, time, participants, agenda);
                meeting.displayMeetingDetails();
                cout << "--------------------------" << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open meetings file." << endl;
        }
    }



    //Display
    void displayFacultyMenu()
    {
        int choice;
        do
        {
            cout << endl;
            cout << "       [Faculty Profile Menu]        \n";
            cout << "------------------------------------\n";
            cout << "1. Update Profile\n";
            cout << "2. List all students\n";
            cout << "3. View Enrolled Students in Course\n";
            cout << "4. Schedule Meeting\n";
            cout << "5. View Scheduled Meetings\n";
            cout << "6. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                updateProfile();
                break;
            case 2:
                listAllStudents();
                break;
            case 3:
                viewEnrolledStudentsInCourse();
                break;
            case 4:
                scheduleMeeting();
                break;
            case 5:
                viewScheduledMeetings();
                break;
            case 6:
                cout << "Returning to the Faculty Information menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
            }
        } while (choice != 6);
    }
};

#endif // FACULTY_H
