struct CALENDAR {
    int month[13];
    int d, m, y, daysInYear;
    int day;

    CALENDER () {
        month[1] = 31; month[2] = 28; month[3] = 31;
        month[4] = 30; month[5] = 31; month[6] = 30;
        month[7] = 31; month[8] = 31; month[9] = 30;
        month[10] = 31; month[11] = 30; month[12] = 31;
        daysInYear = 365;
    }

    void assign ( int a, int b, int c, int _day = 0 ) {
        d = a;
        m = b;
        y = c;
        day = _day;
        updateFeb();
    }

    bool isLeapYear ( int n ) {
        if ( n % 400 == 0 || ( n % 4 == 0 && n % 100 != 0 ) ) return true;
        else return false;
    }

    //Call this whenever year changes
    void updateFeb () {
        if ( isLeapYear( y ) ) {
            month[2] = 29;
            daysInYear = 366;
        }
        else {
            month[2] = 28;
            daysInYear = 365;
        }
    }

    bool operator < ( const CALENDER &b ) const {
        if ( y < b.y ) return true;
        else if ( y == b.y && m < b.m ) return true;
        else if ( y == b.y && m == b.m && d < b.d ) return true;
        else return false;
    }

    //Increase 1 day
    void increment () {
        d++;
        day = ( day + 1 ) % 7;
        
        if ( d > month[m] ) {
            d = 1;
            m++;
            if ( m > 12 ) {
                m = 1;
                y++;
                updateFeb();
            }
        }
    }
    
    //Number of days between 1/1/a to 31/12/b inclusive
    int daysBetweenYear ( int a, int b ) {
        int p = b - a + 1;
        int res = p * 365;
        //Add 1 day for each leap year between [a,b].

        //Leap year between [0,b] - [0,a-1]
        int leap = b / 4 - b / 100 + b / 400;
        if ( a ) {
            a--;
            leap -= a / 4 - a / 100 + a / 400;
        }

        return res + leap;
    }

    //Return number of days between two dates. Go from b to *this.
    int diff ( CALENDER b ) {
        if ( y == b.y && m == b.m && d == b.d ) return 0;
        if ( *this < b ) return b.diff( *this );

        int res = 0;
        //The year is not same yet
        if ( b.y < y ) {
            //So we can move to next year, one day at a time.
            while ( b.d != 1 || b.m != 1 ) { 
                b.increment();
                res++;
            }
            res += daysBetweenYear( b.y, y - 1 );
            b.y = y;
            b.updateFeb();
        }

        //Same year
        while ( b.d != d || b.m != m ) {
            b.increment();
            res++;
        }

        return res;
    }

    //Add n days to current date
    CALENDER add ( int n ) {
        CALENDER res = *this;

        if ( n < 800 ) {
            while ( n ) {
                res.increment();
                n--;
            }
            return res;
        }

        while ( res.d != 1 || res.m != 1 ) {
            n--;
            res.increment();
        }

        while ( n > 366 ) {
            int jump = n / 366;
            if ( jump ) {
                int jd = daysBetweenYear( res.y, res.y + jump - 1 );
                n -= jd;
                res.day = ( res.day + jd ) % 7;
                res.y = res.y + jump;
                res.updateFeb();
            }
        }

        while ( n ) {
            res.increment();
            n--;
        }

        return res;
    }
};