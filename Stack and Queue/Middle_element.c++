#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    node* next, *prev;
    int val;
    node(node* next , node* prev, int val) :next(next), prev(prev), val(val){}
};

class Middle_stack{
    node* head, *mid;
    int size;
    public:
    Middle_stack(): head(nullptr), mid(nullptr), size(0){}
    void push(int ele){
        node* ptr = new node(head, nullptr, ele);
        if(ptr){
            size++;
            cout<<"node pushed\n";
        }else{
            cout<<"memory not allocated\n";
            return;
        }
        if(!head){
            head = ptr;
            mid = ptr;
        }else{
            head->prev = ptr;
            head = ptr;
            if(size%2==1){
                mid = mid->prev;
            }
        }
        cout<<"size : "<<size<<endl;
    }
    void top(){
        if(size){
            cout<<head->val<<"\n";
        }else{
            cout<<"stack is empty\n";
        }
    }
    void pop(){
        if(size==0){
            cout<<"Stack is empty\n";
            return;
        }
        node* temp = head->next;
        delete head;
        size--;
        head = temp;
        if(head)
            head->prev = nullptr;
        if(size==0){
            head=nullptr;
            mid=nullptr;
        }
        if(size%2==0 && size){
            mid = mid->next;
        }
        cout<<"size : "<<size<<endl;
    }
    void middle(){
        if(mid){
            cout<<mid->val<<"\n";
        }else{
            cout<<"stack is empty\n";
        }
    }
    void delete_middle(){
        node* temp = mid;
        if(mid){
            if(mid->prev)
            mid->prev->next = mid->next;
            if(mid->next)
            mid->next->prev = mid->prev;
            
            if(size%2==1)
                mid = mid->next;
            else
                mid = mid->prev;
            size--;
            if(size==0){
                head= nullptr;
            }
            cout<<"deleting "<<temp->val<<"\n";
            delete temp;
        }else{
            cout<<"stack is empty\n";
        }
        cout<<"size : "<<size<<endl;
    }
};

int main(){
    Middle_stack mstk;
    mstk.push(1);
    mstk.push(2);
    mstk.push(3);
    mstk.push(4);
    mstk.push(5);
    mstk.push(6);
    mstk.push(7);
    mstk.delete_middle();
    mstk.delete_middle();
    mstk.delete_middle();
    mstk.delete_middle();
    mstk.delete_middle();
    mstk.delete_middle();
    mstk.delete_middle();

    return 0;
}