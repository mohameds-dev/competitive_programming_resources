#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "apple,banana,orange,grape";
    vector<string> tokens;
    string token;

    stringstream ss(s);
    while (getline(ss, token, ',')) { // split by comma
        tokens.push_back(token);
    }

    for (const auto &t : tokens)
        cout << t << "\n";

    return 0;
}
