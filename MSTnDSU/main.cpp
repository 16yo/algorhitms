#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define line(a) (a).begin(), (a).end()

struct wedge {
    i64 u, v;
    i64 w;
};

typedef vector<wedge> graph;

bool operator<(wedge a, wedge b) {
    return a.w < b.w;
} 

struct dsu {
    vector<i64> leader;
    vector<i64> size;
    i64 n;

    dsu(i64 other_n) {
        n = other_n;
        leader.resize(n);
        for (i64 i = 0; i < n; ++i) {
            leader[i] = i;
        }
        size.resize(n, 1);
    }

    i64 find(i64 u) {
        if (leader[u] == u) {
            return u;
        }
        leader[u] = find(leader[u]);
        return leader[u];
    }

    bool merge(i64 u, i64 v) {
        i64 lu = find(u);
        i64 lv = find(v);
        if (lu == lv) {
            return false;
        }
        if (size[lu] > size[lv]) {
            swap(lu, lv);
        }
        leader[lu] = lv;
        size[lv] += size[lu];
        return true;
    }
};

int main() {

    i64 n, m;
    cin >> n >> m;
    graph g;
    for (i64 i = 0; i < m; ++i) {
        i64 u, v, w;
        cin >> u >> v >> w;
        g.push_back(wedge{u - 1, v - 1, w});
    }

    sort(line(g));
    dsu d(n);
    i64 W = 0;
    for (wedge e : g) {
        if (!d.merge(e.u, e.v)) {
            continue;
        }
        W += e.w;
    }

    cout << W << endl;

    return 0;
}