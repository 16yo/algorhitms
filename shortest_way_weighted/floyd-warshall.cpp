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

using matrix = vector<vector<int64_t>>;

int main(int argc, char** argv) {

    turn_std_sync_off();
    
    uint64_t n, m; cin >> n;
    
    matrix g(n, vector<int64_t>(n, INF));
    
    foreach(i, 0, n, 1) {
        foreach(j, 0, n, 1) {
            cin >> g[i][j];
        }
    }

    matrix d(g);

    foreach(i, 0, n, 1)
        d[i][i] = 0;

    foreach(k, 0, n, 1)
        foreach(u, 0, n, 1) 
            foreach(v, 0, n, 1)
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);

    foreach(i, 0, n, 1) {
        foreach(j, 0, n, 1) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
};