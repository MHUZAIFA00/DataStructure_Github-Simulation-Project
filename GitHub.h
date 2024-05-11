#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include<vector>
#include<map>
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
    string username, password;
    Repository rep;
    User(string username, string password);
};
class Repository
{
public:
    Node* root;
    string User_directory;
    map<string, User> users;
    Repository();
    void Register(string username, string password);
    bool Login(string username, string password);
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
    void display();
};