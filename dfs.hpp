#ifndef DFS_H

#define DFS_H

#include <algorithm>
#include <vector>
#include <queue>
#include <cinttypes>
#include <utility>

#ifndef GRAPH_T
#define GRAPH_T
template <typename T>
using graph = std::vector<std::vector<T>>;
#endif

#ifndef INF_C
#define INF_C
const int32_t inf = static_cast<int32_t>((static_cast<int64_t>(1) << 31) - 1);
#endif

#ifndef DV
#define DV
struct dv {
    dv() {
        this->first = 0;
        this->second = 0;
    }
    int32_t first;
    uint64_t second;
};
bool operator ==(dv a, dv b) {
    return a.first == b.first && a.second == b.second;
}
#endif

dv dfs(const graph<int32_t>& g, std::vector<int32_t>& p, int32_t start,bool skip = false) {
    if (!skip) {
        p = std::vector<int32_t>(g.size(), -1);
    }
    dv v, t;
    for (int32_t u : g[start]) {
        t = dfs(g, p, u, true);
        if (v.second < t.second)
            p[start] = u;
            v = t;
    }
    if (v == dv()) {
        p[start] = start;
        v.first = start;
    }
    ++v.second;
    return v;
}

#endif