/*
Suffix array implementation using bucket sorting + lcp.
Complexity O(n log n), str[] is the target string,
nnn is its length and suffix[i] contains i'th sorted suffix position.
*/

/*
1. Fill str[] with string or augmented string.
2. Assign nnn length of str[].
3. Call SortSuffix()
4. Result is at two different arrays: suffix[i] contains index of i'th sorted string
   and sufRank[stp][i] contains rank of i'th suffix
*/

#define MAXN Maximum Length of str[]
#define MAXL Maximum Depth of log(MaxN)

int nnn, stp, mv, suffix[MAXN], tmp[MAXN];
int sum[MAXN], cnt[MAXN], sufRank[MAXL][MAXN];
char str[MAXN];

inline bool equal(const int &u, const int &v){
    if(!stp) return str[u] == str[v];
    if(sufRank[stp-1][u] != sufRank[stp-1][v]) return false;
    int a = u + mv < nnn ? sufRank[stp-1][u+mv] : -1;
    int b = v + mv < nnn ? sufRank[stp-1][v+mv] : -1;
    return a == b;
}

void update(){
    int i, rnk;
    for(i = 0; i < nnn; i++) sum[i] = 0;
    for(i = rnk = 0; i < nnn; i++) {
        suffix[i] = tmp[i];
        if(i && !equal(suffix[i], suffix[i-1])) {
            sufRank[stp][suffix[i]] = ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else sufRank[stp][suffix[i]] = rnk;
        sum[rnk+1]++;
    }
}

void Sort() {
    int i;
    for(i = 0; i < nnn; i++) cnt[i] = 0;
    memset(tmp, -1, sizeof tmp);
    for(i = 0; i < mv; i++){
        int idx = sufRank[stp - 1][nnn - i - 1];
        int x = sum[idx];
        tmp[x + cnt[idx]] = nnn - i - 1;
        cnt[idx]++;
    }
    for(i = 0; i < nnn; i++){
        int idx = suffix[i] - mv;
        if(idx < 0)continue;
        idx = sufRank[stp-1][idx];
        int x = sum[idx];
        tmp[x + cnt[idx]] = suffix[i] - mv;
        cnt[idx]++;
    }
    update();
    return;
}

inline bool cmp(const int &a, const int &b){
    if(str[a]!=str[b]) return str[a]<str[b];
    return false;
}

void SortSuffix() {
    int i;
    for(i = 0; i < nnn; i++) tmp[i] = i;
    sort(tmp, tmp + nnn, cmp);
    stp = 0;
    update();
    ++stp;
    for(mv = 1; mv < nnn; mv <<= 1) {
        Sort();
        stp++;
    }
    stp--;
    for(i = 0; i <= stp; i++) sufRank[i][nnn] = -1;
}

///Here u and v are unsorted suffix string positions
inline int lcp(int u, int v) {
    if(u == v) return nnn - u;
    int ret, i;
    for(ret = 0, i = stp; i >= 0; i--) {
        if(sufRank[i][u] == sufRank[i][v]) {
            ret += 1<<i;
            u += 1<<i;
            v += 1<<i;
        }
    }
    return ret;
}
