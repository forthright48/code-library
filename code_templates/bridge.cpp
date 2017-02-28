#define BRIDGENODE 10010

class BridgeFinding {
    int disc[BRIDGENODE]; ///Discovery time of nodes
    int low[BRIDGENODE]; ///Lowest back edge extension
    int col[BRIDGENODE]; ///Color for marking node

    int cnt; ///Timer
    int cc; ///Color

    void tarjan ( int s, int parentEdge ) {
        disc[s] = low[s] = cnt++;
        col[s] = cc + 1;

        for ( int i = 0; i < adj[s].size(); ++i ) {

            int t = adj[s][i].ff;
            int edgeNumber = adj[s][i].ss;
            if ( edgeNumber == parentEdge ) continue; ///Don't use the same edge from parent

            if ( col[t] <= cc ) { ///New node. Discovery.

                tarjan ( t, edgeNumber );
                low[s]=min(low[s],low[t]); ///Update back edge extension for S

                if ( low[t] > disc[s] ) { ///Back edge of T did not go above S
                    ///This edge is Bridge
                }
            }
            else if ( col[t] == cc + 1 ) { ///Back Edge
                low[s]=min(low[s],disc[t]);
            }
        }
    }

public:

    vector< pair<int,int> > adj[BRIDGENODE]; ///Enter target and edge number as pair

    void clear ( int n ) {
        cc += 2; ///cc is now 0. cc+1 is 1
        for (int i = 0; i <= n; i++ ) {
            adj[i].clear();
        }
    }

    void findBridge( int n, int start = 0 ) {
        for ( int i = start; i <= n; i++ ) {
            if ( col[i] <= cc ) {
                tarjan ( i, -1 );
            }
        }
    }
}bridge;