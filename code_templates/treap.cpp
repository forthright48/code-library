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
        root = NULL; //When the first element is inserted, that element becomes the root
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
        /** Takes a treap and splits it into two subtree l and r
            such that, l contains elements smaller to key 
            and r contains elements bigger or equal than key
        */
        if ( !t ) { // If treap is empty there is nothing to split
            l = r = NULL;
        }
        else if ( key < t->key ) { // If key is smaller than root
            // So now, we have a treap whose right subtree is bigger than root
            // but its left subtree has SOME values smaller than key
            // So hey! Lets SPLIT the left subtree and extract those values which are bigger than key 
            // and put them to treap->l. That way, our current treap will have all values bigger than 
            // key
            split( t->l, key, l, t->l );
            r = t;
        }
        else {
            // Same as above. We split treap->r.
            split( t->r, key, t->r, r );
            l = t;
        }
        upd_cnt (t);
    }
    void insert ( pitem &t, pitem it ) {
        if ( !t ) { // If the treap is empty, make the item root of the tree
            t = it;
            size++;
        }
        else if ( it->prior > t->prior ) { // When item is more important than root
            // Since it is more important than root, IT should be the root
            split( t, it->key, it->l, it->r ); // Split the treap and put them as child of item
            t = it;
            size++;
        }
        else  // Item is not more important than root
            if ( it->key < t->key ) insert( t->l, it ); // If item is smaller than root, than go to left subtree
            else insert ( t->r, it ); // Else go to right subtree
        }
        upd_cnt (t);
    }

    void merge ( pitem &t, pitem l, pitem r ) {
        /** Merges two treap where l contains values smaller than r 
            
            After merging the treap, put it inside pitem t
        */
        if ( !l || !r ) {
            t = l? l:r;
        }
        else if ( l->prior > r->prior ){ // Left subtree is more important
            // 
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
        else { // Iterate over the treap until we find the key
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
