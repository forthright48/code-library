//The dice is sitting on its bottom and I can see the front.
struct DICE {
    int bottom = 0, top = 1, front = 2, right = 3, back = 4, left = 5; //Names of Faces
    int face[6]; //Value of faces

    void assign ( int _bot, int _top, int _front, int _right, int _back, int _left ) {
        face[0] = _bot; face[1] = _top; face[2] = _front; face[3] = _right; face[4] = _back; face[5] = _left;
    }

    //All rotation anti-clockwise
    DICE rotateZ() {
        DICE res;
        res.assign ( face[0], face[1], face[5], face[2], face[3], face[4] );
        return res;
    }
    DICE rotateX() {
        DICE res;
        res.assign ( face[back], face[front], face[bottom], face[right], face[top], face[left] );
        return res;
    }
    DICE rotateY() {
        DICE res;
        res.assign ( face[left], face[right], face[front], face[bottom], face[back], face[top] );
        return res;
    }

    //Comparer
    bool operator == ( const DICE &b ) const {
        FOR(i,0,5) {
            if ( face[i] != b.face[i] ) return false;
        }
        return true;
    }
    bool operator < ( const DICE &b ) const {
        FOR(i,0,5) {
            if ( face[i] < b.face[i] ) return true;
            else if ( face[i] > b.face[i] ) return false;
        }
        return false;
    }

    //Find the original Scheme of the DICE
    DICE diceScheme() {
        DICE res = *this;
        DICE temp = *this;

        FOR(i,0,3) {
            temp = temp.rotateX();
            FOR(j,0,3) {
                temp = temp.rotateZ();
                if ( temp < res ) res = temp;
            }
        }
        FOR(i,0,3) {
            temp = temp.rotateY();
            FOR(j,0,3) {
                temp = temp.rotateZ();
                if ( temp < res ) res = temp;
            }
        }
        return res;
    }

    void print() {
        FOR(i,0,5) printf ( "%d ", face[i] );
        nl;
    }
};
