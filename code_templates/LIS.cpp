/*
Finds only LIS. LDS can be found by simply multiplying the whole input array with -1.
For Longest Non-Decreasing sequence, simply use upper_bound().
Complexity: NlogK
*/
struct LIS {
    int bbb[NSIZE+10];

    int calculateLIS ( int arr[], int lisVal[], int n ) {
        FOR(i,0,n) {
            bbb[i] = inf;
        }
        bbb[0] = -inf;

        int mx = 0;
        FOR(i,0,n-1) {
            int v = arr[i];
            int pos = lower_bound ( bbb, bbb + mx + 1, v ) - bbb;
            lisVal[i] = pos;
            bbb[pos] = v;
            mx = MAX(mx,pos);
        }

        return mx;
    }
}lis;
