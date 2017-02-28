//Returns char according to kind of solution
//Ax + By = C Run+ Rise-
//AX + (-B)y = C Run+ Rise+
//When changing X, steps are either d/run or (d+run-1)/run depending on crossing or not.
//When changing Y, steps are same as X, but take ABS(Rise) and assign sign to step.
//Always assign sign to steps and ADD values to x and y.


struct LinearDiphontine {
    vlong a, b, c, x, y, run, rise;
    char solution;

    char solve () {
        if ( a == 0 && b == 0 ) {
            if ( c == 0 ) {
                //Infinite solutions. Anything works
                return solution = 'i';
            }
            else return solution = '0'; //No solution
        }
        if ( a == 0 || b == 0 ) {
            //Vertical or Horizontal Line
            if ( !a ) {
                if ( c % b != 0 ) return solution = '0'; /// No Solution
                run = 1; rise = 0;
                return solution = 'h'; /// ( anything, c / b )
            }
            else {
                if ( c % a != 0 ) return solution = '0'; ///No Solution
                run = 0; rise = 1;
                return solution = 'v'; /// ( c / a , anything )
            }
        }
        
        vlong g = ext_gcd( a, b, &x, &y );
        if ( c % g != 0 ) {
            //No solution
            return solution = '0';
        }

        a /= g; b /= g; c /= g;

        ext_gcd ( a, b, &x, &y );
        x *= c; y *= c;

        ///run and rise calculation
        run = b; rise = -a;
        if ( run < 0 ) {
          run *= -1; rise *= -1;
        }
        
        return solution = '1';
    }
    
    ///Move solution near to vertical line x = p
    void moveNearVerticalLine( int p ) {
        if ( run == 0 ) return; /// Both are vertical
        vlong jump = ( p - x ) / run;
        x += jump * run;
        y += jump * rise;
        
        if ( x < p ) { ///Keep solution on right of the line
            x += run;
            y += rise;
        }
    }
    
    void moveNearHorizontalLine( int p ) {
        if ( rise == 0 ) return; /// Both are horizontal
        vlong jump = ( p - y ) / rise;
        x += jump * run;
        y += jump * rise;
        
        if ( y < p ) { ///Keep solution above the line
           if ( rise > 0 ) {
             x += run;
             y += rise;
           }
           else {
             x -= run;
             y -= rise;
           }
        }
    }
};
