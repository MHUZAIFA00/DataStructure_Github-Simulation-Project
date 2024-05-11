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
class Repository
{
public:
    Node* root;
    Repository();
    void CreateRepository(string name, bool is_public, int num_files, int num_commits, int num_forks);
    void DeleteRepository(string name);
    Node* FindRepository(string name);
    void ViewStats(string name);
    void Commit(string name);
    void Set(string name, bool is_public);
    void AddFile(string repo_name, string file_name); // Add file to repository
    void DeleteFile(string repo_name, string file_name); // Delete file from repository
    void WriteToCSV();
    void WriteToCSVHelper(Node* node, ofstream& file);
    void ReadFromCSV();
};