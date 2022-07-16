//Ford-Fulkerson Algorithm with augumenting path using simple DFS

#include<bits/stdc++.h>
using namespace std;

class Edge{
    public: 
        int from, to, capacity, flow;
        Edge* residual = nullptr;
        Edge(int from, int to, int capacity){
            this->from = from;
            this->to = to;
            this->capacity = capacity;
            flow = 0;
        }
        int remainingCapacity(){
            //cout<<"{from : "<<from<<"to : "<<to<<" capacity : "<<capacity<<" flow : "<<flow<<"}"<<endl;
            return capacity-flow;
        }
        int augumentFlow(int f){
            this->flow += f;
            this->residual->flow -= f;
        }
};
int dfs(int start, int T, vector<vector<Edge*>>& Graph, vector<int>& visited, int visitTarget, int flow){
    if(start == T){
        //cout<<"sink reached from - "<<start<<endl;
        return flow;
    }
    visited[start] = visitTarget;
    //cout<<start<<" visited"<<endl;
    for(int i = 0; i<Graph[start].size(); i++){
        Edge *e = Graph[start][i];
        
        if(e->remainingCapacity()>0 && visited[e->to]!= visitTarget){
            //cout<<"from - "<<start<<" - dfs started to - "<<e->to<<endl;
            int bottomNeck;
            bottomNeck = dfs(e->to, T, Graph, visited, visitTarget, min(flow, e->remainingCapacity()));
            if(bottomNeck>0){
                e->augumentFlow(bottomNeck);
                return bottomNeck;
            }
        }else{
            //cout<<"Address of edge  :"<<e<<endl;
            //cout<<"from - "<<start<<" - Not passed to "<<e->to<<" Reason: remaining_cap : "<<e->remainingCapacity()<<"  visited : "<<(visited[e->to]== visitTarget)<<endl;
        }
    }
    visited[start] = visitTarget-1;
    //cout<<start<<" unvisited"<<endl;
    return 0;
}

void GetGraph(vector<vector<Edge*>>& Graph){
    for(int i = 0; i<Graph.size(); i++){
        for(int j = 0; j<Graph[i].size(); j++){
            if(Graph[i][j]->capacity){
                //cout<<"Address of edge  :"<<&Graph[i][j]<<endl;
                cout<<" Edge "<<Graph[i][j]->from<<"  ->  "<<Graph[i][j]->to<<"     |   Flow "<< Graph[i][j]->flow<<"   |   Capacity "<<Graph[i][j]->capacity<<" |   residual : "<< (Graph[i][j]->capacity==0 ? "true" : "false") << endl;
                //cout<<"Address of edge  :"<<&(Graph[i][j]->residual)<<endl;
                cout<<" Edge "<<Graph[i][j]->residual->from<<"  ->  "<<Graph[i][j]->residual->to<<"    |   Flow "<< Graph[i][j]->residual->flow<<"   |   Capacity "<<Graph[i][j]->residual->capacity<<" |   residual : "<< (Graph[i][j]->residual->capacity==0 ? "true" : "false") << endl;
            }
        }
    }
}

int Ford_Fulkerson(vector<vector<Edge*>>& Graph, int N, int S, int T){
    int visitTarget = 1;
    vector<int> visited(N, 0);
    int flow = INT_MAX;
    int maxflow = 0;
    int i = 0;
    for(int f = dfs(S, T, Graph, visited, visitTarget, flow); f!=0; f = dfs(S, T, Graph, visited, visitTarget, flow) ){
        maxflow += f;
        visitTarget++;
        i++;
        cout<<i<<"th Graph : maxflow: "<<maxflow<<endl;
        //GetGraph(Graph);
    }
    //cout<<"number of f increments : "<<i<<endl;
    return maxflow;
}

void solve(){

    int N, E, MaxFlow = 0;
    cin>>N>>E;
    int S = N-2, T = N-1;
    vector<vector<Edge*>> Graph(N, vector<Edge*>());
    for(int i = 0; i<E; i++){
        int from, to, capacity;
        cin>>from>>to>>capacity;
        Edge* e1 = new Edge(from, to, capacity);
        Edge* e2 = new Edge(to, from, 0);
        e1->residual = e2;
        e2->residual = e1;
        Graph[from].push_back(e1);
        Graph[to].push_back(e2);
    }
    //cout<<"Initial Graph"<<endl;
    //GetGraph(Graph);
    MaxFlow = Ford_Fulkerson(Graph, N, S, T);

    cout<<"MaxFlow  :  "<<MaxFlow<<endl;
    GetGraph(Graph);
}

int main(){
    solve();
    return 0;
}















/*

number of nodes: N;
source is N-2; sink is N-1, 
Number of edges E;
all Edges
from -> to Cost

Test case:
      source is 9 and sink is 10
11         
17
0 3 10
2 5 15
5 8 10
3 1 20
7 5 7
6 10 15
8 10 10
1 2 10
3 6 15
9 1 5
4 1 15
7 4 10
4 3 3
5 4 4
6 7 10
9 0 10
9 2 10

Output : 23

*/