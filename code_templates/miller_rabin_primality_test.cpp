/**
    1. Works for n <= 2^64
    2. Uses at most 7 witnesses.
    3. Complexity: O( k log^3 n ), where k = 7

    Complexity should be reduced by log(n) factor since I used __int128 instead of mul_mod(),
    but lets just consider it

    How to use it?
    You just call the only public method of the class, isPrime(n) and get boolean result.
*/

typedef long long vlong;

class MillerRabin {
    private:

    /** https://miller-rabin.appspot.com/ confirms that the following base covers 2^64**/
    vlong prime[7] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    int psize = 7;

    vlong bigmod ( __int128 a, __int128 p, vlong mod ) {
        __int128 x = a % mod, res = 1;
        while ( p ) {
            if ( p & 1 ) res = res * x % mod;
            x = x * x % mod;
            p >>= 1;
        }
        return res;
    }

    ///Witness to compositeness of n
    ///n - 1 = 2^s * d, where d is odd
    bool witness ( vlong a, vlong d, vlong s, vlong n ) {
        __int128 r = bigmod( a, d, n );
        if ( r == 1 || r == n - 1 ) return false;
        int i;
        for ( i = 0; i < s - 1; i++ ) {
            r = r * r % n;
            if ( r == 1 ) return true;
            if ( r == n - 1 ) return false;
        }
        return true;
    }

    public:
    bool isPrime ( vlong n ) {
        if ( n <= 1 ) return false;

        vlong p = n - 1, s = 0;
        while ( ! ( p & 1 ) ) {
            p /= 2;
            s++;
        }
        vlong d = p;
        p = n - 1;

        for ( int i = 0; i < psize && prime[i] < n; i++ ) {
            if ( witness ( prime[i], d, s, n ) ) return false;
        }
        return true;
    }
} millerRabin;
