#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class userNode;
class commitNode 
{
public:
    string commitMsg;
    commitNode* next;
    commitNode(string msg);
};
class fileNode 
{
public:
    string fileName;
    fileNode* next;
    fileNode(string name);
};
class repositoryNode 
{
public:
    string repositoryName;
    bool isPublic;
    int forkCount;
    commitNode* commit;
    fileNode* files;
    repositoryNode* next;
    repositoryNode(string name, bool isPublic);
};
class userNode 
{
public:
    string userName;
    string password;
    repositoryNode* repositories;
    userNode* next;
    userNode** following;
    userNode** followers;
    int followingCount;
    userNode() {}
    userNode(string name, string pass);
    ~userNode();
};
class HashTable 
{
public:
    static const int TABLE_SIZE = 10;
    struct User 
    {
    public:
        string username;
        string passwordHash;
        User* next;

        User(const string& uname, const string& pword) : username(uname), passwordHash(pword), next(nullptr) {}
    };
    User* table[TABLE_SIZE];
    int hashFunction(const string& key);
public:
    HashTable();
    ~HashTable();
    void insertUser(const string& username, const string& password);
    User* searchUser(const string& username);
};
class Graph 
{
public:
    userNode* vertices;
    bool** adjMatrix;
    int size;
    userNode* findUser(const string& name) 
    {
        userNode* current = vertices;
        while (current != nullptr) {
            if (current->userName == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    int findUserIndex(const string& name) {
        userNode* current = vertices;
        int index = 0;
        while (current != nullptr) {
            if (current->userName == name) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1; // User not found
    }

    Graph() {
        vertices = nullptr;
        adjMatrix = nullptr;
        size = 0;
    }
    ~Graph() {
        userNode* current = vertices;
        while (current != nullptr) {
            userNode* temp = current;
            current = current->next;
            delete temp;
        }

        if (adjMatrix != nullptr) {
            for (int i = 0; i < size; ++i) {
                delete[] adjMatrix[i];
            }
            delete[] adjMatrix;
        }
    }

    void addUser(const string& name) {
        if (findUser(name) == nullptr) {
            userNode* newUser = new userNode;
            newUser->next = vertices;
            vertices = newUser;
            ++size;

            // Resize adjacency matrix
            bool** newMatrix = new bool* [size];
            for (int i = 0; i < size; ++i) {
                newMatrix[i] = new bool[size];
                for (int j = 0; j < size; ++j) {
                    newMatrix[i][j] = false;
                }
            }

            // Copy old data to new matrix
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - 1; ++j) {
                    newMatrix[i][j] = adjMatrix[i][j];
                }
                delete[] adjMatrix[i];
            }
            delete[] adjMatrix;

            adjMatrix = newMatrix;
        }
    }

    void addEdge(const string& from, const string& to) {
        int fromIndex = findUserIndex(from);
        int toIndex = findUserIndex(to);
        if (fromIndex != -1 && toIndex != -1) {
            adjMatrix[fromIndex][toIndex] = true;
        }
    }

    void removeEdge(const string& from, const string& to) {
        int fromIndex = findUserIndex(from);
        int toIndex = findUserIndex(to);
        if (fromIndex != -1 && toIndex != -1) {
            adjMatrix[fromIndex][toIndex] = false;
        }
    }

    bool hasEdge(const string& from, const string& to) {
        int fromIndex = findUserIndex(from);
        int toIndex = findUserIndex(to);
        if (fromIndex != -1 && toIndex != -1) {
            return adjMatrix[fromIndex][toIndex];
        }
        return false;
    }
};

class GitHub {
public:
    Graph graph;
    HashTable usersTable;

    GitHub();
    ~GitHub();
    void registerUser();
    void loginUser();
    void logoutUser();
    void viewUserProfile();
    void createRepository();
    void deleteRepository();
    void forkRepository();
    void changeRepoVisibility();
    void addCommit();
    void addFile();
    void deleteFile();
    void viewRepositoryStats();
    void followUser();
    void unfollowUser();
    void writeToCSV();
    void readFromCSV();
    userNode* searchUser(string name);
    repositoryNode* searchRepository(repositoryNode* node, string name);
    void deleteCommit(commitNode* node);
    void deleteFile(fileNode* node);
    void deleteRepository(repositoryNode* node);

    userNode* users;
    userNode* loggedInUser;
};