/*
Make sure BIT is 1-indexed
1. Properly change update and read
2. Call clear() and set row and col
*/
struct BIT {
    int arr2D[XXX][XXX], arr[XXX];
    int row, col;

    void clear( int r, int c ){
        row = r;
        col = c;
        CLR(arr,0);
    }

    ///If I need sum[1-x], I will update from [x-n]. Opposite for reverse.
    void update ( int x, int val ) {
        for ( int i = x; i <= col; i += i & -i ) arr[i] += val;
    }
    int read ( int x ) {
        int res = 0;
        for ( int i = x; i > 0; i -= i & -i ) res += arr[i];
    }

    ///If I need sum[1-x], I will update from [x-n]. Opposite for reverse.
    void update2D ( int x, int y, int val ) {
        for ( int i = x; i > 0; i -= i & -i ) { ///Change Here. Both increment and loop condition
            for ( int j = y; j <= col; j += j & -j ) { ///And here
                arr[i][j] += val;
            }
        }
    }

    ///Just reverse direction of update
    int read2D ( int x, int y ) {
        int res = 0;
        for ( int i = x; i <= row; i += i & -i ) { ///Change Here. Both increment and loop condition
            for ( int j = y; j > 0; j -= j & -j ) { ///And here
                res += arr[i][j];
            }
        }
        return res;
    }
}bit;
