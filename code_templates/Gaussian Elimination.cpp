/*
1. Set row and col of mat
2. Call rank() to perform gauss-elimination and find rank
3. Call isValid() to find if solution exists.

Careful about int a[x][x]. If mod^2 crosses int, take vlong
If mod is 2, it is better to use XOR since it a lot faster.
*/
struct GAUSS {
    int row, col;
    vlong a[x][x];
    int mod;
	bool valid;
	GAUSS() {
        mod = xyz;
	}
    void clear () {
        memset ( a, 0, sizeof a );
    }
	void isValid ( int st ) {
		int i;
        valid = true;
		for ( i = st; i < row; i++ ) {
    	    if ( a[i][col-1] ) {
                valid = false;
                return;
    	    }
		}
	}
    ///Return Rank of Matrix
    ///Free variable = Variable - Rank or Col - Rank - 1
    int rank(){
        int i = 0, j = 0, k, r, u;
    	while(i < row && j < col - 1){
    		r = i;
    		for(k = i; k < row; k++)
                if(a[k][j]){
                    r = k; ///Find non-zero coefficient
                    break;
                }
    		if(a[r][j]){
    			if(r != i) ///Swap row if required
    				for(k = 0; k < col; k++)
    					swap(a[r][k], a[i][k]);

               ///Neutralize if required. Depends on whether double or modular division
                vlong v = a[i][j];
                v = modInv ( v, mod );
                for ( u = j; u < col; u++ ) {
                    a[i][u] = ( a[i][u] * v ) % mod;
                }
                /*
                double v = a[i][j];
                for ( u = j; u < col; u++ ) {
                    a[i][u] /= v;
                }
                */

    			for(u = i + 1; u < row; u++)
    				if(a[u][j]) { ///Eliminate
                        int v = a[u][j];
    					for(k = j; k < col; k++) {
    						a[u][k] = ( ( a[i][k] * v ) - a[u][k] ) % mod; ///Change here if no mod
                            if ( a[u][k] < 0 ) a[u][k] += mod;
    					}
    				}
    			i++;
    		}
    		j++;
    	}
    	return i;
    }

    void print() {
        FOR(i,0,row-1){
            FOR(j,0, col-1){
                printf ( "%d ", a[i][j] );
            }
            nl;
        }
    }
}mat;
