// https://cp-algorithms.com/data_structures/fenwick.html

struct FenwickTree
{
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size())
    {
        for (int i = 0; i < n; i++)
        {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    int sum(int r)
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

// https://csacademy.com/lesson/fenwick_trees
// this one is easier to derive if the BIT was drawn like in the above article
struct FenwickTree
{
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size())
    {
        for (int i = 0; i < n; i++)
        {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    int lsb(int pos)
    {
        return pos & -pos;
    }

    int sum(int pos)
    {
        int sum = 0;
        while (pos > 0)
        {
            sum += bit[pos];
            pos -= lsb(pos);
        }
        return sum;
    }

    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    void add(int pos, int val)
    {
        while (pos <= n)
        {
            bit[pos] += val;
            pos += lsb(pos);
        }
    }
};

// 2D 
struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n,int m){
        bit.assign(n,vector<int>(m,0));
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};





