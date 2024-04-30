#include <iostream>
#include "Github.h"
int main() 
{
    Repository repos;
    int choice;
    string name1, name2, original, copy;
    bool is_public;
    while (true) 
    {
        cout << "1.Create repository"<<endl;
        cout << "Enter Choice " ;
        cin >> choice;
        switch (choice) 
        {
        case 1:
            cout << "Enter repository name: ";
            cin >> name1;
            cout << "Enter repository status (1 for public, 0 for private): ";
            cin >> is_public;
            repos.CreateRepository(name1, is_public);
            break;
        }
    }
    return 0;
}
