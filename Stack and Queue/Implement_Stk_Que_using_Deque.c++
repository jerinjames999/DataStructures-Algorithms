#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int val;
    node* pre;
    node* next;
    node(int val, node* pre, node* next): val(val), pre(pre), next(next){}
};

class Deque{
    node* head, *tail;
    int sz;
    public:
    Deque():head(nullptr), tail(nullptr), sz(0){}

    void push_front(int val){

    }
    void push_back(int val){
        node* ptr = new node(val, tail, nullptr);
        if(!ptr){
            cout<<"node not created\n";return;
        }
        sz++;
        if(!tail){
            head = ptr;
            tail = ptr;
            return;
        }
        
        tail->next = ptr;
        tail = ptr;
    }
    void pop_front(){

    }
    void pop_back(){
        if(empty()){
            cout<<"Container is empty\n";return;
        }
        sz--;
        node* temp = tail->pre;
        delete tail;
        tail = temp;
        if(!tail){
            head=nullptr;
        }
    }
    int front(){
        if(!empty()){
            return head->val;
        }
        return INT_MIN;
    }
    int back(){
        if(!empty()){
            return tail->val;
        }
        return INT_MIN;
    }
    int size(){
        return sz;
    }
    bool empty(){
        return sz==0;
    }
};

class Stack : public Deque{
    public:
    void push(int val){
        push_back(val);
    }
    void pop(){
        pop_back();
    }
    int top(){
        return back();
    }
    int size(){
        return Deque::size();
    }
    bool empty(){
        return Deque::empty();
    }
};

int main(){
    Stack obj;
    obj.push(1);
    obj.push(2);
    cout<<obj.top()<<endl;
    cout<<obj.size()<<endl;
    obj.push(3);
    cout<<obj.top()<<endl;
    obj.pop();
    cout<<obj.top()<<endl;
    obj.push(4);

    return 0;
}
