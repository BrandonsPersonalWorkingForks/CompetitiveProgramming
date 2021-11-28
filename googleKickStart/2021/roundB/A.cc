#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif


void runCase() {
    int N;
    string S;
    cin >> N >> S;

    for (int i = 0; i < N; i++) {
        int count = 1;
        
        for (int k = i; k > 0; k--) {
            if (S[k] - '0' > S[k - 1] - '0') {
                testArgs(S[k] - '0', S[k - 1] - '0');
                count++;
            }
        }

        cout << count << ' ';
        count = 1;
    }

    cout << '\n';
}


// #define TEXT_IO
int main() {
    #ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    printf("Don't Forget to Submit Without DBG Enabled\n\n");
    #endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        cout << "Case #" << tc << ": ";
        runCase();
        cerr << flush;
    }
}