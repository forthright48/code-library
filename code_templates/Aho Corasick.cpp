/// Aho Corasick
/// !!! Works with lowercase letters !!!
/// !!! If RTE, bring struct node outside !!!

class AhoCorasick {
    #define SIZE asdf
    struct node {
        int val;
        int child[26];
        void clear() {
            memset(child,0,sizeof child);
        }
    }trie[SIZE];

    int curNode, root, fail[SIZE], par[SIZE];

public:
    void clear() {
        root = 0;
        curNode = 0;
        trie[root].clear();
    }

    void addTrie ( string s ) {
        int len = s.size();

        int cur = root;
        for ( int i = 0; i < len; i++ ) {
            char c = s[i] - 'a';
            if ( trie[cur].child[c] == 0 ) {
                curNode++;
                trie[curNode].clear();
                trie[curNode].val = c;
                trie[cur].child[c] = curNode;
            }
            cur = trie[cur].child[c];
        }

        ///Mark the node cur as finishing point, if needed
    }

    void calcFail() {
        queue<int> q;
        q.push ( 0 );

        while ( !q.empty() ) {
            int s = q.front(); q.pop();

            ///Push all child to queue
            for ( int i = 0; i < 26; i++ ) {
                int t = trie[s].child[i];
                if ( t != 0 ) {
                    q.push ( t );
                    par[t] = s;
                }
            }

            ///Calculate failure of current node s
            if ( s == 0 ) { ///Special case
                fail[s] = 0;
                par[s] = 0;
                continue;
            }

            int p = par[s];
            int f = fail[p];
            int v = trie[s].val;

            while ( f != 0 && trie[f].child[v] == 0 ) f = fail[f]; ///Keep on jumping until found

            fail[s] = trie[f].child[v];
            if ( fail[s] == s ) fail[s] = 0; ///Can't be fail of itself
        }
    }

    int goTo ( int state, int c ) {
        if ( trie[state].child[c] != 0 ) {
            return trie[state].child[c];
        }

        ///Fall back
        int f = fail[state];
        while ( f != 0 && trie[f].child[c] == 0 ) {
            f = fail[f];
        }

        return trie[f].child[c];
    }

}aho;

