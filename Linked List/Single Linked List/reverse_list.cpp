#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
    node(){
        next = NULL;
    }
};

class List{
    node* head = NULL;
    node* tail = NULL;
    public:
    void push_front(int value){
        node* ptr = new node;
        ptr->value = value;
        ptr->next = head;
        head = ptr;
        if(!head)
            tail = ptr;
    }
    void reverse(){
        if(head && head->next){

            node* first_Ptr = head;
            node* second_Ptr = first_Ptr->next;
            node* third_Ptr = second_Ptr->next;
            do{
                second_Ptr->next = first_Ptr;
                first_Ptr = second_Ptr;
                second_Ptr = third_Ptr;
                if(second_Ptr)
                    third_Ptr = third_Ptr->next;
                else
                    break;
                
            }while(1);
            head->next = NULL;
            tail = head;
            head = first_Ptr;
        }
    }
    void reverse_it(node* head){

        node* prev_node = NULL;
        node* present_node = head;
        node* next_node;
        while(present_node){
            next_node = present_node->next;
            present_node->next = prev_node;
            prev_node = present_node;
            present_node = next_node;
        }
        tail = head;
        head = prev_node;//reseting head;

        // struct Node* reverseList(struct Node *head)
        //     {
        //         if(head == NULL || head -> next == NULL)
        //         return head;
        //         struct Node* tmp = reverseList(head -> next);    Using Recursion;
        //         head -> next -> next = head;
        //         head -> next = NULL;
        //         return tmp;
        //     }


    }
    void reverse_list_call(){
        reverse_it(head);
        head->next = NULL;
    }
    void Print_list(){
        node* temp = head;
        while(temp){
            cout<<temp->value<<" ";
            if(temp->next){
                temp= temp->next;
            }
            else{
                break;
            }
        }
    }
    void delete_list(){
        node* temp = head;
        while(temp){
            node* second = temp->next;
            delete temp;
            temp = second;
            cout<<" Deleting";
        }
    }
};

int main(){

    int array[4] = {1,2,3,4};
    List Number;
    for(int i = 0; i< 4; i++){
        Number.push_front(array[i]);
    }
    Number.Print_list();
    Number.reverse();
    Number.Print_list();
    Number.delete_list();
    return 0;   
}