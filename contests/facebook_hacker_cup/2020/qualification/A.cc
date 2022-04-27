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
#include <vector>
using namespace std;

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif


template<typename T, class Fun>
void print_empty_matrix(const int &_x, const int &_y, T _a, T _b, Fun condition, const bool space = false) {
    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            std::cout << (condition(x, y) ? _b : _a);

            if (space) std::cout << ' ';
        }

        std::cout << '\n';
    }
}


void runCase(int tc) {
    int N;
    cin >> N;
    string A, B;
    cin >> A >> B;

    cout << "Case #" << tc << ":" << '\n';
    print_empty_matrix(N, N, 'N', 'Y', [&](int x, int y) -> bool {
        if (x == y)
            return true;

        int starting = min(x, y), ending = max(x, y);
        bool conecting = B[x] == 'Y' && A[y] == 'Y';

        for (int i = starting + 1; i < ending; i++) 
            conecting = conecting && A[i] == 'Y' && B[i] == 'Y';

        return conecting;
    });
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}