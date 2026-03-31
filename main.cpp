#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long memo[MAXN][MAXN];
bool vis[MAXN][MAXN];

// Count non-crossing trees on interval [l, r]
long long dp(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;

    if (vis[l][r]) return memo[l][r];
    vis[l][r] = true;

    long long res = 0;

    // Node l connects to some node k in [l+1, r]
    for (int k = l + 1; k <= r; k++) {
        if (adj[l][k] == 0) continue;

        long long left = dp(l + 1, k - 1);
        long long right = dp(k + 1, r);
        res = (res + left * right % MOD) % MOD;
    }

    memo[l][r] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    if (n == 2) {
        cout << (adj[0][1] ? 1 : 0) << endl;
        return 0;
    }

    memset(vis, false, sizeof(vis));

    long long answer = 0;

    // Case 1: Node 0 has degree 1 (leaf)
    for (int k = 1; k < n; k++) {
        if (adj[0][k] == 0) continue;

        long long ways = dp(1, k - 1) * dp(k + 1, n - 1) % MOD;
        answer = (answer + ways) % MOD;
    }

    // Case 2: Node 0 has degree >= 2
    for (int i = 1; i < n; i++) {
        if (adj[0][i] == 0) continue;

        for (int j = i + 1; j < n; j++) {
            if (adj[0][j] == 0) continue;

            long long ways = dp(1, i - 1);
            ways = ways * dp(i + 1, j - 1) % MOD;
            ways = ways * dp(j + 1, n - 1) % MOD;

            answer = (answer + ways) % MOD;
        }
    }

    cout << answer << endl;

    return 0;
}
