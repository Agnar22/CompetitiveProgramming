#include <vector>
#include "../src/datastructures/trees/segment_tree.cpp"
#include "gtest/gtest.h"

TEST(SegmentTree, build) {
    std::vector<int> nodes{0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);
    std::vector<int> tree{0, 6, 1, 5, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0};
    
    ASSERT_EQ(sgt.get_tree(), tree);
}

TEST(SegmentTree, update) {
    std::vector<int> nodes{0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);
    std::vector<int> tree{0, 15, 10, 5, 0, 10, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0};

    sgt.update_leaf(10, 1);
    
    ASSERT_EQ(sgt.get_tree(), tree);
}

TEST(SegmentTree, update_out_of_bounds_left) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    try {
        sgt.update_leaf(10, -1);
        FAIL();
    } catch (...) {
        SUCCEED();
    }
}

TEST(SegmentTree, update_out_of_bounds_right) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    try {
        sgt.update_leaf(10, 6);
        FAIL();
    } catch (...) {
        SUCCEED();
    }
}

TEST(SegmentTree, reduce_leftmost) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    int sum = sgt.reduce(0, 0);

    ASSERT_EQ(sum, 10);
}

TEST(SegmentTree, reduce_rightmost) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    int sum = sgt.reduce(5, 5);

    ASSERT_EQ(sum, 3);
}

TEST(SegmentTree, reduce_entire) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    int sum = sgt.reduce(0, 5);

    ASSERT_EQ(sum, 17);
}

TEST(SegmentTree, reduce_partial) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    int sum = sgt.reduce(1, 4);

    ASSERT_EQ(sum, 4);
}

TEST(SegmentTree, reduce_out_of_bounds_left) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    try {
        sgt.reduce(-1, 4);
        FAIL();
    } catch (...) {
        SUCCEED();
    }
}

TEST(SegmentTree, reduce_out_of_bounds_right) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    try {
        sgt.reduce(1, 6);
        FAIL();
    } catch (...) {
        SUCCEED();
    }
}

TEST(SegmentTree, reduce_illegal_segment) {
    std::vector<int> nodes{10, 1, 0, 1, 2, 3};
    SegmentTree<int> sgt(nodes, add);

    try {
        sgt.reduce(3, 2);
        FAIL();
    } catch (...) {
        SUCCEED();
    }
}

