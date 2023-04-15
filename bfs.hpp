#ifndef BFS_H

#define BFS_H

#include <vector>
#include <queue>
#include <cinttypes>

#ifndef GRAPH_T
#define GRAPH_T
template <typename T>
using graph = std::vector<std::vector<T>>;
#endif

#ifndef INF_C
#define INF_C
const int32_t inf = static_cast<int32_t>((static_cast<int64_t>(1) << 31) - 1);
#endif

void bfs(const graph<int32_t>& g, std::vector<int32_t>& d, std::vector<int32_t>& p, const uint32_t start) {
    std::queue<int32_t> q;
    q.push(start);
    d = std::vector<int32_t>(g.size(), inf);
    d[start] = 0;
    p = std::vector<int32_t>(g.size(), 0);
    p[start] = start;
    while (!q.empty()) {
        int32_t u = q.front();
        q.pop();
        for (int32_t to : g[u]) {
            if (d[to] == inf) {
                q.push(to);
                d[to] = d[u] + 1;
                p[to] = u;
            }
        }
    }
}

#endif