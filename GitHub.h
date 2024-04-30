#include <string>
using namespace std;
class Node 
{
public:
    string name;
    bool is_public;
    int num_files;
    int num_commits;
    int num_forks;
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
    void CreateRepository(string name, bool is_public);
};
