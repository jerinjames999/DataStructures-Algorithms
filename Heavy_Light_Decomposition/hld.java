import java.util.ArrayList;
import java.util.Scanner;
import static java.lang.Math.*;


public class Main {
    //problem specific variables
    static ArrayList<Pair> adj[];
    static int U[], V[];

    //HLD stuff
    static int subtree_size[], chain[], chainHead[], position[], chainId = 0,pos = 0;
    
    //LCA stuff
    static int parent[][], level[], MAX;

    //Segment tree related stuff
    static int n, arr[], tree[];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        while(t-->0) {
            //reset
            chainId = 0;
            pos = 0;

            n = scanner.nextInt();
            MAX = (int)(log(n)/log(2));
            adj = new ArrayList[n+1];
            for(int i=1;i<=n;++i) {
                adj[i] = new ArrayList<>();
            }
            U = new int[n];
            V = new int[n];
            for(int i=1;i<n;++i) {
                int u = scanner.nextInt(), v = scanner.nextInt(), c = scanner.nextInt();
                adj[u].add(new Pair(v, c));
                adj[v].add(new Pair(u, c));
                U[i] = u;
                V[i] = v;
            }
            parent = new int[n+1][MAX+1];
            chain = new int[n+1];
            chainHead = new int[n+1];
            position = new int[n+1];
            subtree_size = new int[n+1];
            arr = new int[n];
            level = new int[n+1];
            int sz = (int)pow(2, ceil(log(n)/log(2)) + 1);
            tree = new int[sz];
            dfs(1,0, 0);
            chainHead[0] = 1;
            HLD(1,0);
            //print the array
            build(1,0, n-1);
            while(true) {
                String s = scanner.next();
                if(s.equals("DONE")) {
                    break;
                }
                if(s.equals("QUERY")) {
                    int u = scanner.nextInt(), v = scanner.nextInt() , LCA = lca(u,v);
                    int max = 0;
                    max = max(max, queryUp(u, LCA));
                    max = max(max, queryUp(v, LCA));
                    System.out.println(max);
                }
                else {
                    int idx = scanner.nextInt(), cost = scanner.nextInt();
                    int u = U[idx], v = V[idx];
                    if(level[u]>level[v]) {
                        update(position[u], cost);
                    }
                    else {
                        update(position[v], cost);
                    }
                }
            }
        }
    }
    static void dfs(int v, int par, int l) {
        parent[v][0] = par;
        for(int i=1;i<=MAX;++i) {
            if(parent[v][i-1]!=0) {
                parent[v][i] = parent[parent[v][i-1]][i-1];
            }
        }
        subtree_size[v] += 1;
        level[v] = l;
        for(Pair p : adj[v]) {
            if(p.x!=par) {
                dfs(p.x, v, l+1);
                subtree_size[v]+=subtree_size[p.x];
            }
        }
    }
    
     /**
      * Decompose the tree into chains, keeping all of all values we need
    */
    static void HLD(int v, int par) {
        int heavyChild = -1, heavySize = 0,heavyEdgeWeight = -1;
        chain[v] = chainId;
        position[v] = pos++;
        for(Pair p : adj[v]) {
            if(p.x!=par) {
                if(subtree_size[p.x] > heavySize) {
                    heavySize = subtree_size[p.x];
                    heavyChild = p.x;
                    heavyEdgeWeight = p.y;
                }
            }
        }
        if(heavyChild!=-1) {
            arr[pos] = heavyEdgeWeight;
            HLD(heavyChild, v);
        }
        for(Pair p : adj[v]) {
            if(p.x != par && p.x != heavyChild) {
                chainId++;
                chainHead[chainId] = p.x;
                arr[pos] = p.y;
                HLD(p.x, v);
            }
        }
    }

    /**
     * Returns the maximum in path from node from to node to. Node to should be a ancestor of from.
     * Uses the decomposition to reduce the number of queries to  at most log(n)
     * @param from
     * @param to
     * @return
     */
    static int queryUp(int from, int to) {
        int curr = from;
        int ans = 0;
        while(chain[curr] != chain[to]) {
            ans = max(ans, query(position[chainHead[chain[curr]]], position[curr]));
            curr = parent[chainHead[chain[curr]]][0];
        }
        ans = max(ans, query(position[to] + 1, position[curr]));
        return ans;
    }
    
    //calculates lca of node u and node v
    static int lca(int u, int v) {
        if(level[u]>level[v]) {
            int temp = u;
            u = v;
            v = temp;
        }
        int diff = level[v] - level[u];
        for(int i=MAX;i>=0;--i) {
            if((diff&(1<<i))!=0) {
                v = parent[v][i];
            }
        }
        if(u==v) {
            return u;
        }
        for(int i=MAX;i>=0;--i) {
            if(parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }
    
    //segment tree build
    static void build(int treein,int low,int high)
    {
        if(low==high)
            tree[treein] = arr[low];
        else
        {
            int mid = (low+high)>>1;
            build(2*treein,low,mid);
            build(2*treein+1,mid+1,high);
            tree[treein] = max(tree[2*treein],tree[2*treein+1]);
        }
    }
    //segment tree update
    static void update(int treein,int low,int high,int idx,int val)
    {
        if(low==high)
            tree[treein] = val;
        else
        {
            int mid = (low+high)>>1;
            if(idx<=mid)
                update(2*treein,low,mid,idx,val);
            else update(2*treein+1,mid+1,high,idx,val);
            tree[treein] = max(tree[2*treein],tree[2*treein+1]);
        }
    }
    //segment tree query
    static int query(int treein,int low,int high,int l,int r)
    {
        if(l<=low && high<=r)
            return tree[treein];
        if(low>r || high<l)
            return 0;
        int mid = (low+high)>>1;
        return max(query(2*treein,low,mid,l,r),query(2*treein+1,mid+1,high,l,r));
    }
    static int query(int l,int r)
    {
        if(l>r) {
            return 0;
        }
        return query(1,0,n-1,l,r);
    }
    static void update(int idx,int val)
    {
        update(1,0,n-1,idx,val);
    }
    static class Pair implements Comparable<Pair>
    {
        int x,y;
        Pair(int x,int y)
        {
            this.x=x;
            this.y=y;
        }
        public int compareTo(Pair other)
        {
            if(this.x!=other.x)
                return this.x-other.x;
            return this.y-other.y;
        }
        public String toString()
        {
            return "("+x+","+y+")";
        }
    }
}
/*
2

3
1 2 1
1 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE

3
1 2 1
1 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
 */