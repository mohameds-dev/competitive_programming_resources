#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    segment_tree<int> st;
    st.init(n);

    for (int i = 0; i < n; ++i)
    {
        int val;
        cin >> val;
        st.set_index_to_value(i, val);
    }

    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i, v;
            cin >> i >> v;
            st.set_index_to_value(i, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.get(l, r).val << '\n';
        }
    }

    return 0;
}
