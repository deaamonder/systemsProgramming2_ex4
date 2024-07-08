#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"
#include <iostream>
#include <sstream>

using namespace std;

//testing Node class
TEST_CASE("test add_child") {
    Node<int> n(5);
    Node<int> child(6);
    n.add_child(&child);
    vector<Node<int>*> nodes = n.get_children();
    CHECK(nodes[0] == &child);
}

//testing Tree class
TEST_CASE("test add_root and add_sub_node") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    vector<Node<int>*> children = tree.begin_bfs_scan().operator*()->get_children();
    CHECK(children.size() == 2);
    CHECK(children[0]->get_value() == 2);
    CHECK(children[1]->get_value() == 3);
}

TEST_CASE("test PreOrderIterator") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    auto it = tree.begin_pre_order();
    CHECK((*it)->get_value() == 1);
    ++it;
    CHECK((*it)->get_value() == 2);
    ++it;
    CHECK((*it)->get_value() == 3);
}

TEST_CASE("test InOrderIterator") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    auto it = tree.begin_in_order();
    CHECK((*it)->get_value() == 2);
    ++it;
    CHECK((*it)->get_value() == 1);
    ++it;
    CHECK((*it)->get_value() == 3);
}

TEST_CASE("test PostOrderIterator") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    auto it = tree.begin_post_order();
    CHECK((*it)->get_value() == 2);
    ++it;
    CHECK((*it)->get_value() == 3);
    ++it;
    CHECK((*it)->get_value() == 1);
}

TEST_CASE("test bfsIterator") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    auto it = tree.begin_bfs_scan();
    CHECK((*it)->get_value() == 1);
    ++it;
    CHECK((*it)->get_value() == 2);
    ++it;
    CHECK((*it)->get_value() == 3);
}

TEST_CASE("test dfsIterator") {
    Tree<int> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    auto it = tree.begin_dfs_scan();
    CHECK((*it)->get_value() == 1);
    ++it;
    CHECK((*it)->get_value() == 2);
    ++it;
    CHECK((*it)->get_value() == 3);
}

//testing Complex class
TEST_CASE("test Complex class") {
    Complex c1(1, 2);
    Complex c2(3, 4);

    CHECK((c1 + c2) == Complex(4, 6));
    CHECK((c1 - c2) == Complex(-2, -2));
    CHECK((c1 * c2) == Complex(-5, 10));
    CHECK((c1 / c2) == Complex(0.44, 0.08));

    stringstream ss;
    ss << c1;
    CHECK(ss.str() == "1 + 2i");
}
