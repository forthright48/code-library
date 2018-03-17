//WARNING: Arrays are 1-based index.

const int LENGTH = XYZ;
char text[LENGTH], pat[LENGTH];
int pre[LENGTH];

void compute () {
    int plen = strlen ( pat + 1 ), k = 0;
    pre[1] = 0;
    for ( int i = 2; i <= plen; i++ ) {
        while ( k && pat[k+1] != pat[i] ) k = pre[k];
        if ( pat[k+1] == pat[i] ) k++;
        pre[i] = k;
    }
}
int match () {
    int tlen = strlen ( text + 1 ), plen = strlen ( pat + 1 );
    int q = 0, res = 0;
    for ( int i = 1; i <= tlen; i++ ) {
        while ( q && pat[q+1] != text[i] ) q = pre[q];

        if ( pat[q+1] == text[i] ) q++;
        if ( q == plen ) {
            res++;
            q = pre[q];
        }
    }
    return res;
}

/// Application
/// Period of a string. N - pre[N] is the length of period iff period length divides N.
