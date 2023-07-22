#include <bits/stdc++.h>

using namespace std;

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define min(a, b) ((a) < (b) ? (a) : (b))

vector<i64> z_func(const string& s) {
    int n = s.size();
    vector<i64> z(n);
    z[0] = n;
    i64 l = 0, r = 0;
    for (i64 i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] <n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    vector<i64> z = z_func(s);
    for (auto i : z) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}