#include <bits/stdc++.h>
using namespace std;

int main() {
    // --- Example 1: Multiple lines in a loop ---
    int n = 3; // number of lines
    cout << "Enter " << n << " lines:\n";
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        cout << "Line " << i+1 << ": " << line << "\n";
    }

    // --- Example 2: Number first, then lines ---
    int m;
    cout << "Enter number of lines: ";
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard leftover '\n'

    cout << "Enter " << m << " lines:\n";
    for (int i = 0; i < m; i++) {
        string line;
        getline(cin, line);
        cout << "Line " << i+1 << ": " << line << "\n";
    }

    // --- Example 3: Reading until EOF using while(getline) ---
    cout << "Enter lines (Ctrl+D / Ctrl+Z to stop):\n";
    string line;
    while (getline(cin, line)) {
        cout << "Read: " << line << "\n";
    }

    return 0;
}
