#include <iostream>
#include <stack>
using namespace std;
 
// Binary Tree node
struct Node {
    int key;
    struct Node *left, *right;
};

void spiralPrint(struct Node* root)
{
  deque<Node*> dq;
  dq.push_back(root);
  bool reverse=true;
  while(!dq.empty())
  {
    int n=dq.size();
    if(!reverse)
    {
      while(n--)
      {
        if(dq.front()->left!=NULL)
        {
          dq.push_back(dq.front()->left);
        }
        if(dq.front()->right!=NULL)
        {
          dq.push_back(dq.front()->right);
        }
        cout<<dq.front()->key<<" ";
        dq.pop_front();
      }
      reverse=!reverse;
    }
    else
    {
      while(n--)
      {
        if(dq.back()->right!=NULL)
        {
          dq.push_front(dq.back()->right);
        }
        if(dq.back()->left!=NULL)
        {
          dq.push_front(dq.back()->left);
        }
        cout<<dq.back()->key<<" ";
        dq.pop_back();
      }
      reverse=!reverse;
    }
  }
}

struct Node* newNode(int data)
{
    struct Node* node = new struct Node;
    node->key = data;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}

int main()
{
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(7);
    root->left->right = newNode(6);
    root->right->left = newNode(5);
    root->right->right = newNode(4);
    cout << "Spiral Order traversal of binary tree is :\n";
    spiralPrint(root);
 
    return 0;
}