template <class state, class Merge = plus<state>> 
struct segtree {
    vector <state> node; 
    const Merge merge; 
    int sz = 1; 
    segtree (int n) : merge(Merge()) {
        while (sz < n) sz <<= 1; 
        node.resize(2 * sz); 
    }
    template <typename T> 
    segtree (const vector <T> &a) : segtree ((int) a.size()) {
        for (int i = 0;i < (int) a.size();i++) {
            node[i + sz] = state(a[i]); 
        }
        for (int i = sz - 1;i >= 1;i--) {
            node[i] = merge(node[i * 2], node[i * 2 + 1]); 
        }
    }
    template <typename T> 
    void set (int i, T v) {
        for (node[i += sz] = state(v);i > 1;i >>= 1) {
            node[i / 2] = merge(node[i / 2 * 2], node[i / 2 * 2 + 1]); 
        }
    }   
    state query (int id, int lx, int rx, int l, int r) {
        if (lx >= l && rx <= r) {
            return node[id]; 
        }
        if (lx > r || rx < l) return state(); 
        int mid = (lx + rx) / 2; 
        state left = query(id * 2, lx, mid, l, r); 
        state right = query(id * 2 + 1, mid + 1, rx, l, r); 
        return merge(left, right);
    }
    state query (int l, int r) {
        return query(1, 0, sz - 1, l, r); 
    }   
    int find_last (int r, int lx, int rx,int id, state x) {
        if (lx == rx) {
            if (lx <= r && node[id] > x) {
                return lx; 
            }
            return -1; 
        }
        int mid = (lx + rx) / 2; 
        int ans = -1; 
        if (node[id * 2 + 1] > x && mid + 1 <= r) ans = find_last(r, mid + 1, rx, 2 * id + 1, x); 
        if (ans == -1 && node[2 * id] > x) ans = find_last(r, lx, mid, 2 * id, x); 
        return ans;
    }
    int find_last (int l, int r, state x) {
        int ans = find_last(r, 0, sz - 1, 1, x); 
        if (ans >= l) return ans; 
        return -1; 
    }
    int find_first (int l, int lx, int rx, int id, state x) {
        if (lx == rx) {
            if (lx >= l && node[id] > x) {
                return lx; 
            }
            return -1; 
        }
        int mid = (lx + rx) / 2; 
        int ans = -1; 
        if (node[id * 2] > x && l <= mid) ans = find_first(l, lx, mid, 2 * id, x); 
        if (ans == -1 && node[id * 2 + 1] > x) ans = find_first(l, mid + 1, rx, 2 * id + 1, x); 
        return ans; 
    }
    int find_first (int l, int r, state x) {
        int ans = find_first(l, 0, sz - 1, 1, x); 
        if (ans <= r) return ans; 
        return -1; 
    }
};
struct state {
    int val = inf32;
    state () = default; 
    state (int val) : val(val) {
        
    }
    friend bool operator > (const state &a, const state &b) {
        return a.val < b.val; 
    } 
    friend state operator + (const state &a, const state &b) {
        state c; 
        return c = state(min(a.val,b.val)); 
    }
}; 