#include<bits/stdc++.h>
using namespace std;
//push, pop, top, isfull
class Kstack{
    vector<int> arr;
    vector<int> top;
    vector<int> next;
    int free, n, k;
    public:
    Kstack(int n, int k): free(0), n(n), k(k){
        arr = vector<int>(n);
        top = vector<int>(k, -1);
        next = vector<int>(n);
        for(int i =0; i<n; i++){
            next[i] = i+1;
        }
        next[n-1] = -1;
        free = 0;
    }
    bool isfull(){
        return free == -1;
    }
    bool isEmpty(int stack_id){
        return top[stack_id]==-1;
    }
    void push(int stack_id, int ele){
        if(isfull()){
            cout<<"stack is full\n";
            return;
        }
        arr[free] = ele;
        int temp = next[free];
        next[free] = top[stack_id];
        top[stack_id] = free;
        free = temp;
        
    }
    void stk_top(int stack_id){
        if(top[stack_id]==-1){
            cout<<"stack is empty\n";return;
        }
        cout<<arr[top[stack_id]]<<"\n";
    }
    void pop(int stack_id){
        if(top[stack_id]==-1){
            cout<<"stack is empty\n";
            return ;
        }
        int temp = top[stack_id];
        top[stack_id] = next[temp];
        next[temp] = free;
        free = temp;
    }
    void print(){
        for(int i = 0; i<n;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
        for(int i = 0; i<k;i++){
            cout<<top[i]<<" ";
        }
        cout<<endl;
        for(int i = 0; i<n; i++){
            cout<<next[i]<<" ";
        }
        cout<<endl<<endl;
    }
};

int main(){

    Kstack st(15, 3);
    st.push(0, 100);
    st.push(1, 101);
    st.push(2, 102);
    st.push(0, 103);
    // st.print();
    st.stk_top(0);
    st.pop(0);
    // st.print();
    st.stk_top(0);
    st.pop(0);
    // st.print();
    st.stk_top(0);
    st.pop(0);
    // st.print();
    st.push(1, 104);
    st.push(2, 105);
    st.push(1, 106);
    st.push(1, 107);
    st.push(2, 108);
    st.push(0, 109);
    st.push(1, 110);
    st.push(1, 111);
    st.stk_top(0);
    st.pop(0);
    st.stk_top(1);
    st.pop(1);
    st.stk_top(1);
    st.pop(1);
    st.stk_top(1);
    st.pop(1);
    st.stk_top(2);
    st.pop(2);
    st.stk_top(2);
    st.pop(2);
    return 0;
}