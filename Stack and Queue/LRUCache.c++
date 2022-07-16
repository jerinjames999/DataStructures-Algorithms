#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    pair<int,int> val;
    node* prev;
    node*next;
    node(pair<int,int> val, node* prev, node* next): val(val), prev(prev), next(next){}
};

class DLL{
    
    public:
    node* head, *tail;
    int size;
    DLL(): head(nullptr), tail(nullptr){}
    node* createnode(pair<int,int> val,node* prev = nullptr, node* next = nullptr){
        return new node(val, prev, next);
    }
    node* push_front(pair<int,int> val){    
        node* ptr = createnode(val, nullptr, head);
        if(!ptr){
            cout<<"Memory Finished\n";return nullptr;
        }
        size++;
        if(!head){
            head = ptr;
            tail = ptr;
            return ptr;
        }
        head->prev = ptr;
        head = ptr;
        return ptr;
    }
    int delete_node(node* ptr){
        size--;
        if(head==ptr && tail== ptr){
            tail = nullptr;
            head = nullptr;
            int value = ptr->val.second;
            delete ptr;
            return value;
        }
        if(tail==ptr){
            tail = ptr->prev;
            tail->next = nullptr;
            int value = ptr->val.second;
            delete ptr;
            return value;
        }
        if(head==ptr){
            head=ptr->next;
            head->prev = nullptr;
            int value = ptr->val.second;
            delete ptr;
            return value;
        }
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
        int value = ptr->val.second;
        delete ptr;
        return value;
    }


};

class LRUCache{
    int capacity;
    DLL* dll;
    unordered_map<int, node*> Address_Book;
    public:
    LRUCache(int cap): capacity(cap){
        dll = new DLL();
    }
    void put(int key, int val){
        if(Address_Book.find(key)==Address_Book.end()){
            if(dll->size<capacity){
                Address_Book[key] = dll->push_front({key, val});
            }else{
                Address_Book.erase(dll->tail->val.first);
                dll->delete_node(dll->tail);
                Address_Book[key] = dll->push_front({key, val});
            }
        }else{
            dll->delete_node(Address_Book[key]);
            Address_Book[key] = dll->push_front({key, val});
        }
    }
    int get(int key){
        if(Address_Book.find(key)==Address_Book.end()){
            return -1;
        }
        int ans = dll->delete_node(Address_Book[key]);
        Address_Book[key] = dll->push_front({key, ans});
        return ans;
    }
};

int main(){
    int cap;
    cin>>cap;
    LRUCache lru(cap);

    while(1){
        int type;
        cout<<"Enter type\n";
        cin>>type;
        if(type==0){
            cout<<"Enter 2 numbers\n";
            int k, v;
            cin>>k>>v;
            lru.put(k, v);
        }else if(type==1){
            cout<<"Enter 1 get number\n";
            int k;
            cin>>k;
            cout<<lru.get(k)<<endl;
        }else{
            break;
        }
    }
    cout<<"EXITING\n";
    
    return 0;
}