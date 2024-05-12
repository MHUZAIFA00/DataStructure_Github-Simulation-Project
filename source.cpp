#include "GitHub.h"
#include <fstream>
#include <sstream>
#include <iostream>
User::User(string username, string password)
{
    this->username = username;
    this->password = password;
}
Node::Node(string name, bool is_public) 
{
    this->name = name;
    this->is_public = is_public;
    num_files = 0;
    num_commits = 0;
    num_forks = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}
Repository::Repository()
{
    root = NULL;
    User_directory = " ";
}
void Repository::Register(string username, string password)
{
    User new_user(username, password);
    users[username] = new_user;

    ofstream userFile("Users.csv", ios::app);        //Save new user to User.csv
    if (userFile.is_open())
    {
        userFile << username << "," << password << endl;
        userFile.close();
    }
    else
    {
        cout << "Unable to open user file";
    }

    cout << "User registered successfully!" << endl;
}
bool Repository::Login(string username, string password)
{
    ifstream userFile("Users.csv");        //Match data from already register user
    if (userFile.is_open())
    {
        string line;
        while (getline(userFile, line))
        {
            stringstream ss(line);
            string storedUsername, storedPassword;
            getline(ss, storedUsername, ',');
            getline(ss, storedPassword, ',');

            if (storedUsername == username && storedPassword == password)
            {
                User_directory = username;
                cout << "Login successful!" << endl;
                userFile.close();
                return true;
            }
        }
        userFile.close();
    }
    else
    {
        cout << "Unable to open user file";
    }

    cout << "Invalid username or password!" << endl;
    return false;
}

void Repository::CreateRepository(string name, bool is_public, int num_files, int num_commits, int num_forks)
{
    if (root == NULL)
    {
        root = new Node(name, is_public);
        root->num_files = num_files;
        root->num_commits = num_commits;
        root->num_forks = num_forks;
    }
    else
    {
        Node* current = root;
        while (true)
        {
            if (name < current->name)
            {
                if (current->left == NULL)
                {
                    current->left = new Node(name, is_public);
                    current->left->parent = current;
                    current->left->num_files = num_files;
                    current->left->num_commits = num_commits;
                    current->left->num_forks = num_forks;
                    break;
                }
                else
                {
                    current = current->left;
                }
            }
            else
            {
                if (current->right == NULL)
                {
                    current->right = new Node(name, is_public);
                    current->right->parent = current;
                    current->right->num_files = num_files;
                    current->right->num_commits = num_commits;
                    current->right->num_forks = num_forks;
                    break;
                }
                else
                {
                    current = current->right;
                }
            }
        }
    }
    if (User_directory == " ")
    {
        User_directory = name;
    }
    ofstream file(User_directory + "/" + name + ".csv");
    file << "This is a new repository for " << name << ".";
    file.close();
}

void Repository::DeleteRepository(string name)
{
    Node* current = root;
    Node* parent = NULL;
    while (current != NULL)
    {
        if (name < current->name)
        {
            parent = current;
            current = current->left;
        }
        else if (name > current->name)
        {
            parent = current;
            current = current->right;
        }
        else
        {
            if (current->left != NULL && current->right != NULL)
            {
                Node* min_right = current->right;
                Node* min_right_parent = current;

                while (min_right->left != NULL)
                {
                    min_right_parent = min_right;
                    min_right = min_right->left;
                }

                current->name = min_right->name;
                current->is_public = min_right->is_public;
                current->num_files = min_right->num_files;
                current->num_commits = min_right->num_commits;
                current->num_forks = min_right->num_forks;
                if (min_right->parent == current)
                {
                    min_right_parent = current;
                }
                current = min_right;
                current = current->right;
                min_right_parent->left = current;
            }
            else
            {
                if (current->left != NULL)
                {
                    Node* child = current->left;
                    if (parent == NULL)
                    {
                        root = child;
                    }
                    else if (parent->left == current)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                }
                else
                {
                    Node* child = current->right;
                    if (parent == NULL)
                    {
                        root = child;
                    }
                    else if (parent->left == current)
                    {
                        parent->left = child;
                    }
                    else {
                        parent->right = child;
                    }
                }
                delete current;
                break;
            }
        }
    }
}
void Repository::ForkRepository(string original_repo_name,string forked_repo_name) 
{
    Node* original_repo = FindRepository(original_repo_name);
    if (original_repo != NULL && original_repo->is_public) 
    {
        Node* forked_repo = new Node(forked_repo_name, true);
        forked_repo->num_files = original_repo->num_files;
        forked_repo->num_commits = original_repo->num_commits;
        forked_repo->num_forks = 0;
        forked_repo->files = original_repo->files;
        if (root == NULL) 
        {
            root = forked_repo;
        }
        else 
        {
            Node* current = root;
            while (true) 
            {
                if (forked_repo_name < current->name) 
                {
                    if (current->left == NULL)
                    {
                        current->left = forked_repo;
                        current->left->parent = current;
                        break;
                    }
                    else 
                    {
                        current = current->left;
                    }
                }
                else 
                {
                    if (current->right == NULL) 
                    {
                        current->right = forked_repo;
                        current->right->parent = current;
                        break;
                    }
                    else {
                        current = current->right;
                    }
                }
            }
        }
    }
    else 
    {
        cout << "Repository Not found!" << endl;
    }
}
Node* Repository::FindRepository(string name)    //search for repository
{
    Node* current = root;
    while (current != NULL)
    {
        if (name < current->name)
        {
            current = current->left;
        }
        else if (name > current->name)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
    return NULL;
}
void Repository::ViewStats(string name)    //Set as public or private ,initialy set as private;
{
    Node* repo = FindRepository(name);
    if (repo != NULL)
    {
        cout << "Repository name: " << repo->name << endl;
        if (repo->is_public)
        {
            cout << "Public : yes"<<endl;
        }
        else
        {
            cout << "Public : No"<<endl;
        }
        
        cout << "Number of files: " << repo->num_files << endl;
        cout << "Number of commits: " << repo->num_commits << endl;
        cout << "Number of forks: " << repo->num_forks << endl;
    }
    else
    {
        cout << "Repository not found" << endl;
    }
}

void Repository::Commit(string name)
{
    Node* repo = FindRepository(name);
    if (repo != NULL)
    {
        repo->num_commits++;
    }
    else
    {
        cout << "Repository not found" << endl;
    }
}

void Repository::Set(string name, bool is_public)       // Update or set Repository status
{
    Node* repo = FindRepository(name);
    if (repo != NULL)
    {
        repo->is_public = is_public;
    }
    else
    {
        cout << "Repository not found." << endl;
    }
}
void Repository::AddFile(string repo_name, string file_name)
{
    Node* repo = FindRepository(repo_name);
    if (repo != NULL) 
    {
        repo->files.push_back(file_name);
        repo->num_files++;
    }
    else {
        cout << "Repository not found." << endl;
    }
}

void Repository::DeleteFile(string repo_name, string file_name)
{
    Node* repo = FindRepository(repo_name);
    if (repo != NULL) {
        auto it = find(repo->files.begin(), repo->files.end(), file_name);
        if (it != repo->files.end()) 
        {
            repo->files.erase(it);
            repo->num_files--;
        }
        else {
            cout << "File not found in repository." << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}
void Repository::display()
{

    string repo_name,fork_repo_name,file_name,username,password;
    bool is_public;
    int choice;
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
        cout << "9.exit" << endl;
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
            CreateRepository(repo_name, is_public, 0, 0, 0); // Assuming initial values 
            break;
        case 2:
            cout << "Enter repository name: ";
            cin >> repo_name;
            DeleteRepository(repo_name);
            break;
        case 3:
            cout << "Enter original repository name: ";
            cin >> repo_name;
            cout << "Enter copied repository name: ";
            cin >> fork_repo_name;
            ForkRepository(repo_name, fork_repo_name);
            break;
        case 4:
            cout << "Enter repository name: ";
            cin >> repo_name;
            ViewStats(repo_name);
            break;
        case 5:
            cout << "Enter repository name: ";
            cin >> repo_name;
            Commit(repo_name);
            break;
        case 6:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter repository public status (1 for public, 0 for private): ";
            cin >> is_public;
            Set(repo_name, is_public);
            break;
        case 7:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter file name: ";
            cin >> file_name;
            AddFile(repo_name, file_name);
            break;
        case 8:
            cout << "Enter repository name: ";
            cin >> repo_name;
            cout << "Enter file name: ";
            cin >> file_name;
            DeleteFile(repo_name, file_name);
            break;
        case 9:
            WriteToCSV(); // Save repositories to CSV before exiting
            exit(0);
        default:
            cout << "Invalid choice" << endl;
        }
    }
}
void Repository::WriteToCSV()
{
    ofstream file("Data.csv");
    if (file.is_open())
    {
        WriteToCSVHelper(root, file);
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    ofstream userFile("Users.csv");
    if (userFile.is_open())
    {
        for (auto& user : users)
        {
            userFile << user.first << "," << user.second.password << endl;
        }
        userFile.close();
    }
    else
    {
        cout << "Unable to open user file";
    }
}

void Repository::WriteToCSVHelper(Node* node, ofstream& file) 
{
    if (node)
    {
        file << node->name << "," << node->is_public << "," << node->num_files << ","
            << node->num_commits << "," << node->num_forks << endl;
        WriteToCSVHelper(node->left, file);
        WriteToCSVHelper(node->right, file);
    }
}
void Repository::ReadFromCSV()
{
    ifstream file("Data.csv");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, is_public, num_files, num_commits, num_forks;
            getline(ss, name, ',');
            getline(ss, is_public, ',');
            getline(ss, num_files, ',');
            getline(ss, num_commits, ',');
            getline(ss, num_forks, ',');
            CreateRepository(name, stoi(is_public), stoi(num_files), stoi(num_commits), stoi(num_forks));
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}
