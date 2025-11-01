// templated node type. The neutral value is a static field on the node struct.
template <typename T>
struct node
{
    T val;
};

// generic segment tree storing nodes of type node<T>
template <typename T>
struct segment_tree
{
    int size = 1;
    vector<node<T>> nodes;

    // for safe margin and no loop. we can initialize by 4*num_leaves
    // NOT RECOMMENDED for multiple initialization or large N
    void init(int num_leaves)
    {
        while (size < num_leaves)
            size <<= 1;
        nodes.resize(size << 1);
        nodes.assign(size << 1, neutral_node());
    }

    node<T> neutral_node() const
    {
        return {T{}}; // like 0 or empty string
    }

    node<T> single(T val) const
    {
        return {val};
    }

    // merge operation — here sum for generic T that supports +, it can be product, min, max, etc.
    node<T> merge(const node<T> &node1, const node<T> &node2) const
    {
        return single(node1.val + node2.val);
    }

    void build(vector<T> &v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)v.size())
            {
                nodes[x] = single(v[lx]);
            }
            return;
        }

        int m = (rx + lx) >> 1;
        build(v, 2 * x + 1, lx, m);
        build(v, 2 * x + 2, m, rx);
        nodes[x] = merge(nodes[2 * x + 1], nodes[2 * x + 2]);
    }

    void build(vector<T> &v)
    {
        build(v, 0, 0, size);
    }

    // desired index, value (as node), current node index, left and right bounds of node
    void set_index_to_value(int i, const node<T> &v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        { // we are at desired node
            nodes[x] = v;
            return;
        }

        int m = (rx + lx) >> 1;
        if (i < m)
        { // go left
            set_index_to_value(i, v, 2 * x + 1, lx, m);
        }
        else
        { // go right
            set_index_to_value(i, v, 2 * x + 2, m, rx);
        }
        nodes[x] = merge(nodes[2 * x + 1], nodes[2 * x + 2]);
    }

    void set_index_to_value(int i, T val)
    {
        set_index_to_value(i, single(val), 0, 0, size);
    }

    node<T> get(int l, int r, int x, int lx, int rx) const
    {
        if (l >= rx || lx >= r)
        { // out of bounds of query
            return neutral_node();
        }
        if (lx >= l && rx <= r)
        {
            return nodes[x]; // all within bounds, take this node
        }

        int m = (rx + lx) >> 1;
        node<T> lt = get(l, r, 2 * x + 1, lx, m);
        node<T> rt = get(l, r, 2 * x + 2, m, rx);
        return merge(lt, rt);
    }

    node<T> get(int l, int r) const
    {
        return get(l, r, 0, 0, size);
    }
};
