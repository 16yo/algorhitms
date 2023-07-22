#include <bits/stdc++.h>

using namespace std;

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define min(a, b) ((a) < (b) ? (a) : (b))

struct segtree {
    vector<i64> data;
    i64 n;

    segtree(i64 _n) : n(_n), data(4 * _n) {}
    segtree(const vector<i64>& a) : segtree(a.size()) {
        build(1, 1, n, a);
    }

    void build(i64 id, i64 l, i64 r, const vector<i64>& a) {
        if ( l == r) {
            data[id] = a[l - 1];
            return;
        }
        i64 m = (l + r) / 2;
        build(id * 2, l, m, a);
        build(id * 2 + 1, m + 1, r, a);
        data[id] = data[id * 2] + data[id * 2 + 1];
    }

    void set(i64 p, i64 x) {
        set(1, 1, n, p, x);
    }

    void set(i64 id, i64 l, i64 r, i64 p, i64 x) {
        if (l == r){ 
            data[id] += x;
            return;
        }
        i64 m  = (l + r) / 2;
        if (p <= m) {
            set(id * 2, l, m, p, x);
        } else {
            set(id * 2 + 1, m + 1, r, p, x);
        }
        data[id] = data[id * 2] + data[id * 2 + 1];
    }

    i64 get(i64 ql, i64 qr) {
        return get(1, 1, n, ql, qr);
    }

    i64 get(i64 id, i64 l, i64 r, i64 ql, i64 qr) {
        if (ql <= l && r <= qr) {
            return data[id];
        } 
        i64 m = (l + r) / 2;
        if  (qr <= m) {
            return get(id * 2, l, m, ql, qr);
        } 
        if (m + 1 <= ql) {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        return get(id * 2, l, m, ql, qr) + get(id * 2 + 1, m + 1, r, ql, qr);
    }
};


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    
    i64 n; cin >> n;
    vector<i64> a(n);

    for (auto& i : a) {
        cin >> i;
    }

    segtree st(a);

    i64 k; cin >> k;

    for (i64 i = 0; i < k; ++i) {
        i64 q, x, y; cin >> q >> x >> y;
        if (q == 0) {
            cout << st.get(x, y) << endl;
        } else if (q == 1) {
            st.set(x, y);
        }
    }

    return 0;
}