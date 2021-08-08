#include <vector>
#include <numeric>
#include "../src/datastructures/trees/fenwick_tree.cpp"
#include "gtest/gtest.h"

TEST(FenwickTree, build) {
    int tree_size = 10;
    FenwickTree ft(tree_size);

    ASSERT_EQ(ft.ft, vector<int>(tree_size+1, 0));
}

TEST(FenwickTree, update) {
    int node = 3;
    int val = 5;
    int tree_size = 10;
    FenwickTree ft(tree_size);

    ft.update(node, val);

    for (int i = 1; i<=tree_size; i++)
        ASSERT_EQ(ft.rsq(i, i), i==node?val:0);
}

TEST(FenwickTree, ranges) {
    vector<int> vals{5, 10, 17, -5, -2, 10, 123, 34, -100};
    FenwickTree ft(vals.size());

    for (int i=0; i<vals.size(); i++)
        ft.update(i+1, vals[i]);

    for (int i = 0; i<vals.size(); i++)
        for (int j = i; j<vals.size(); j++)
            ASSERT_EQ(ft.rsq(i+1, j+1), std::accumulate(vals.begin()+i, vals.begin()+j+1, 0));
}

TEST(FenwickTree, ranges_update_twice) {
    vector<int> vals{5, 10, 17, -5, -2, 10, 123, 34, -100};
    vector<int> vals2{-5, 1, 7, 5, -3, 1, 13, 4, -10};
    FenwickTree ft(vals.size());

    for (int i=0; i<vals.size(); i++)
        ft.update(i+1, vals[i]);
    for (int i=0; i<vals.size(); i++)
        ft.update(i+1, vals2[i]);

    for (int i = 0; i<vals.size(); i++)
        for (int j = i; j<vals.size(); j++)
            ASSERT_EQ(
                ft.rsq(i+1, j+1),
                std::accumulate(vals.begin()+i, vals.begin()+j+1, 0) +
                std::accumulate(vals2.begin()+i, vals2.begin()+j+1, 0)
            );
}