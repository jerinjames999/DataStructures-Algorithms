#include<bits/stdc++.h>
using namespace std;

class Stack{
    int MaxSize;
    int size;
    int* ptr;
    public:
    Stack(int sz){
        ptr = new int[sz];
        if(ptr){
            cout<<"Stack created\n";
            MaxSize = sz;
            size = 0;
        }else{
            cout<<"Memory for Stack is not available\n";
        }
    }
    void push(int ele){
        if(size==MaxSize){
            cout<<"Stack is full\n";
            return;
        }
        ptr[size] = ele;
        size++;

    }
    bool empty(){
        return size==0;
    }
    void pop(){
        if(empty()){
            cout<<"Stack is empty, nothing to pop\n";
            return ;
        }
        size--;
    }
    int top(){
        if(size){
            return ptr[size-1];
        }else{
            cout<<"Stack is empty\n";
        }
    }
    ~Stack(){
        delete[] ptr;
        cout<<"Stack Memory Released\n";
    }
};

int main(){
    Stack S(4);
    cout<<S.empty()<<endl;
    S.push(1);
    S.push(2);
    S.push(3);
    S.push(4);
    S.push(5);
    cout<<S.top()<<endl;
    S.pop();
    cout<<S.empty()<<endl;
    return 0;
}