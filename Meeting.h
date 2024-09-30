#ifndef MEETING_H
#define MEETING_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Meeting
{
public:
    string date;
    string time;
    vector<string> participants; // usernames of students
    string agenda;

    Meeting(string date, string time, vector<string> participants, string agenda)
        : date(date), time(time), participants(participants), agenda(agenda) {}

    void displayMeetingDetails() const
    {
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Participants: ";
        for (const auto &participant : participants)
        {
            cout << participant << " ";
        }
        cout << endl;
        cout << "Agenda: " << agenda << endl;
    }
};

#endif // MEETING_H
