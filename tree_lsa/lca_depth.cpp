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

struct wedge {
    int64_t u;
    int64_t v;
    int64_t w;
};

template <class T>
using graph = vector<vector<T>>;

#define MAX_DEPTH 20


// For unweighted grapg
struct lca {
    void dfs(const int64_t u, const int64_t p, const graph<int64_t>& g) {
        for (auto v : g[u]) {
            if (v == p) 
                continue;
            d[v] = d[u] + 1;
            up[v][0] = u;
            dfs(v, u, g);
        }
    }

    lca(const graph<int64_t>& g, const int64_t root) {
        n = g.size();
        up.resize(n, vector<int64_t>(MAX_DEPTH));
        d.resize(n);
        d[root] = 0;
        up[root][0] = root;
        dfs(root, root, g);
        foreach(j, 1, MAX_DEPTH, 1)
            foreach(u, 0, n, 1)
                up[u][j] = up[up[u][j - 1]][j - 1];
    }

    // p - direct ancentor
    void add_leaf(int64_t p) {
        up.push_back(vector<int64_t>(MAX_DEPTH));
        d.push_back(d[p] + 1);
        foreach(j, 1, MAX_DEPTH, 1)
            up[n][j] = up[up[n][j - 1]][j - 1];
        ++n;
    }

    int64_t find(const int64_t u_, const int64_t v_) {
        int64_t u = u_, v = v_;
        if (d[u] > d[v])
            swap(u, v);
        uint64_t delta = d[v] - d[u];
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j)
            if (delta & (1 << j))
                v = up[v][j];
        if (u == v)
            return u;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int64_t path_len(const int64_t u_, const int64_t v_) {
        int64_t u = u_, v = v_;
        if (d[u] > d[v])
            swap(u, v);
        uint64_t delta = d[v] - d[u];
        uint64_t res = delta;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j)
            if (delta & (1 << j))
                v = up[v][j];
        if (u == v)
            return res;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
                res += 2 * (1 << j);
            }
        }
        return res + 2;
    }


// private:
    vector<vector<int64_t>> up;
    vector<uint64_t> d;
    uint64_t n;

};

// For weighted graph

struct lca_weighted {
    void dfs(const int64_t u, const int64_t p, const graph<wedge>& g) {
        for (auto wg : g[u]) {
            int64_t v = wg.v;
            if (v == p) 
                continue;
            d[v] = d[u] + 1;
            up[v][0] = u;
            data[v][0] = wg.w;
            dfs(v, u, g);
        }
    }

    lca_weighted(const graph<wedge>& g, const int64_t root) {
        n = g.size();
        data.resize(n, vector<int64_t>(MAX_DEPTH));
        up.resize(n, vector<int64_t>(MAX_DEPTH));
        d.resize(n);
        d[root] = 0;
        up[root][0] = root;
        data[root][0] = 0;
        dfs(root, root, g);
        foreach(j, 1, MAX_DEPTH, 1)
            foreach(u, 0, n, 1)
                up[u][j] = up[up[u][j - 1]][j - 1];
        
        foreach(j, 1, MAX_DEPTH, 1)
            foreach(u, 0, n, 1)
                data[u][j] = data[u][j - 1] + data[up[u][j - 1]][j - 1];
    }

    // p - direct ancentor
    void add_leaf(int64_t p) {
        up.push_back(vector<int64_t>(MAX_DEPTH));
        d.push_back(d[p] + 1);
        foreach(j, 1, MAX_DEPTH, 1)
            up[n][j] = up[up[n][j - 1]][j - 1];
        foreach(j, 1, MAX_DEPTH, 1)
            data[n][j] = data[n][j - 1] + data[up[n][j - 1]][j - 1];
        ++n;
    }

    int64_t find(const int64_t u_, const int64_t v_) {
        int64_t u = u_, v = v_;
        if (d[u] > d[v])
            swap(u, v);
        uint64_t delta = d[v] - d[u];
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j)
            if (delta & (1 << j))
                v = up[v][j];
        if (u == v)
            return u;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int64_t path_len(const int64_t u_, const int64_t v_) {
        int64_t u = u_, v = v_;
        if (d[u] > d[v])
            swap(u, v);
        uint64_t delta = d[v] - d[u];
        int64_t w = 0;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j) {
            if (delta & (1 << j)) {
                w += data[v][j];
                v = up[v][j];
            }
        }
        if (u == v)
            return w;
        for (int64_t j = MAX_DEPTH - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                w += data[u][j] + data[v][j];
                u = up[u][j];
                v = up[v][j];
            }
        }
        return w + data[u][0] + data[v][0];
    }


// private:
    vector<vector<int64_t>> up;
    vector<vector<int64_t>> data;
    vector<uint64_t> d;
    uint64_t n;

};


int main(int argc, char** argv) {

    turn_std_sync_off();
    
    uint64_t n, m; cin >> n; m = n - 1;

    graph<wedge> g(n);
    
    foreach(i, 0, m, 1) {
        int64_t u, v, w; cin >> u >> v >> w;
        --u; --v;
        g[u].push_back({ u, v, w });
        g[v].push_back({ v, u, w });
    }

    int64_t root = 4; --root;
    lca_weighted a(g, root);

    foreach(i, 0, n, 1) {
        cout << a.data[i][19] << " ";
    }
    cout << endl;


    int64_t q; cin >> q;
    while (q--) {
        int64_t u, v; cin >> u >> v; --u; --v;
        cout << a.path_len(u, v) << endl;
    }

    return 0;
};