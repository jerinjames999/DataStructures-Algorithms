#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int key;
    node* next = NULL;
};

class List{
        node* head = NULL;
        node* tail = NULL;
        int size;
    public:
        List(){
            head = NULL;
            size = 0;
        }
        void push_front(int value){
            node* ptr = new node;
            ptr->key = value;
            ptr->next = NULL;
            
            if(!head)
                head=ptr;
            else{
                node* temp_head = head;
                head = ptr;
                ptr->next = temp_head;
            }
            size++;
        }
        
        void print_List(){
            node* temp = head;
            while(temp){
                cout<<temp->key<<" ";
                temp = temp->next;
            }
        }
        void multiply(int num2){
            int reminder = 0;
            node* temp = head;
            while(temp){
                int newNumber = reminder + (temp->key * num2);
                int digit = newNumber%10;
                reminder = newNumber/10;
                temp->key = digit;
                if(temp->next){
                    temp = temp->next;
                }else{
                    break;
                }
                    
            }
            while(reminder){
                int newNumber = reminder%10;
                reminder = reminder/10;
                node* ptr = new node;
                ptr->key = newNumber;
                temp->next = ptr;
                temp = ptr;
            }
        }

        void reverse(){
            if(head && head->next){

                node* first_Ptr = head;
                node* second_Ptr = first_Ptr->next;
                node* third_Ptr = second_Ptr->next;
                do{
                    second_Ptr->next = first_Ptr;
                    first_Ptr = second_Ptr;
                    second_Ptr = third_Ptr;
                    if(second_Ptr)
                        third_Ptr = third_Ptr->next;
                    else
                        break;
                    
                }while(1);
                head->next = NULL;
                tail = head;
                head = first_Ptr;
            }
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
    int num_size=5;
    int array[5] = {3,4,2,9,9};
    List Number;
    for(int i = 0; i < num_size; i++){
        Number.push_front(array[i]);
    }
    Number.print_List();
    cout<<"\n";
    cout<<" Enter The multiplying Number";
    int no;
    cin>>no;
    Number.multiply(no);
    Number.reverse();
    Number.print_List();
    Number.deleteList();

    return 0;
}
