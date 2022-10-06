#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
 
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

void postOrderiterative(Node* root){
    stack<Node*> st;
    Node* curr = root;
    if(!curr){
        return root;
    }

    while(!st.empty()){
        // cout<<"Hi"<<endl;
        if(curr){
            st.push(curr);
            if(curr->right){
                curr=curr->right;
            }
        }else{
            curr = st.top();
            st.pop();
            cout<<curr->data<<" ";
        }

        if(curr){
            st.push(curr);
            cout<<curr->data<<" ";
            curr = curr->left;
        }else{
            curr = st.top();
            st.pop();
            curr=curr->right;
        }

    }
}

int main(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    root->right->left->left = new Node(7);
    root->right->left->right = new Node(8);
 
    postOrderiterative(root);
 
    return 0;
    return 0;
}