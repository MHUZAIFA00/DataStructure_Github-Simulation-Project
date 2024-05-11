#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include<vector>
using namespace std;
class Node
{
public:
    string name;
    bool is_public;
    int num_files;
    int num_commits;
    int num_forks;
    vector<string> files; // Store file names
    Node* parent;
    Node* left;
    Node* right;
    Node(string name, bool is_public);
};
class User 
{
public:
    vector<Repository>repositories;
    string username,password;
};
class UserRepository 
{
public:
    vector<User>users;
    void User_Registeration(string username, string password);
    bool Login(string username, string password);
    void Profile_view(string username);
};
class Repository
{
public:
    Node* root;
    string name;
    Repository();
    void CreateRepository(string name, bool is_public, int num_files, int num_commits, int num_forks);     
    void DeleteRepository(string name);
    void ForkRepository(string original_repo_name,string forked_repo_name);
    Node* FindRepository(string name);
    void ViewStats(string name);
    void Commit(string name);
    void Set(string name, bool is_public);
    void AddFile(string repo_name, string file_name); // Add file to repository
    void DeleteFile(string repo_name, string file_name); // Delete file from repository
    void WriteToCSV();
    void WriteToCSVHelper(Node* node, ofstream& file);
    void ReadFromCSV();
    void display(string useranme);
};