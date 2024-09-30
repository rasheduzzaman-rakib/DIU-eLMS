#include "User.h"
#include "Faculty.h"
#include "Student.h"

#include <bits/stdc++.h>
using namespace std;

class ManagementSystem
{
public:
    void displayMainMenu()
    {
        int choice;
        do
        {
            cout << endl;
            cout << "__________________________________________________\n";
            cout << endl;
            cout << "         [ DHAKA INTERNATIONAL UNIVERSITY]        \n";
            cout << "         [DIU eLearning Management System]        \n";
            cout << "                    [Main Menu]             \n";
            cout << "             [Visit- www.lms.diu.ac.bd]                \n";
            cout << "            [Email- hello@lms.diu.ac.bd]                \n";
            cout << "__________________________________________________\n";
            cout << endl;
            cout << "Option 1. Registration\n";
            cout << "Option 2. Login\n";
            cout << "Option 3. Exit\n";
            cout << "--------------------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();
            cout << "--------------------------------------------------\n";
            switch (choice)
            {
            case 1:
                displayRegistrationMenu();
                break;
            case 2:
                displayLoginMenu();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "___________________________\n\n";
                cout << "Invalid choice! Try again." << endl;
                cout << "___________________________\n\n\n";
            }
        } while (choice != 3);
    }

    void displayRegistrationMenu()
    {
        int choice;
        do
        {
            cout << endl;
            cout << "--------------------------------------------------\n";
            cout << "        [Registration Menu]         \n";
            cout << "--------------------------------------------------\n";
            cout << "Option 1. Faculty Registration\n";
            cout << "Option 2. Student Registration\n";
            cout << "option 3. Main Menu" << endl;
            cout << "--------------------------------------------------\n";
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();
            cout << "--------------------------------------------------\n";
            switch (choice)
            {
            case 1:
            {
                Faculty faculty;
                faculty.registerUser();
                break;
            }
            case 2:
            {
                Student student;
                student.registerUser();
                break;
            }
            case 3:
                return;
            default:
                cout << "--------------------------------------------------\n";
                cout << "Invalid choice! Try again." << endl;
                cout << "--------------------------------------------------\n";
            }
        } while (choice != 3);
    }

    void displayLoginMenu()
    {
        int choice;
        do
        {
            cout << endl;
            cout << "__________________________________________________\n\n";
            cout << "             [Login Menu]             \n";
            cout << "--------------------------------------------------\n";
            cout << "Option 1. Login Faculty Account\n";
            cout << "Option 2. Login Student Account\n";
            cout << "Option 3. Main Menu" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
            {
                Faculty faculty;
                faculty.login();
                break;
            }
            case 2:
            {
                Student student;
                student.login();
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice! Try again." << endl;
            }
        } while (choice != 3);
    }
};

int main()
{
    ManagementSystem system;
    system.displayMainMenu();
    return 0;
}
