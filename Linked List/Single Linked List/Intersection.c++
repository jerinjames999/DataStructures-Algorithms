#include<bits/stdc++.h>
using namespace std;

class node{
    public:
        node* next;
        int value;
    node(node* next, int value) : next(next), value(value) {}
};

class List{
    node* head = NULL;
    node* tail = NULL;
    public:
    void push_back(int value){
            node* ptr = new node(NULL, value);
            if(!tail){
                head = ptr;
                tail = ptr;
            }
            else{
                tail->next = ptr;
                tail = ptr;
            }
    }
    List operator&&(List list2){
        cout<<"entered here";
        List intersection;
        node* temp1 = head;
        node* temp2 = list2.head;
        while(temp1){
            while(temp2){
                if(temp1->value == temp2->value){
                    intersection.push_back(temp1->value);
                    temp2 = temp2->next;
                    break;
                }
                else if(temp1->value > temp2->value){
                    temp2 = temp2->next;
                }
                else {break;}
            }
            temp1 = temp1->next;
        }
        return intersection;
    }
    void print_List(){
        node* temp = head;
        while(temp){
            cout<<temp->value<<" ";
            temp = temp->next;
        }
    }
    void delete_list(){
        node* temp = head;
        while(temp){
            node* second = temp->next;
            delete temp;
            temp = second;
        }
    }
};

int main(){

    int array1[8] = {1,2,3,4,6,7,8,9};
    List list1;
    for(int i = 0; i< 8; i++){
        list1.push_back(array1[i]);
    }
    cout<<endl;
    int array2[6] = {1,3,4,5,8,9};
    List list2;
    for(int i = 0; i< 6; i++){
        list2.push_back(array2[i]);
    }

    list1.print_List();
    cout<<endl;
    list2.print_List();
    //List intersection = list1.intersection(list2);
    List intersection = list1 && list2;
    cout<<endl;
    intersection.print_List();
    cout<<endl;
    list1.delete_list();
    list2.delete_list();
    intersection.delete_list();
    return 0;
}