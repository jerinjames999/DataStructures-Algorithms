#include <bits/stdc++.h>
using namespace std;

struct node{
    int key;
    node* next;
    node(int val): key(val){}
};

class LinkedList{
    public:
    node* head;
    int sz;
    LinkedList(){
        head=nullptr;
        sz = 0;
    }
    void push_front(int val){
        node* ptr = new node(val);
        ptr->next = head;
        head = ptr;
        sz++;
    }

    void reverse_recurse(){
        node* ptr = reverse_list(head);
        head = ptr;
    }

    node* reverse_list(node* start){
        if(start==nullptr){
            return nullptr;
        }
        if(start->next==nullptr){
            return start;
        }
        node* ptr = reverse_list(start->next);
        start->next->next=start;
        start->next = nullptr;
        return ptr;
    }
    void reverse_iter(){
        if(head==nullptr||head->next==nullptr){
            return;
        }
        node* curr1 = head, *curr2 = head->next;
        while(1){
            node* temp = curr2->next;
            curr2->next = curr1;
            curr1=curr2;
            curr2 = temp;
            if(!curr2){
                break;
            }
        }
        head->next = nullptr;
        head = curr1;
    }



    void display(){
        node* curr = head;
        while(curr){
            cout<<curr->key<<" ";
            curr= curr->next;
        }
        cout<<endl;
    }

};


int main()
{
    LinkedList List;
    List.push_front(1);
    List.push_front(2);   
    List.reverse_iter();
    List.push_front(3);   
    List.push_front(4);   
    List.reverse_iter();
    List.push_front(5);
    List.reverse_iter();
    List.display();
    return 0;
}