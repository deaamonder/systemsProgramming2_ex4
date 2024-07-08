#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Node {
public:
    T value;
    vector<Node<T>*> children;

    Node(const T& value) : value(value), children() {}

    T get_value() const { return value; }
    void add_child(Node<T>* child) { children.push_back(child); }
    vector<Node<T>*> get_children() {return children;}
};

#endif // NODE_HPP
