#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        node* prev;
        int value;
    node(node* next, node* prev, int value) :next(next), prev(prev), value(value) {}
};

class CircularList{
    node* head;
    CircularList() : head(NULL) {}
    ~CircularList(){
        if(!head) return;
        node* last = head->prev;
        node* temp = head;
        while(temp->next != head){
            node* tmp = temp->next;
            delete temp;
            temp = tmp;
        }
        delete last;

    }
}

int main(){

}