#define MAXNODE 5000000 ///Total number of nodes in the tree. Add all length of suffix.
#define ALPHABET_SIZE 27

struct NODE {
    int start, end, slink; ///Except for root - Each edge has a [start and end) corresponding to text[start,end)
	int child[ALPHABET_SIZE];
    
    ///Always use this to find length of edge
	int edgeLen () {
    		return min ( pos + 1, end ) - start;
	}
}t[2*MAXNODE]; ///*2 cause each internal node can have terminal node attached. Imagine "aaa...aa"
char text[MAXNODE];

struct SuffixTree {
    int root, last_added, pos, needSL, rem, act_node, act_e, act_len;
    ///Only need root from here. Others can be private.
    
    int newNode ( int start, int end = inf ) {
        NODE nd;
        nd.start = start;
        nd.end = end;
        nd.slink = 0;
        for ( int i = 0; i < ALPHABET_SIZE; i++ ) {
                nd.child[i] = 0;
        }
        t[++last_added] = nd;
        return last_added;
    }
    char actEdge() {
        return text[act_e];
    }

    void addSL ( int node ) {
        if ( needSL > 0 ) t[needSL].slink = node;
        needSL = node;
    }

    bool walkdown ( int node ){
        if ( act_len >= t[node].edgeLen() ) {
                act_e += t[node].edgeLen();
                act_len -= t[node].edgeLen();
                act_node = node;
                return true;
        }
        return false;
    }

    void st_init() {
        needSL = 0; last_added = 0; pos = -1;
        rem = 0; act_node = 0; act_e = 0; act_len = 0;
        root = act_node = newNode ( -1, -1 );
    }

    void st_extend( int c ) {
        text[++pos] = c;
        needSL = 0;
        rem++;

        while ( rem ) {
                if ( act_len == 0 ) act_e = pos;
                if ( t[act_node].child[actEdge()] == 0  ) {
                    int leaf = newNode ( pos );
                    t[act_node].child[actEdge()] = leaf;
                    addSL ( act_node );
                }
                else {
                    int nxt = t[act_node].child[actEdge()];
                    if ( walkdown ( nxt ) ) continue;
                    if ( text[t[nxt].start+act_len] == c ) {
                            act_len++;
                            addSL ( act_node );
                            break;
                    }
                    int split = newNode ( t[nxt].start, t[nxt].start + act_len );
                    t[act_node].child[actEdge()] = split;
                    int leaf = newNode ( pos );
                    t[split].child[c] = leaf;
                    t[nxt].start += act_len;
                    t[split].child[text[t[nxt].start]] = nxt;

                    addSL ( split );
                }
                rem--;
                if ( act_node == root && act_len > 0 ) {
                    act_len--;
                    act_e = pos - rem + 1;
                }
                else {
                    if ( t[act_node].slink > 0 ) act_node = t[act_node].slink;
                    else act_node = root;
                }
        }
    }
};


/*
1. How to insert?
    Take input in a string, then convert each charater to int and insert using st_extend( c ).
    At the end of the string, extend using st_extend($), where $ is an int > than others.

2. How to check for terminal node?
    if ( t[s].end == inf ) it is a terminal node.
*/
