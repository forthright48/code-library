/**
    Dependencies:
        1. MillerRabin

    How to Use it?
        1. Call pollardRho.clear();
        2. Call pollardRho.getPrimeFactorization(n);

    See sample main() function below
*/

class PollardRho {
    private:

    MillerRabin millerRabin;

    int prime[50000], status[50000], primeSize;
    void sieve() {
        primeSize = 0;
        memset( status, 0, sizeof status );

        status[0] = status[1] = 1;
        int n = 46340;
        for ( int i = 4; i <= n; i += 2 ) status[i] = 1;

        int sqrtn = sqrt(n);
        for ( int i = 3; i <= sqrtn; i += 2 ){
            for ( int j = i*i; j <= n; j += 2 * i ) {
                status[j] = 1;
            }
        }

        prime[primeSize++] = 2;
        for ( int i = 3; i <= n; i += 2 ) {
            if ( status[i] == 0 ) {
                prime[primeSize++] = i;
            }
        }
    }

    void factorizeWithSieve(int n) {
        int sqrtn = sqrt(n);
        for ( int i = 0; i < primeSize && prime[i] <= sqrtn; i++ ) {
            if ( n % prime[i] == 0 ) {
                while ( n % prime[i] == 0 ) {
                    factors.push_back(prime[i]);
                    n /= prime[i];
                }
                sqrtn = sqrt(n);
            }
        }
        if ( n != 1 ) {
            factors.push_back(n);
        }
    }

    vlong pollard_rho( vlong n, vlong c ) {
        vlong y = 2, i = 1, k = 2, d;
        __int128 x = 2;
        while (true) {
            x = x * x % n + c;
            if (x >= n)	x -= n;
            d = __gcd((vlong)x - y, n);
            if (d > 1) return d;
            if (++i == k) {
                y = x, k <<= 1;
            }
        }
        return n;
    }

    void factorize(vlong n) {
        if (n == 1)
            return ;
        if (n < 1e+9) {
            factorizeWithSieve(n);
            return ;
        }
        if (millerRabin.isPrime(n)) {
            factors.push_back(n);
            return ;
        }
        vlong d = n;
        for (int i = 2; d == n; i++) {
            d = pollard_rho(n, i);
        }
        factorize(d);
        factorize(n/d);
    }

    public:

    vector<vlong> factors;

    PollardRho() {
        sieve();
    }

    void clear() {
        factors.clear();
    }

    vector<pair<vlong,int>> getPrimeFactorization(vlong n) {
        factorize(n);
        sort(factors.begin(), factors.end());

        vector<pair<vlong,int>> res;
        for( int i = 0; i < factors.size(); i++ ) {
            vlong p = factors[i];
            int cnt = 1;
            while ( i + 1 < factors.size() && factors[i+1] == p) {
                i++;
                cnt++;
            }
            res.push_back({p,cnt});
        }

        return res;
    }
}pollardRho;

/***************************/

int main() {
    int n = 1e16+8;

    pollardRho.clear(); /// Don't forget to clear. Important for multi case.
    prime<pair<vlong,int>> factors = pollardRho.getPrimeFactorization(n);
    for ( int i = 0; i < factors.size(); i++ ) {
        int p = factors[i].first;
        int a = factors[i].second;

        /// p^a is factor of n
        /// Do your work here
    }
}
