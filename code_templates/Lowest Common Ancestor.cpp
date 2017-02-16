/*
1. Set N and root using setNM(). Here N is the largest index of node. No need to worry about 0/1 based indexing
2. Add Edges using addEdge
3. Call precal()
4. Ready to query findLCA(u,v)
*/
struct LCA{
    private:
    int tab[LCANODE][LCADEPTH], par[LCANODE], lev[LCANODE], vis[LCANODE], q[LCANODE], cc, N, M, root;
    vi adj[LCANODE];

    void bfs ( int s ) {
        vis[s] = cc; lev[s] = 0; par[s] = -1; ///Set par[root] = -1

        int qh = 0, qt = 0, t;
        q[qt++] = s;
        while ( qh < qt ) {
            s = q[qh++];
            FOR(i,0,SZ(adj[s])-1){
                t = adj[s][i];
                if ( vis[t] != cc ) {
                    par[t] = s;
                    vis[t] = cc;
                    lev[t] = lev[s] + 1;
                    q[qt++] = t;
                }
            }
        }
    }

    void calculate (){
        int i,j,p;
        for (i=0;i<=N;i++){
           tab[i][0]=par[i];
        }

        for(i=1;i<=M;i++){
            for(j=0;j<=N;j++){
                p=tab[j][i-1];
                if(p==-1) tab[j][i]=-1;
                else tab[j][i]=tab[p][i-1];
            }
        }
    }
    void clear () {
        cc++;
        FOR(i,0,N) adj[i].clear();
    }

    public:
    LCA() {
        cc = 1;
    }

    void setVar ( int n, int r ) {
        N = n;
        M = 0; ///Dynamically Set Depth
        int temp = n+1; ///Cause of 0 based index
        while ( temp ) {
            M++;
            temp /= 2;
        }
        root = r;
        clear();
    }

    void addEdge ( int u, int v ) {
        adj[u].pb ( v );
    }
    void precal () {
        bfs ( root ); ///Does not handle forest. Run a loop for that.
        calculate();
    }
    int findLCA(int s,int t){
        int dif,pos,i;
        if(lev[s]!=lev[t] ) {
            if(lev[s]>lev[t]) swap( s, t );
            dif=lev[t]-lev[s];
            while(dif){
                pos=RIGHTMOST(dif);
                t=tab[t][pos];
                dif-=1<<pos;
            }
        }
        if (s==t)return s;
        for(i=M;i>=0;i--){
            if(tab[s][i]!=tab[t][i]){
                s=tab[s][i];
                t=tab[t][i];
            }
        }
        return tab[s][0];
    }
};
