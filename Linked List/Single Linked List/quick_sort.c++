#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
    node(node* next, int value) :next(next), value(value) {}
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
        void print_List(){
            node* temp = head;
            while(temp){
                cout<<temp->value<<" ";
                temp = temp->next;
            }
        }
        node* getTail(node* head){
            node* temp = head;
            while(temp && temp->next){
                temp = temp->next;
            }
            return temp;
        }
        node* partition(node* head, node* tail , node* &newhead, node* &newtail){
            cout<<"Partitioning at "<<tail->value<<"...\n";

            node* pivot = tail;
            node* temp = head;
            node* prev = NULL;
            newtail = pivot;
            while(temp!=pivot){
                if(temp->value < pivot->value){
                    if(!newhead){
                        newhead = temp;
                    }
                    prev = temp;
                    temp = temp->next;
                }
                else{
                    if(prev){
                        prev->next = temp->next;
                    }
                    node* tmp = temp->next;
                    temp->next = newtail->next; //or to NULL or it's already null;
                    newtail->next = temp;
                    newtail = temp;
                    temp = tmp;
                }
            }
            if(newhead == NULL) newhead = pivot;
            return pivot;
        }
        void QuickSort(){
            cout<<"QuickSorting...\n";

            head = QuickSortUtil(head, tail);
            cout<<"Sorting Done!\n";
            return;
        }
        node* QuickSortUtil(node* head, node* tail){
            if(!head || head == tail) return head;

            cout<<"QuickSortUtil...\n";
            node* newhead = NULL;
            node* newtail = NULL;
            node* pivot = partition(head, tail , newhead, newtail);
            if(pivot!=newhead){
                node* temp = newhead;
                while(temp->next != pivot){
                    temp = temp->next;
                }
                temp->next = NULL;

                newhead = QuickSortUtil(newhead,temp);
                temp = getTail(newhead);
                temp->next = pivot;
            }
            pivot->next = QuickSortUtil(pivot->next, newtail);
            return newhead;
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
    list.QuickSort();
    list.print_List();
    
    return 0;
}