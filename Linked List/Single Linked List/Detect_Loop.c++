/*
#include<bits/stdc++.h>
using namespace std;
class node{
    public:
        node* next;
        int value;
        node(node* next, int value) : next(next), value(value) {}
};

class List{
    node* head;
    node* tail;
    node* loop_node;
    int size;
    public:
        List(): head(NULL), tail(NULL), loop_node(NULL), size(0) {}
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
            size++;
        }
        void detcet_loop(){
            unordered_set<node*> ptr_set;
            node* temp = head;
            while(temp){
                if(ptr_set.find(temp) != ptr_set.end()) {loop_node = temp;cout<<"loopHere = "<<loop_node->value<<endl; return;}//Don't skip this bracket;
                ptr_set.insert(temp);
                temp = temp->next;
                cout<<"going through"<<temp->value<<endl;
            }
        }
        void print_loop(){
            detcet_loop();
            if(loop_node){
                cout<<loop_node->value<<"-->";
                node* temp=loop_node;
                while(temp->next !=loop_node){
                    temp= temp->next;
                    cout<<temp->value<<"-->";
                }
                cout<<loop_node->value;
            }
            cout<<"\nNo Loop Detected";
        }
        void make_loop(int loop_place){
            node* temp = head;
            while(loop_place--){
                temp = temp->next;
            }
            tail->next = temp;
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
    list.make_loop(size/2);
    list.print_loop();
    return 0;
}
*/
//Time  O(n)
//Space O(n);
//Better and fastest algorithm to find the loop in Linked List is :   

            /*Floyd’s Cycle-Finding Algorithm*/         //Time : O(n), Space: O(1);

#include<bits/stdc++.h>
using namespace std;
class node{
    public:
        node* next;
        int value;
        node(node* next, int value) : next(next), value(value) {}
};

class List{
    node* head;
    node* tail;
    node* loop_node;
    int size;
    public:
        List(): head(NULL), tail(NULL), loop_node(NULL), size(0) {}
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
            size++;
        }
        void detcet_loop(){
            
            node* ptr1 = head;
            node* ptr2 = head;
            while(ptr2 && ptr2->next && ptr2->next->next){
                ptr1 = ptr1->next;
                ptr2 = ptr2->next->next;
                if(ptr1 == ptr2) {loop_node = ptr1; cout<<"Loop Node = "<<loop_node->value<<endl; return;}//Don't skip this bracket;
            }
        }
        void print_loop(){
            detcet_loop();
            if(loop_node){
                cout<<loop_node->value<<"-->";
                node* temp=loop_node;
                while(temp->next !=loop_node){
                    temp= temp->next;
                    cout<<temp->value<<"-->";
                }
                cout<<loop_node->value;
            }
            else cout<<"\nNo Loop Detected";
        }
        void make_loop(int loop_place){
            node* temp = head;
            while(loop_place--){
                temp = temp->next;
            }
            tail->next = temp;
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
    int loop_at;
    cin>>loop_at;
    list.make_loop(loop_at);
    list.print_loop();
    return 0;
}




