#include<bits/stdc++.h>
using namespace std;

class Queue{
    int MaxSize;
    int size;
    int* ptr;
    int front;
    int rear;
    public:
    Queue(int sz){
        ptr = new int[sz];
        if(ptr){
            cout<<"Queue created\n";
            MaxSize = sz;
            size = 0;
            front = -1;
            rear = -1;
        }else{
            cout<<"Memory for Queue is not available\n";
        }
    }
    void push(int ele){
        if(size==MaxSize){
            cout<<"Queue is full\n";
            return;
        }
        if(size==0){
            front = 0;
            rear = 0;
        }else{
            rear = (rear+1)%MaxSize;
        }
        ptr[rear] = ele;
        size++;
    }
    bool empty(){
        return size==0;
    }
    void pop_back(){
        if(empty()){
            cout<<"Queue is empty, nothing to pop\n";
            return ;
        }
        size--;
        rear = (rear + MaxSize-1)%MaxSize;
        if(size==0){
            front = -1;
            rear = -1;
        }
    }
    void pop(){
        if(empty()){
            cout<<"Queue is empty, nothing to pop\n";
            return ;
        }
        size--;
        front = (front + MaxSize+1)%MaxSize;
        if(size==0){
            front = -1;
            rear = -1;
        }

    }
    int rear1(){
        if(size){
            return ptr[rear];
        }else{
            cout<<"Queue is empty\n";
        }
    }
    int front1(){
        if(size){
            return ptr[front];
        }else{
            cout<<"Queue is empty\n";
        }
    }
    ~Queue(){
        delete[] ptr;
        cout<<"Queue Memory Released\n";
    }
};

int main(){

    Queue Q(4);
    cout<<Q.empty()<<endl;
    Q.push(1);
    Q.push(2);
    Q.push(3);
    Q.push(4);
    Q.pop();
    Q.push(5);
    cout<<Q.rear1()<<endl;
    cout<<Q.front1()<<endl;
    Q.pop();
    cout<<Q.empty()<<endl;
    return 0;
}