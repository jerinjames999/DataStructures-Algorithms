#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
        node(node* next, int value) :next(next), value(value){}
};

class List{
    node* head = NULL;
    node* tail = NULL;
    int size = 0;
    int length;
    public:
        void push_back(int value){
            node* ptr = new node(NULL, value);
            if(!tail){
                head = ptr;
                tail = ptr;
            }
            else{
                tail->next = ptr;
                tail = ptr;
            }
            size++;
        }
        int list_size(){
            return size;
        }
        int  list_length(){
            length = 0;
            node* temp = head;
            while(temp){
                length++;
                temp = temp->next;
            }
            return length;
        }
        ~List(){
            node* temp = head;
            while(temp){
                node* next_temp = temp->next;
                delete temp;
                temp = next_temp;
            }
        }
};


int main(){
    List list;
    cout<<"Enter size : ";
    int size;
    cin>>size;
    for(int i = 0; i < size; i++){
        int element;
        cin>>element;
        list.push_back(element);
    }
    cout<<"\nLength of the List = "<<list.list_length();
    cout<<"\nSize = "<<list.list_size();
}