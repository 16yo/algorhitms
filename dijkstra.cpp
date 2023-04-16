#include <bits/stdc++.h>

using namespace std;

////////////////////////////////////////////////
 
void turn_std_sync_off() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

#define foreach(i, b, e, s) for(int64_t i = b; i < e; i += s)

////////////////////////////////////////////////

const int64_t INF = 1e10;

struct wedge {
    int64_t u;
    int64_t v;
    int64_t w;

};

using wgraph = vector<vector<wedge>>;

void dijkstra_slow(vector<int64_t>& dp, vector<int64_t>& p, const int64_t s, const wgraph& g) {
    int64_t n = g.size();
    dp[s] = 0;
    p[s] = s;
    vector<int8_t> visited(n, 0);
    for (int64_t i = 0; i < n; ++i) {
        int64_t mid_id = -1;
        int64_t val = INF;
        for (int64_t j = 0; j < n; ++j) {
            if (!visited[j] and dp[j] < val) {
                mid_id = j;
                val = dp[j];
            }
        }
        if (mid_id == -1) {
            return;
        }
        int64_t u = mid_id;
        visited[u] = true;
        for (wedge el : g[u]) {
            int64_t v  = el.v;
            int64_t w = el.w;
            if (dp[v] > dp[u] + w) {
                dp[v] = dp[u] + w;
                p[v] = u; 
            }
        }
    }
}

using item = pair<int64_t, int64_t>;
void dijkstra_fast(vector<int64_t>& dp, vector<int64_t>& p, const int64_t s, const wgraph& g) {
    int64_t n = g.size();
    dp[s] = 0;
    p[s] = s;
    set<item> pq;
    foreach(i, 0, n, 1)
        pq.insert({dp[i], i});
    vector<int8_t> visited(n, 0);
    while (!pq.empty()) {
        item el = *pq.begin();
        pq.erase(pq.begin());
        int64_t u = el.second;
        visited[u] = 1;
        for (wedge elem : g[u]) {
            int64_t v = elem.v;
            if (visited[v])
                continue;
            int64_t w = elem.w;
            if (dp[u] + w < dp[v]) {
                pq.erase({dp[v], v});
                dp[v] = dp[u] + w;
                p[v] = u;
                pq.insert({dp[v], v});
            }
        }
    }
}

int main(int argc, char** argv) {

    turn_std_sync_off();
    
    int64_t n, m, s, f; cin >> n >> m >> s >> f;
    --s; --f;
    wgraph g(n);

    foreach(i, 0, m, 1) {
        int64_t u, v, w; cin >> u >> v >> w; --u; --v;
        g[u].push_back({u, v, w});
        g[v].push_back({v, u, w});
    }

    vector<int64_t> prev(n);
    vector<int64_t> dp(n, INF);
    dp[s] = 0;

    dijkstra_fast(dp, prev, s, g);


    foreach(i, 0, n, 1)
        cout << i + 1 << "\t";
    cout << endl;
    foreach(i, 0, n, 1)
        cout << (dp[i] < INF ? dp[i] : -1) << "\t";
    cout << endl;
    int64_t u = f;
    vector<int64_t> path;
    while(prev[u] != u) {
        path.push_back(u);
        u = prev[u];
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    cout << "Path from start to finish node:\n";
    for (auto u : path) {
        cout << u + 1 << " ";   
    }
    cout << endl;

    cout << endl;    

    return 0;
};
