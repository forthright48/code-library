#define BIOSIZE 0

struct BIONOMIAL {
    vlong n, k, val;

    void goDown() {
        vlong a = n + 1, b = n - k + 1; vlong g = gcd ( a, b ); a /= g; b /= g;
        val /= b; val *= a;
        n++;
    }
    void goRight() {
        if ( k + 1 > n ) {
            k = n + 1;
            val = 0;
            return;
        }
        vlong a = n - k, b = k + 1; vlong g = gcd ( a, b ); a /= g; b /= g;
        val /= b; val *= a;
        k++;
    }

    void assign ( vlong _n, vlong _k, vlong _val ) {
        n = _n; k = _k; val = _val;
    }

    void clear () {
        //CLR(memo,-1);
    }

    //Calculate NCK
    int memo[BIOSIZE][BIOSIZE];
    vlong nck ( int n, int k ) {
        if ( memo[n][k] != -1 ) return memo[n][k];
        if ( k == 0 ) return 1;
        if ( n == 0 ) return 0;

        memo[n][k] = nck ( n - 1, k ) + nck ( n - 1, k - 1 );
        return memo[n][k];
    }
};
