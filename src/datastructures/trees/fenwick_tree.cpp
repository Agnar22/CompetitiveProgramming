#include <iostream>
#include <vector>

#define LSOne(a) (a & (-a))

using namespace std;

class FenwickTree {
public:
    vector<int> ft;
    FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }

    int rsq(int i) {
        int sum = 0;
        for (; i > 0; i -= LSOne(i))
            sum += ft[i];
        return sum;
    }

    int rsq(int i, int j) {
        return rsq(j) - (i == 1 ? 0 : rsq(i - 1));
    }

    void update(int k, int v) {
        for (; k < ft.size(); k += LSOne(k))
            ft[k] += v;
    }
};

