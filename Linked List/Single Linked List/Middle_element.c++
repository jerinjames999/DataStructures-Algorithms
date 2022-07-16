#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    node* next =NULL;
    int value;
    node(node* next, int value) :  next(next), value(value) {}
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
        node* middle_element(){
            if(!head) return NULL;
            if(!head->next) return head;
            node* main_ptr = head;
            node* second_ptr = head;
            while(second_ptr->next){
                cout<<"1testing "<<second_ptr->value<<endl;
                second_ptr = second_ptr->next->next;
                if( second_ptr)
                    main_ptr = main_ptr->next;
                else{
                    break;
                }
                cout<<"2testing "<<second_ptr->value<<endl;
            }
            return main_ptr;
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
    node* middle_element = list.middle_element();
    if(!middle_element) {cout<<"Error"; return 0;}

    cout<<"The Middle Element is = "<< middle_element->value;
    return 0;
}


