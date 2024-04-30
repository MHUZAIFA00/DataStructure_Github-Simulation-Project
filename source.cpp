#include "GitHub.h"
#include<iostream>
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
void Repository::CreateRepository(string name, bool is_public) 
{
    if (root == NULL) 
    {
        root = new Node(name, is_public);
    }
    else 
    {
        Node* current = root;
        while (true) {
            if (name < current->name) 
            {
                if (current->left == NULL) 
                {
                    current->left = new Node(name, is_public);
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
                    current->right = new Node(name, is_public);
                    current->right->parent = current;
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
