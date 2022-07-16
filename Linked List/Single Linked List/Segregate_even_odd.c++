#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
    node(int value, node* next)
        : value(value), next(next) {}
};

class List{
        node* head = NULL;
        node* tail = NULL;
    public:
        void push_front(int value){
            node* ptr = new node(value, head);
            head = ptr;
            if(!head)
                tail = ptr;
        }
        void push_back(int value){
            node* ptr = new node(value, NULL);
            if(!tail){
                head = ptr;
                tail = ptr;
            }
            else{
                tail->next = ptr;
                tail = ptr;
            }
        }
        void print_List(){
            node* temp = head;
            while(temp){
                cout<<temp->value<<" ";
                temp = temp->next;
            }
        }
        void delete_after(node* pre_ptr){//no case of deleting the first element;
            node* next_ptr = pre_ptr->next->next;
            delete pre_ptr->next;
            pre_ptr->next = next_ptr;
            if(!next_ptr)
                tail = pre_ptr;
        }
        void segregate(){
            node* track_even_ptr = NULL;
            node* temp = head;
            node* prev_temp = NULL;
            while(temp){
                if(!((temp->value)&1)){
                    if(!track_even_ptr && !prev_temp){   
                        track_even_ptr = head; 
                        prev_temp = temp;
                        temp = temp->next;
                    }
                    else if(!track_even_ptr && prev_temp){
                        int value = temp->value;
                        
                        temp = temp->next;
                        delete_after(prev_temp);
                        insert_after(NULL, value);
                        track_even_ptr = head;
                    }
                    else if(track_even_ptr->next == temp){
                        track_even_ptr = temp;
                        prev_temp = temp;
                        temp = temp->next;
                    }else{
                        int value = temp->value;
                        temp = temp->next;
                        delete_after(prev_temp);
                        insert_after(track_even_ptr, value);
                        track_even_ptr = track_even_ptr->next;
                    }
                }else{
                    prev_temp = temp;
                    temp = temp->next;
                }
            }
        }
        void insert_after(node* pos, int value){
            if(!pos){
                push_front(value);
                return;
            }
            if(!pos->next){
                push_back(value);
            }
            node* ptr = new node(value, pos->next);
            pos->next = ptr;
        }
        void deleteList(){
            node* temp = head;
            while(temp){
                node* temp1 = temp->next;
                delete temp;
                temp = temp1;
            }
        }
};
int main(){
    List even_odd_list;
    int total_number;
    cin>>total_number;
    cout<<"\n";
    for(int i = 0; i< total_number; i++){
        int num;
        cin>>num;
        even_odd_list.push_back(num);
    }
    even_odd_list.print_List();
    cout<<"\n";
    even_odd_list.segregate();
    even_odd_list.print_List();
    even_odd_list.deleteList();

    return 0;
}