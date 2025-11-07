#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;

typedef vector<int> vi;
typedef vector<ll> vll;

#define el '\n'
#define pb push_back

#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

#define OO (int)2e9
#define LOO (ll)9e18

#define bitCountLL(x) __builtin_popcountll(x)
#define bitCount(x) __builtin_popcount(x)


int di[] = {-1, 1, 0, 0, 1, -1, 1, -1};
int dj[] = {0, 0, 1, -1, 1, -1, -1, 1};


const int mod = (int) 1e9 + 7;
const int N = 2e5 + 5, M = 20 + 5;

bool MULTIPLE_TEST_CASES = true;

void run_case(int case_index){

}


int main() {
    // FILE IO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // FAST IO
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    int test_cases = 1;
    if (MULTIPLE_TEST_CASES) cin >> test_cases;
    
    for (int i = 1; i <= test_cases; ++i) {
        run_case(i);
    }
}