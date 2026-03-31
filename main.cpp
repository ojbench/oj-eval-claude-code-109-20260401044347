#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];

// Compute non-crossing trees for interval [start, end] in circular order
// start and end are absolute node indices
long long compute_interval(int start, int len) {
    if (len <= 0) return 1;
    if (len == 1) return 1;

    // Use DP: dp[i][j] = ways to connect nodes in subinterval [i, i+j]
    long long dp[len + 1][len + 1];
    memset(dp, 0, sizeof(dp));

    // Base cases
    for (int i = 0; i <= len; i++) {
        dp[i][0] = 1;  // Empty interval
    }

    // Fill DP table
    for (int l = 1; l <= len; l++) {  // Length of interval
        for (int i = 0; i + l <= len; i++) {  // Start of interval
            int j = i + l - 1;  // End of interval

            // Node indices in original graph
            int node_i = (start + i) % n;

            // Try connecting node_i to node_k
            for (int k = i + 1; k <= j + 1; k++) {
                if (k > j) break;
                int node_k = (start + k) % n;
                if (adj[node_i][node_k] == 0) continue;

                long long left = (k == i + 1) ? 1 : dp[i + 1][k - i - 2];
                long long right = (k == j) ? 1 : dp[k + 1][j - k - 1];

                dp[i][j - i] = (dp[i][j - i] + left * right % MOD) % MOD;
            }
        }
    }

    return dp[0][len - 1];
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

    // Sum over all choices of root
    long long answer = 0;

    for (int root = 0; root < n; root++) {
        // root connects to pairs (i, j)
        for (int i = 0; i < n - 1; i++) {
            int node_i = (root + 1 + i) % n;
            if (adj[root][node_i] == 0) continue;

            for (int j = i + 1; j < n - 1; j++) {
                int node_j = (root + 1 + j) % n;
                if (adj[root][node_j] == 0) continue;

                // Compute three intervals
                long long ways = 1;
                ways = ways * compute_interval((root + 1) % n, i) % MOD;
                ways = ways * compute_interval((root + 1 + i + 1) % n, j - i - 1) % MOD;
                ways = ways * compute_interval((root + 1 + j + 1) % n, n - 2 - j) % MOD;

                answer = (answer + ways) % MOD;
            }
        }
    }

    cout << answer << endl;

    return 0;
}
