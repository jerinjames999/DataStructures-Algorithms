#include<bits/stdc++.h>
using namespace std;

/*
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
*/

class DisjointSet{
    int *Parent, *Rank, *Size, n, no_components;
    public:
        DisjointSet(int n){
            this->n = n;
            Parent = new int[n];
            Rank = new int[n];
            Size = new int[n];
            makeset();
        }
        void makeset(){
            for(int i = 0; i< n; i++){
                Parent[i] = i;
                Rank[i] = 1;
                Size[i] = 1;
            }
            no_components = n;
        }
        int Find(int a){
            if(Parent[a] == a ){
                return a;
            }
            return Parent[a] = Find(Parent[a]);
        }
        bool Union(int a, int b)//returns 0 if no union happened, else union happened
        {
            int aRoot = Find(a);
            int bRoot = Find(b);
            if(aRoot == bRoot) return 0;

            if(Rank[aRoot]>Rank[bRoot]){
                Parent[bRoot] = aRoot;
                Size[aRoot] += Size[bRoot];
            }
            else{
                Parent[aRoot] = bRoot;
                Size[bRoot] += Size[aRoot];
            }
            no_components--;
            if(Rank[aRoot] == Rank[bRoot]){
                Rank[bRoot]++;
            }
            return 1;
        }
        int no_of_components(){
            return no_components;
        }
        vector<int> Set_size(){//Just to find the size of small sets;
            vector<int> Ssize;
            for(int i = 0; i<n; i++){
                if(Parent[i] == i){
                    Ssize.push_back(Size[i]);
                }
            }
            return Ssize;
        }
        
};

int main(){
    int n;
    cin>>n;
    DisjointSet wonderland(6);
    wonderland.Union(0,2);
    wonderland.Union(0,1);
    wonderland.Union(4,5);
    for(int i = 0; i<n; i++){
        cout<<wonderland.Find(i)<<" ";
    }
    cout<<endl;
    vector<int> Ssize = wonderland.Set_size();

    for(int i = 0; i<Ssize.size(); i++){
        cout<<Ssize[i]<<" ";
    }

    return 0;
}