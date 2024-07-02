#include <iostream>
#include <stack>
#include <queue>
#include "node.hpp"

using namespace std;

template<typename T>
class Tree {
private:
    Node<T>* root;
    int numOfChildren;

public:
    //default constructor
    Tree() : root(nullptr), numOfChildren(2) {}

    //destructor
    ~Tree();

    //regular constructor
    Tree(int numOfChildren) : root(nullptr), numOfChildren(numOfChildren) {}

    //function to add a root
    void add_root(Node<T> node) {
        root = node;
    }

    //function to add a sub node to a node
    void add_sub_node(Node<T> parent_node, Node<T> added_node) {
        parent_node->add_child(added_node);
    }

    //pre order iterator
    class preOrderIterator {
    private:
        stack<Node<T>*> nodes;
    public:
        preOrderIterator(Node<T>* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        preOrderIterator& operator++() {
            Node<T>* node = nodes.top();
            nodes.pop();
            auto children = node->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    //begin and end functions for pre-order
    preOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    preOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    //in order iterator
    class inOrderIterator {
    private:
        stack<Node<T>*> nodes;
        void push_left(Node<T>* node) {
            while (node) {
                nodes.push(node);
                auto children = node->get_children();
                if (!children.empty()) {
                    node = children[0];
                } else {
                    node = nullptr;
                }
            }
        }
    public:
        inOrderIterator(Node<T>* root) {
            push_left(root);
        }

        bool operator!=(const InOrderIterator& other) const {
            return !nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        inOrderIterator& operator++() {
            Node<T>* node = nodes.top();
            nodes.pop();
            auto children = node->get_children();
            if (children.size() > 1) {
                push_left(children[1]);
            }
            return *this;
        }
    };

    //begin and end functions for in-order
    inOrderIterator begin_in_order() {
        return inOrderIterator(root);
    }

    inOrderIterator end_in_order() {
        return inOrderIterator(nullptr);
    }

    //post order iterator
    class postOrderIterator {
    private:
        stack<Node<T>*> nodes;
        Node<T>* last_visited;
        void push_left_most(Node<T>* node) {
            while (node) {
                nodes.push(node);
                auto children = node->get_children();
                if (!children.empty()) {
                    node = children[0];
                } else {
                    node = nullptr;
                }
            }
        }
    public:
        postOrderIterator(Node<T>* root) : last_visited(nullptr) {
            push_left_most(root);
        }

        bool operator!=(const postOrderIterator& other) const {
            return !nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        postOrderIterator& operator++() {
            Node<T>* node = nodes.top();
            if (!node->get_children().empty() && last_visited != node->get_children().back()) {
                push_left_most(node->get_children().back());
            } else {
                nodes.pop();
                last_visited = node;
            }
            return *this;
        }
    };

    //begin and end functions for post-order
    postOrderIterator begin_post_order() {
        return postOrderIterator(root);
    }

    postOrderIterator end_post_order() {
        return postOrderIterator(nullptr);
    }

    // BFS iterator
    class bfsIterator {
    private:
        queue<Node<T>*> nodes;
    public:
        bfsIterator(Node<T>* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.front();
        }

        bfsIterator& operator++() {
            Node<T>* node = nodes.front();
            nodes.pop();
            auto children = node->get_children();
            for (auto child : children) {
                nodes.push(child);
            }
            return *this;
        }
    };

    //begin and end functions for BFS
    bfsIterator begin_bfs() {
        return bfsIterator(root);
    }

    bfsIterator end_bfs() {
        return bfsIterator(nullptr);
    }

    //dfs iterator
    class dfsIterator {
    private:
        stack<Node<T>*> nodes;
    public:
        dfsIterator(Node<T>* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const DFSIterator& other) const {
            return !nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        dfsIterator& operator++() {
            Node<T>* node = nodes.top();
            nodes.pop();
            auto children = node->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    //begin and end functions for DFS
    dfsIterator begin_dfs() {
        return dfsIterator(root);
    }

    dfsIterator end_dfs() {
        return dfsIterator(nullptr);
    }
};