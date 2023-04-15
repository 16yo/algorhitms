#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////
 
void turn_std_sync_off() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

////////////////////////////////////////////////

const int64_t INF = 1e10;

struct wedge {
    int64_t u;
    int64_t v;
    int64_t w;

};

using wgraph = vector<vector<wedge>>;


int main(int argc, char** argv) {

    turn_std_sync_off();
    
    uint64_t n, m, start; cin >> n >> m >> start; --start;

    vector<wedge> edges;

    for (uint64_t i = 0; i < m; ++i) {
        int64_t u, v, w; cin >> u >> v >> w; --u; --v;
        edges.push_back(wedge{u, v, w});
        edges.push_back(wedge{v, u, w});
    }

    bool flag = true;
    vector<int64_t> dp(n, INF);
    dp[start] = 0;
    for (uint64_t i = 0; i < n; ++i) {
        flag = false;
        for (wedge elem : edges) {
            int64_t u, v, w;
            u = elem.u; v = elem.v; w = elem.w;
            if (dp[v] > dp[u] + w) {
                dp[v] = dp[u] + w;
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }

    if (flag) {
        cout << "Negative cycle\n";
    } else {
        for (int64_t el : dp) {
            cout << (el < INF ? el : -1) << " ";
        }
        cout << endl;
    }

    

    return 0;
}