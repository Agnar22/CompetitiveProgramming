add_executable(segment_tree_tests do_tests.cpp segment_tree_tests.cpp)
target_link_libraries(segment_tree_tests PUBLIC source gtest)
add_test(NAME SEGMENT_TREE_TESTS COMMAND segment_tree_tests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_executable(fenwick_tree_tests do_tests.cpp fenwick_tree_tests.cpp)
target_link_libraries(fenwick_tree_tests PUBLIC source gtest)
add_test(NAME FENWICK_TREE_TESTS COMMAND fenwick_tree_tests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})