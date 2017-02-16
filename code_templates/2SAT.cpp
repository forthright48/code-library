#define SCCNODE adf
struct SCC{
    int num[SCCNODE], low[SCCNODE], col[SCCNODE], cycle[SCCNODE], st[SCCNODE];
    int tail, cnt, cc;
    vi adj[SCCNODE];

    SCC():tail(0),cnt(0),cc(0) {}
    void clear ( int n ) {
        cc += 3;
        FOR(i,0,n) adj[i].clear();
        tail = 0;
    }
    void tarjan ( int s ) {
        num[s] = low[s] = cnt++;
        col[s] = cc + 1;
        st[tail++] = s;
        FOR(i,0,SZ(adj[s])-1) {
            int t = adj[s][i];
            if ( col[t] <= cc ) {
                tarjan ( t );
                low[s]=min(low[s],low[t]);
            }
            /*Back edge*/
            else if (col[t]==cc+1)
                low[s]=min(low[s],low[t]);
        }
        if ( low[s] == num[s] ) {
            while ( 1 ) {
                int temp=st[tail-1];
                tail--;
                col[temp] = cc + 2;
                cycle[temp] = s;
                if ( s == temp ) break;
            }
        }
    }
    void shrink( int n ) {
        FOR(i,0,n){
            FOR(j,0,SZ(adj[i])-1){
                adj[i][j] = cycle[adj[i][j]]; ///Careful. This will create self-loop
            }
        }
        FOR(i,0,n){
            if ( cycle[i] == i ) continue;
            int u = cycle[i];
            FOR(j,0,SZ(adj[i])-1){
                int v = adj[i][j];
                adj[u].pb ( v );
            }
            adj[i].clear();
        }
        FOR(i,0,n){ ///Not always necessary
            sort ( ALL(adj[i]) );
            UNIQUE(adj[i]);
        }
    }
    void findSCC( int n ) {
        FOR(i,0,n) {
            if ( col[i] <= cc ) {
                tarjan ( i );
            }
        }
    }
};

/*
1. The nodes need to be split. So change convert() accordingly.
2. Using clauses, populate scc edges.
3. Call possible, to find if a valid solution is possible or not.
4. Dont forget to keep space for !A variables
*/
struct SAT2 {
    SCC scc;

    SAT2(): bfscc(1) {}

    void clear( int n ) {
        scc.clear( int n );
    }

    int convert ( int n ) { ///Change here. Depends on how input is provided
        int x = ABS(n);
        x--;
        x *= 2;
        if ( n < 0 ) x ^= 1;
        return x;
    }

    void mustTrue ( int a ) { ///A is True
        scc.adj[a^1].pb ( a );
    }
    void orClause ( int a, int b ) { /// A || B clause
        //!a->b !b->a
        scc.adj[a^1].pb ( b );
        scc.adj[b^1].pb ( a );
    }
    /// Out of all possible option, only one is true
    void atMostOneClause ( int a[], int n, int flag ) {
        if ( flag == 0 ) { /// At most one can be false
            FOR(i,0,n){
                a[i] = a[i] ^ 1;
            }
        }
        FOR(i,0,n) {
            FOR(j,i+1,n) {
                orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
            }
        }
    }

    ///Send n, total number of nodes, after expansion
    bool possible( int n ) {
        scc.findSCC( n );

        FOR(i,0,n) {
            int a = i, b = i^1;
            ///Falls on same cycle a and !a.
            if ( scc.cycle[a] == scc.cycle[b] ) return false;
        }

        ///Valid solution exists
        return true;
    }

    ///To determine if A can be true. It cannot be true, if a path exists from A to !A.
    int vis[SAT2NODE], qqq[SAT2NODE], bfscc;
    void bfs( int s ) {
        bfscc++;
        int qs = 0, qt = 0;
        vis[s] = bfscc;
        qqq[qt++] = s;
        while ( qs < qt ) {
            s = qqq[qs++];
            FOR(i,0,SZ(scc.adj[s])-1) {
                int t = scc.adj[s][i];
                if ( vis[t] != bfscc ) {
                    vis[t] = bfscc;
                    qqq[qt++] = t;
                }
            }
        }
    }

}sat2;
