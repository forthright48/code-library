class Fraction {
    vlong num, denom;

    void simplify() {
        vlong g = gcd ( num, denom );
        num /= g;
        denom /= g;
        if ( denom < 0 ) {
            num *= -1;
            denom *= -1;
        }
    }

public:

    ///First deal with initiation of the class
    Fraction () {
        num = 0;
        denom = 1;
    }
    Fraction ( vlong a, vlong b ) {
        num = a;
        denom = b;
        simplify();
    }
    Fraction ( vlong x ) {
        num = x;
        denom = 1;
    }
    Fraction ( pll x ) {
        num = x.ff;
        denom = x.ss;
        simplify();
    }
    Fraction ( const Fraction &b ) {
        num = b.num;
        denom = b.denom;
    }
    void operator = ( vlong x ) {
        num = x;
        denom = 1;
    }
    void operator = ( pll x ) {
        num = x.ff;
        denom = x.ss;
        simplify();
    }
    void operator = ( Fraction b ) {
        num = b.num;
        denom = b.denom;
    }

    ///Basic Arithmetic operations
    Fraction operator - () { ///Negation
        return Fraction( -num, denom );
    }
    Fraction operator + ( Fraction b ) { ///Addition
        Fraction res;
        res.denom = abs( LCM(denom,b.denom) );
        res.num = (res.denom/denom)*num + (res.denom/b.denom)*b.num;
        res.simplify();
        return res;
    }
    Fraction operator - ( Fraction b ) { ///Subtraction
        return (*this) + (-b);
    }
    Fraction operator * ( Fraction b ) {
        Fraction res ( b.num / gcd(b.num,denom), b.denom / gcd(b.denom,num) );
        res.num *= num / gcd(num,b.denom);
        res.denom *= denom / gcd(denom,b.num);
        res.simplify();
        return res;
    }
    Fraction operator / ( Fraction b ) { ///Division
        Fraction rev ( b.denom, b.num );
        if ( rev.denom < 0 ) {
            rev.denom *= -1;
            rev.num *= -1;
        }
        return (*this)*rev;
    }

    ///Basic Arithmetic Operations overloaded
    void operator += ( Fraction b ) {
        *this = *this + b;
    }
    void operator -= ( Fraction b ) {
        *this = *this - b;
    }
    void operator *= ( Fraction b ) {
        *this = *this * b;
    }
    void operator /= ( Fraction b ) {
        *this = *this / b;
    }

    ///Comparison
    bool operator == ( Fraction b ) {
        if ( num == b.num && denom == b.denom ) return true;
        else return false;
    }
    bool operator < ( Fraction b ) {
        if ( num * b.denom < b.num * denom ) return true;
        else return false;
    }
    bool operator > ( Fraction b ) {
        return ( b < *this );
    }
    bool operator <= ( Fraction b ) {
        if ( *this == b || *this < b ) return true;
        else return false;
    }
    bool operator >= ( Fraction b ) {
        return ( b <= *this );
    }

    ///Output
    void print() {
        printf ( "%lld/%lld %lf\n",num, denom, num/(denom-0.0) );
    }

    Fraction getAbs() {
      return Fraction(abs(num),denom);
    }
};