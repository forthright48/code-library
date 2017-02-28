#define ARTNODE 10010

class ArticulationPoint {
    int disc[ARTNODE]; ///Discovery time of nodes
    int low[ARTNODE]; ///Lowest back edge extension
    int col[ARTNODE]; ///Color for marking node

    int cnt; ///Timer
    int cc; ///Color
    int root; ///Root of tree

    void tarjan ( int s, int p ) {
        disc[s] = low[s] = cnt++;
        col[s] = cc + 1;

        int child = 0; ///Needed for root only
        int art = 0;

        for ( int i = 0; i < adj[s].size(); ++i ) {

            int t = adj[s][i];
            if ( t == p ) continue; ///Don't go to parent

            if ( col[t] <= cc ) { ///New node. Discovery.
                child++;

                tarjan ( t, s );
                low[s]=min(low[s],low[t]); ///Update back edge extension for S

                if ( low[t] >= disc[s] ) { ///Back edge of T did not go above S
                    art++; ///S is articulation point for T
                }
            }
            else if ( col[t] == cc + 1 ) { ///Back Edge
                low[s]=min(low[s],disc[t]);
            }
        }

        if ( ( s == root && child > 1 ) || ( s != root && art ) ) {
            ///Edit in this block
            printf ( "This is a articulation point: %d\n", s );
        }
    }

public:

    vector<int> adj[ARTNODE];

    void clear ( int n ) {
        cc += 2; ///cc is now 0. cc+1 is 1
        for (int i = 0; i <= n; i++ ) {
            adj[i].clear();
        }
    }

    void findArt( int n, int start = 0 ) {
        for ( int i = start; i <= n; i++ ) {
            if ( col[i] <= cc ) {
                root = i;
                tarjan ( i, -1 );
            }
        }
    }
}art;