struct node {
    int x, y, next, cap, cost;
};

/*
1. Clear graph
2. Add edge
3. Assign source and sink
4. Pass highestNumberOfNode to maxFlow() or minCostMaxFlow()
*/
struct FLOW {
    int source, sink;

    int head[NODE];
    void clear() {
        e = 0;
        CLR(head,-1);
    }

    node edge[EDGE]; int e;
    void addEdge ( int u, int v, int cap, int cap2, int cost ) {
        edge[e].x = u; edge[e].y = v; edge[e].cap = cap; edge[e].cost = cost;
        edge[e].next = head[u]; head[u] = e; e++;
        edge[e].x = v; edge[e].y = u; edge[e].cap = cap2; edge[e].cost = -cost;
        edge[e].next = head[v]; head[v] = e; e++;
    }

    int vis[NODE], q[NODE], now[NODE];
    bool bfs ( ) {
        memset ( vis, -1, sizeof vis );
        vis[source] = 0;
        int ini = 0, qend = 0;
        q[qend++] = source;

        while ( ini < qend && vis[sink] == -1 ) {
            int s = q[ini++];
            int i;
            for (i=head[s];i!=-1;i= edge[i].next){
                int t = edge[i].y;
                if ( vis[t] == -1 && edge[i].cap){
                    vis[t] = vis[s] + 1;
                    q[qend++] = t;
                }
            }
        }
        if ( vis[sink] != -1 ) return true;
        else return false;
    }
    int dfs ( int s, int f ) {
        if ( f == 0 ) return 0;
        if ( s == sink ) return f;
        for ( int &i=now[s];i!=-1;i=edge[i].next){
            int t = edge[i].y;
            if ( vis[s] + 1 != vis[t] ) continue;
            int pushed=dfs(t,MIN(f,edge[i].cap));
            if ( pushed ) {
                edge[i].cap -= pushed;
                edge[i^1].cap += pushed;
                return pushed;
            }
        }
        return 0;
    }

    int maxFlow ( int highestNumberOfNode, int flow ) {
        int res = 0;
        while ( 1 ) {
            if ( flow == 0 ) break;
            if ( bfs () == false ) break;
            int i;
            for ( i=0;i<=highestNumberOfNode;i++)now[i]= head[i];
            while (int pushed=dfs(source,flow ) ) {
                res += pushed; ///Can overflow depending on Max Flow
                flow -= pushed;
            }
        }
        return res;
    }

    int inq[NODE], par[NODE], record[NODE];
    int minCostFlow ( int highestNumberOfNode ) {
        int res = 0, i, j, k, fl = 0;
        while ( 1 ) {
            for ( i = 0; i <= highestNumberOfNode; i++ ) vis[i] = inf;
            vis[source] = 0;
            deque < int > dq;
            dq.pb ( source );
            while ( !dq.empty() ) {
                int s = dq.front(); dq.pop_front();
                inq[s] = 0;
                for ( i = head[s]; i != -1; i = edge[i].next ) {
                    int t = edge[i].y;
                    if ( edge[i].cap ) {
                        if ( vis[s] + edge[i].cost < vis[t] ) {
                            vis[t] = vis[s] + edge[i].cost;
                            par[t] = s;
                            record[t] = i;
                            if ( inq[t] == 0 ) {
                                inq[t] = 1;
                                if ( dq.empty() == false && vis[dq.front()] > vis[t] )
                                    dq.push_front( t );
                                else dq.pb ( t );
                            }
                        }
                    }
                }
            }

            //if ( vis[sink] > 0 ) break; ///Cost Getting minimized, Change Here
            if ( vis[sink] == inf ) break; //Flow getting maximized. Either this, or the one above

            fl++; ///Total flow
            res += vis[sink]; ///Cost of Flow
            for ( i = sink; i != source; i = par[i] ) { //Travel from sink to source
                int t = record[i]; //Record which edge was used to travel to t
                edge[t].cap--;
                edge[t^1].cap++;
            }
        }

        return res; ///Min cost of max flow
    }

}graph;

//Kuhn's algo has been moved to kuhn.cpp
