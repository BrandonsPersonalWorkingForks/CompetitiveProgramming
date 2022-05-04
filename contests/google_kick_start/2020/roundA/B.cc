#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
}
template <typename Front, typename... Back>
void DBG_OUT(Front K, Back... T) {
    cerr << ' ' << K;
    DBG_OUT(T...);
}
template <typename T_List>
void testList(T_List List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#define testArgs(...)                                                     \
    cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
        DBG_OUT(__VA_ARGS__)
#else
template <typename T_List>
void testList(T_List List) {
    return;
}
#define testArgs(...)
#endif

void runCase(int tc) {
    int N, K, P;
    cin >> N >> K >> P;
    vector<vector<int>> A(N, vector<int>(K));

    for (auto &row : A)
        for (auto &cell : row) cin >> cell;

    vector<vector<int>> SUM(N, vector<int>(P + 1, 0));

    for (int i = 0; i < N; i++)
        for (int k = 1; k < P + 1; k++) {
            SUM[i][k] = SUM[i][k - 1] + A[i][k - 1];
        }

    vector<vector<int>> dp(N, vector<int>(P, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            for (int x = 0; x < P + 1; x++) {
                dp[i][j] = max(dp[i][j], SUM[i][j] +)
            }
        }
    }

    cout << "Case #" << tc << ": " << '\n';
}

int main() {
#ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}