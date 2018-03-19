/**
    1. First clear the hld class: hld.clear(n, root)
    2. Call hld.decompose() to create the chains and other preprocessing
    3. Call hld.getPath(a, b) to get vector<pair<int,int>> segments of path
    4. Call hld.getLCA(a, b) to get their lca
*/

class HLD {
    private:
    const static int NODE = 10010;

    vector<int> adj[NODE];
    int root, node;

    int par[NODE], level[NODE];

    void dfs (int u, int p) {
        par[u] = p; /// Set parent of u
        child[u] = 1;
        if (p == -1) level[u] = 0;
        else level[u] = level[p] + 1;

        for ( int i = 0; i < adj[u].size(); i++ ) {
            int v = adj[u][i];
            if ( v == p ) continue; /// Don't go back to parent
            dfs(v, u);
            child[u] += child[v];
        }
    }

    int chainLeader, arrayPos;
    int leader[NODE];
    void hld (int u, int newChain) {
        if (newChain) {
            chainLeader = u;
        }
        leader[u] = chainLeader;
        linearPos[u] = arrayPos++;
        linearTree.push_back(u);

        int bigChild = -1, subTreeSize = -1;
        for ( int i = 0; i < adj[u].size(); i++ ) {
            int v = adj[u][i];
            if ( v == par[u] ) continue;
            if ( child[v] > subTreeSize ) {
                subTreeSize = child[v];
                bigChild = v;
            }
        }

        if ( bigChild != -1 ) {
            hld(bigChild, 0);
        }

        for ( int i = 0; i < adj[u].size(); i++ ) {
            int v = adj[u][i];
            if ( v == par[u] ) continue;
            if ( v == bigChild ) continue;
            hld(v, 1);
        }
    }

    public:
    vector<int> linearTree;
    int child[NODE], linearPos[NODE];

    HLD() {}

    void clear( int _node, int _root) {
        node = _node;
        root = _root;
        arrayPos = 0;

        for ( int i = 0; i <= node; i++ ) {
            adj[i].clear();
        }

        linearTree.clear();
    }

    void addUndirectedEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void decompose() {
        dfs(root, -1);
        hld(root, 1);
    }

    vector<pair<int, int>> getPath ( int a, int b ) {
        vector<pair<int,int>> pathSegments;

        if ( level[a] < level[b] ) swap(a, b);

        while ( 1 ) {
            int lead = leader[a];

            if (level[lead] > level[b]) {
                /// Jump to lead
                pathSegments.push_back({linearPos[lead], linearPos[a]});
                a = par[lead];
            } else {
                /// On same chain
                pathSegments.push_back({linearPos[b], linearPos[a]});
                break;
            }
        }

        return pathSegments;
    }

    int getLCA ( int a, int b ) {
        while (leader[a] != leader[b]) {
            if (level[leader[a]] < level[leader[b]])
                b = par[leader[b]];
            else
                a = par[leader[a]];
        }
        if (level[a] < level[b]) {
            return a;
        }
        return b;
    }
}hld;
