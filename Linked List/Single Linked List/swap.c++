#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
    node(node* next, int value) : next(next), value(value) {}
};

class List{
    node* head = NULL;
    node* tail = NULL;
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
    }
    void swap_xy(int x, int y){
        node* temp = head;
        node* prev_first = NULL;
        node* prev_second = NULL;
        bool found_one = 0;
        node* prev_node = NULL;
        while(temp){
            if(temp->value == x || temp->value == y){
                if(!found_one)  {prev_first = prev_node;    found_one = 1;}
                else{prev_second = prev_node;   break;}
            }
            prev_node = temp;
            temp = temp->next;
        }
        if(prev_first){//so the first is not the head
            node* temp = prev_second->next;
            prev_second->next = prev_second->next->next;
            temp->next = prev_first->next;
            prev_first->next = temp;
            if(prev_second != prev_first->next){//Not adjacent case
                node* temp2 = temp->next;
                temp->next = temp->next->next;
                temp2->next = prev_second->next;
                prev_second->next = temp2;
            }
        }else{
            node* temp = prev_second->next;
            prev_second->next = prev_second->next->next;
            temp->next = head;
            head = temp;
            if(prev_second != head){//Not adjacent case
                node* temp2 = temp->next;
                temp->next = temp->next->next;
                temp2->next = prev_second->next;
                prev_second->next = temp2;
            }
        }
        
    }
    void print_List(){
        node* temp = head;
        while(temp){
            cout<<temp->value<<" ";
            temp = temp->next;
        }
    }
    void delete_list(){
        node* temp = head;
        while(temp){
            node* second = temp->next;
            delete temp;
            temp = second;
        }
    }
};

int main(){

    int array[9] = {1,2,3,4,5,6,7,8,9};
    List Number;
    for(int i = 0; i< 9; i++){
        Number.push_back(array[i]);
    }
    Number.print_List();
    Number.swap_xy(2,9);
    cout<<endl;
    Number.print_List();
    Number.delete_list();
    return 0;
}