#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    preprocess();
    for (int i = 50; i < 70; i ++)
    {
        cout << i << " " << spf[i] << endl;
    }
    // Factorize 60: 2 * 2 * 3 * 5
    int x = 60;
    vector<int> factors;
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }

    cout << x << " : ";
    for (int i : factors) cout << i << " ";

    
    return 0;
}

