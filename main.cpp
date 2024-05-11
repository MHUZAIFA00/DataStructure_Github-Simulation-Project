#include <iostream>
#include "GitHub.h"
int main() 
{
    Repository repo;
    repo.ReadFromCSV(); // Load repositories from CSV
    string username, password;
    repo.display();
    return 0;
}
