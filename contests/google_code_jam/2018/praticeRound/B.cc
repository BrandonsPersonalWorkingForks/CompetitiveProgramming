#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '{';
    std::string separator;

    for (const T& item : container) {
        os << separator << item, separator = ", ";
    }

    return os << '}';
}

#ifdef DBG_MODE
void dbg_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void dbg_out(Head A, Tail... B) {
    std::cerr << ' ' << A;
    dbg_out(B...);
}
#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define test(...)
#endif

const int32_t INF = int32_t(numeric_limits<int32_t>::max());
const string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void run_case(const uint16_t& tc) {
    uint16_t N;
    cin >> N;

    vector<int32_t> A(N);

    for_each(A.begin(), A.end(), [&](uint32_t& a) { cin >> a; });

    vector<array<char, 2>> ans;
    array<int32_t, 2> reduce = {0, -INF};

    for (uint16_t i = 1; i < N; ++i) {
        if (A[i] > A[reduce[0]]) {
            reduce[0] = i;
        }
    }

    reduce[1] = A[reduce[0]];
    A[reduce[0]] = -INF;
    int32_t target = *max_element(A.begin(), A.end());
    A[reduce[0]] = target;

    for (int32_t i = reduce[1]; i > target; i -= 2) {
        ans.emplace_back(ALPH[reduce[0]], i - 2 >= target ? ALPH[reduce[0]] : ' ');
    }

    A[reduce[0]] = -INF;
    reduce[1] = INF;

    for (uint16_t i = 0; i < N; ++i) {
        if (A[i] == target) {
            reduce[0] == -INF ? reduce[0] = i : reduce[1] = i;
        }

        if (reduce[0] != -INF && reduce[1] != -INF) break;
    }

    for (int32_t i = 0; i < target; i++) {
        ans.emplace_back(ALPH[reduce[0]], ALPH[reduce[1]]);
    }

    cout << "Case #" << tc << ": ";
    for_each(ans.begin(), ans.end(), [&](const array<char, 2>& a) {
        cout << a[0] << a[1];
    });

    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t test_cases;
    std::cin >> test_cases;

    for (uint16_t tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
#ifdef DBG_MODE
        std::cout << std::flush;
#endif
    }

#ifndef DBG_MODE
    std::cout << std::flush;
#endif

    return 0;
}