#include <bits/stdc++.h>
using namespace std;
const int N = 1e7; 

int spf[N] = {};
void preprocess() {
    spf[1] = spf[0] = 0;
    for (int i = 2; i < N; ++i) spf[i] = i;
    for (int i = 2; i * i < N; ++i) {
        if(spf[i] == i) {
            for (int j = i * i; j < N ; j += i)
                if (spf[j] > i) spf[j] = i;
        }
    }
}
