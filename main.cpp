#include <iostream>
#include "GitHub.h"
int main() 
{
    Repository repo;
    UserRepository user_repo;
    repo.ReadFromCSV(); // Load repositories from CSV
    string username, password;
    cout << "Enter Username : ";
    cin >> username;
    cout << "Enter Passworsd : ";
    cin >> password;
    user_repo.User_Registeration(username, password);
    if (user_repo.Login(username, password))
    {
        repo.display(username);
    }
    return 0;
}
