#include "GitHub.h"
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
void Repository::ViewStats(string name)    //Set as public or private
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

void Repository::Set(string name, bool is_public)
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
