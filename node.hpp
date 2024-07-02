#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Node {
private:
    T value;
    vector<Node<T>*> nodes; // pointer to the node children

public:
    Node(T val) : value(val) {}

    T get_value() {
        return value;
    }

    void add_child(Node<T>* child) {
        nodes.push_back(child);
    }

    vector<Node<T>*> get_children() {
        return nodes;
    }
};
