#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define line(a) (a).begin(), (a).end()

typedef vector<vector<i64>> graph;

vector<i64> bfs(i64 u, const graph& g) {
    i64 n = g.size();
    vector<i64> d(n, -1);
    queue<i64> q;
    d[u] = 0;
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (i64 v : g[u]) {
            if (d[v] == -1) {
                d[v] = 1 + d[u];
                q.push(v);
            }
        }
    }
    return d;
}

bool dfs(i64 u, const graph& g, vector<i64>& mt, vector<char>& visited) {
    if (visited[u]) {
        return 0;
    }
    visited[u] = true;
    for (i64 v : g[u]) {
        if (mt[v] == -1) {
            mt[v] = u;
            return true;
        }
        bool tmp = dfs(mt[v], g, mt, visited);
        if (tmp) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

struct eg {
    eg () {
        this->u = this->v = 0;
    }
    eg (i64 u, i64 v) {
        this->u = u;
        this->v = v;
    }
    i64 u;
    i64 v;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    i64 n, m;
    cin >> n >> m;
    graph g(2 * n);

    vector<i64> f(2 * n);
    vector<i64> d(2 * n);

    i64 c = 0;

    {
        i64 u, v;
        for (i64 i = 0; i < m; ++i) {
            cin >> u >> v; --u; -- v;
            f[u] = u;
            f[v + n] = v;
            g[u].push_back(v + n);
            g[v + n].push_back(u);
        }
        for (i64 i = 0; i < 2 * n; ++i) {
            d[i] = (i < n ? 0 : 1);
        }
    }


    
    i64 ans = 0;
    vector<i64> mt(2 * n, -1);
    for (i64 i = 0; i < 2 * n; ++i) {
        if (d[i] & 1) {
            continue;
        }
        vector<char> visited(2 * n, false); 
        ans += dfs(i, g, mt, visited);
    }

    cout << ans << endl;

    for (i64 i = 0; i < 2 * n; ++i) {
        if (mt[i] == -1) {
            continue;
        }
        cout << f[mt[i]] + 1 << " " << f[i] + 1 << endl;
    }
    


    return 0;
}