#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
        node(node* next, int value) : next(next), value(value){}
};

class List{
    node* head;
    node* tail;
    public:
        List(): head(NULL), tail(NULL) {}
        ~List(){
            node* temp = head;
            while(temp){
                node* next_temp = temp->next;
                delete temp;
                temp = next_temp;
            }
        }
        void push_back(int value){
            node* ptr = new node(NULL, value);
            if(!tail){
                head = ptr;
                tail = ptr;
            }else{
                tail->next = ptr;
                tail = ptr;
            }
        }
        bool check_palindrome(){
            stack<int> stack;
            node* temp = head;
            while(temp){
                stack.push(temp->value);
                temp = temp->next;
            }
            temp = head;
            while(temp){
                if(temp->value !=stack.top()) return false;
                stack.pop();
                temp = temp->next;
            }
            return true;
        }
        void print_List(){
            node* temp = head;
            while(temp){
                cout<<temp->value<<" ";
                temp = temp->next;
            }
        }
};

int main(){

    List list;
    int size;
    cin>>size;
    for(int i = 0; i<size; i++){
        int value;
        cin>>value;
        list.push_back(value);
    }
    list.print_List();
    cout<<"Palindrome? "<<list.check_palindrome()<<endl;
    return 0;
}