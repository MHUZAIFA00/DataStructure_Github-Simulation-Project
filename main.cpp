#include <iostream>
#include "GitHub.h"

int main() {
    Repository repos;
    repos.ReadFromCSV(); // Load repositories from CSV
    int choice;
    string repo_name, file_name, metadata;
    bool is_public;
    while (true) 
    {
        cout << endl;
        cout << "1. Create repository" << endl;
        cout << "2. Delete repository" << endl;
        cout << "3. Fork repository" << endl;
        cout << "4. View stats" << endl;
        cout << "5. Commit" << endl;
        cout << "6. Set visibility" << endl;
        cout << "7. Add file to repository" << endl;
        cout << "8. Delete file from repository" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice) 
        {
        case 1:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter repository status (1 for public, 0 for private): ";
            cin >> is_public;
            repos.CreateRepository(repo_name, is_public, 0, 0, 0); // Assuming initial values 
            break;
        case 2:
            cout << "Enter repository name: ";
            cin >> repo_name;
            repos.DeleteRepository(repo_name);
            break;
        case 3:
            cout << "Enter original repository name: ";
            cin >> repo_name;
            cout << "Enter copied repository name: ";
            cin >> file_name;
            break;
        case 4:
            cout << "Enter repository name: ";
            cin >> repo_name;
            repos.ViewStats(repo_name);
            break;
        case 5:
            cout << "Enter repository name: ";
            cin >> repo_name;
            repos.Commit(repo_name);
            break;
        case 6:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter repository public status (1 for public, 0 for private): ";
            cin >> is_public;
            repos.Set(repo_name, is_public);
            break;
        case 7:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter file name: ";
            cin >> file_name;
            repos.AddFile(repo_name, file_name);
            break;
        case 8:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter file name: ";
            cin >> file_name;
            repos.DeleteFile(repo_name, file_name);
            break;
        case 9:
            repos.WriteToCSV(); // Save repositories to CSV before exiting
            exit(0);
        default:
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
