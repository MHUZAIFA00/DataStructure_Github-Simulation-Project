#include <iostream>
#include "GitHub.h"
#include<string>
int main() 
{
    Repository repo;
    repo.ReadFromCSV(); // Load repositories from CSV
    int choice;
    string username, password;
    while (true) 
    {
        cout << "1.Register" << endl;
        cout << "2.Login" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            repo.Register(username, password);
            break;
        case 2:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (repo.Login(username, password)) 
            {
                repo.display();
            }
            else 
            {
                cout << "Invalid username or password!" << endl;
            }
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
