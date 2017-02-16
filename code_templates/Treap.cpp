/*
To insert an item, pitem x = new item ( key, rand() * rand() )
Many functions need a root to be passed: insert ( treap.root, x )
*/

struct item {
    int key, prior, cnt;
    item * l, * r;
    item() {}
    item( int key, int prior ): key(key), prior(prior), l(NULL), r(NULL) {}
};
typedef item * pitem;

struct Treap {
    int size;
    pitem root;

    /*Resets the Treap. Not complete yet. Need to erase all elements from treap*/
    void clear() {
        size = 0;
        root = NULL;
    }

    int cnt (pitem t) {
        return t ? t->cnt : 0;
    }

    void upd_cnt (pitem t) {
        if (t) {
            t->cnt = 1 + cnt(t->l) + cnt (t->r);
        }
    }

    void split ( pitem t, int key, pitem &l, pitem &r ) {
        if ( !t ) {
            l = r = NULL;
        }
        else if ( key < t->key ) {
            split( t->l, key, l, t->l );
            r = t;
        }
        else {
            split( t->r, key, t->r, r );
            l = t;
        }
        upd_cnt (t);
    }
    void insert ( pitem &t, pitem it ) {
        if ( !t ) {
            t = it;
            size++;
        }
        else if ( it->prior > t->prior ) {
            split( t, it->key, it->l, it->r );
            t = it;
            size++;
        }
        else {
            insert( it->key < t->key? t->l:t->r, it );
        }
        upd_cnt (t);
    }

    void merge ( pitem &t, pitem l, pitem r ) {
        if ( !l || !r ) {
            t = l? l:r;
        }
        else if ( l->prior > r->prior ){
            merge ( l->r, l->r, r );
            t = l;
        }
        else {
            merge ( r->l, l, r->l );
            t = r;
        }
        upd_cnt( t );
    }

    void erase ( pitem &t, int key ) {
        if ( t->key == key ) {
            pitem e = t;
            merge( t, t->l, t->r );
            delete ( e );
            size--;
        }
        else {
            erase( key < t->key? t->l:t->r, key );
        }
        upd_cnt (t);
    }

    //Find key in treap
    pitem find ( pitem t, int key ) {
        if ( !t ) return t;
        if ( t->key == key ) return t;
        if ( key < t->key ) return find ( t->l, key );
        else return find ( t->r, key );
    }

    /*Finds number of element <= x in the treap*/
    int KPivot ( pitem t, int key ) {
        if ( !t ) return 0;
        else if ( t->key <= key ) {
            return ( cnt( t ) - cnt( t->r ) ) + KPivot(t->r, key);
        }
        else {
            return KPivot( t->l, key );
        }
    }

    /*Finds kth element in sorted order*/
    pitem pos ( pitem t, int p ) {
        if ( cnt ( t->l ) == p ) return t;
        if ( cnt ( t->l ) < p ) return pos ( t->r, p  - cnt(t->l) - 1 );
        else return pos ( t->l, p );
    }
}treap;
