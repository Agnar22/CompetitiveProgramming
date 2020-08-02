#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

/*

    Segment tree

    Initialization  -   O(nlog(n))
    Update          -   O(log(n))
    Range query     -   O(log(n))

*/

// TODO: Consider returning l/r value reference from aggregate function
//       for performance or smart pointers.

template <typename T>
class SegmentTree {
    private:
        int num_leaves;
        std::vector<T> tree;
        std::function<T(T&, T&)> aggregate;

        void build(int p, int L, int R, std::vector<T> &leaves) {
            if (L == R) {
                tree[p] = leaves[L];
            } else {
                int p1 = left_child(p), p2 = right_child(p);
                build(left_child(p), L, (L + R) / 2, leaves);
                build(right_child(p), ((L + R) / 2) + 1, R, leaves);
                tree[p] = aggregate(tree[p1], tree[p2]);
            }
        }

        int left_child(int p){
            return p << 1;
        }

        int right_child(int p){
            return (p << 1) + 1;
        }

        T reduce(int node, int leaf_l, int leaf_r, int bound_l, int bound_r) {
            if (bound_l <= leaf_l && leaf_r <= bound_r) {
                return tree[node];
            }

            int ll = leaf_l, lr = (leaf_l+leaf_r) / 2;
            int rl = lr + 1, rr = leaf_r;
            if (bound_l > lr)
                return reduce(right_child(node), rl, rr, bound_l, bound_r); 
            if (bound_r < rl)
                return reduce(left_child(node), ll, lr, bound_l, bound_r); 
            T p1 = reduce(right_child(node), rl, rr, bound_l, bound_r);
            T p2 = reduce(left_child(node), ll, lr, bound_l, bound_r);
            return aggregate(p1, p2);
        }

        T update_leaf(int node, int leaf_l, int leaf_r, int idx, T new_value) {
            if (idx < leaf_l || leaf_r < idx)
                return tree[node];
            if (leaf_l == idx && leaf_r == idx) {
                return tree[node] = new_value;
            }

            int ll = leaf_l, lr = (leaf_l+leaf_r) / 2;
            int rl = lr + 1, rr = leaf_r;
            T p1 = update_leaf(left_child(node), ll, lr, idx, new_value);
            T p2 = update_leaf(right_child(node), rl, rr, idx, new_value);
            return tree[node] = aggregate(p1, p2);
        }

    public:
        SegmentTree(std::vector<T> &leaves, T (*reducer)(T&, T&)) {
            aggregate = reducer;
            num_leaves = (int)leaves.size();
            tree.assign(4 * num_leaves, T {});
            build(1, 0, num_leaves - 1, leaves);
        }

        void update_leaf(T new_value, int idx) {
            if (idx < 0 || num_leaves - 1 < idx)
                throw "Index out of bounds.";
            update_leaf(1, 0, num_leaves - 1, idx, new_value);
        }

        T reduce(int l_idx, int r_idx) {
            if (l_idx > r_idx)
                throw "Invalid segment, l_idx should be lower than r_idx.";
            if (l_idx < 0 || num_leaves - 1 < r_idx)
                throw "Invalid segment, l_idx and r_idx should both be positive numbers lower than the number of leaves.";
            return reduce(1, 0, num_leaves - 1, l_idx, r_idx);
        }

        std::vector<T> get_tree() {
            return tree;
        }
};

int add(int& a, int& b) {
    return std::move(a+b);
}

int max(int& a, int& b) {
    return a >= b ? a : b;
}

