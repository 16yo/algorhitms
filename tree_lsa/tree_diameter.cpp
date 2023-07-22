#include <bits/stdc++.h>

using namespace std;

////////////////////////////////////////////////
 
void turn_std_sync_off() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

#define foreach(i, b, e, s) for(int64_t i = b; i < e; i += s)

////////////////////////////////////////////////

const uint64_t INF = 1e10;

template <class T>
using graph = vector<vector<T>>;

void dfs(int64_t u, int64_t p, vector<uint64_t>& d, const graph<int64_t>& g) {
    for (auto v : g[u]) {
        if (v == p) 
            continue;
        d[v] = d[u] + 1;
        dfs(v, u, d, g);
    }
}

int main(int argc, char** argv) {

    turn_std_sync_off();
    
    uint64_t n, m; cin >> n; m = n - 1;

    graph<int64_t> g(n);
    
    foreach(i, 0, m, 1) {
        int64_t u, v; cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<uint64_t> d(n, INF);

    int64_t s = 0;

    d[s] = 0;
    dfs(s, s, d, g);

    int64_t s_ = 0;
    foreach(i, 0, n, 1)
        if (d[s_] < d[i])
            s_ = i;

    d.resize(n, INF);

    dfs(s_, s_, d, g);

    int64_t f = 0;
    foreach(i, 0, n, 1)
        if (d[f] < d[i])
            f = i;

    cout << s_ + 1 << " " << f + 1 << endl;

    return 0;
};