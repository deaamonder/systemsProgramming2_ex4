#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T, size_t K = 2>
class Tree {
private:
    Node<T>* root;

    void deleteTree(Node<T>* node);
public:
    Tree() : root(nullptr) {}
    ~Tree() { deleteTree(root); }

    void add_root(const Node<T>& node);
    void add_sub_node(const Node<T>& parent, const Node<T>& node);
    Node<T>* get_root(){return root;}

    //defining iterators
    class PreOrderIterator;
    class PostOrderIterator;
    class InOrderIterator;
    class bfsIterator;
    class dfsIterator;

    //begin-end function for pre/in/post order and bfs dfs.
    PreOrderIterator begin_pre_order() { return PreOrderIterator(root); }
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }
    PostOrderIterator begin_post_order() { return PostOrderIterator(root); }
    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr); }
    InOrderIterator begin_in_order() { return InOrderIterator(root); }
    InOrderIterator end_in_order() { return InOrderIterator(nullptr); }
    bfsIterator begin_bfs_scan() { return bfsIterator(root); }
    bfsIterator end_bfs_scan() { return bfsIterator(nullptr); }
    dfsIterator begin_dfs_scan() { return dfsIterator(root); }
    dfsIterator end_dfs_scan() { return dfsIterator(nullptr); }

    // friend ostream& operator<<(ostream& os, const Tree<T, K>& tree) {
    //     return os;
    // }
};

/*
* deleting the tree recursivly
*/
template <typename T, size_t K>
void Tree<T, K>::deleteTree(Node<T>* node) {
    if (node) {
        for (auto child : node->children) {
            deleteTree(child);
        }
        delete node;
    }
}

/*
* adding a root
*/
template <typename T, size_t K>
void Tree<T, K>::add_root(const Node<T>& node) {
    if (root) {
        root->value = node.value;
    } else {
        root = new Node<T>(node.value);
    }
}

/*
* adding a sub-node
*/
template <typename T, size_t K>
void Tree<T, K>::add_sub_node(const Node<T>& parent, const Node<T>& node) {
    queue<Node<T>*> q;
    q.push(root);
    while (!q.empty()) {
        Node<T>* curr_node = q.front();
        q.pop();
        if (curr_node->value == parent.value) {
            if (curr_node->children.size() < K) {
                Node<T>* new_node = new Node<T>(node.value);
                curr_node->add_child(new_node);
                return;
            }
            throw runtime_error("Parent node has maximum children");
        }
        for (auto child : curr_node->children) {
            if (child) q.push(child);
        }
    }
    throw runtime_error("Parent node not found");
}

//PreOrderIterator class
template <typename T, size_t K>
class Tree<T, K>::PreOrderIterator {
private:
    Node<T>* node;
    stack<Node<T>*> nodesStack;

    void preOrder(Node<T>* node);
public:
    PreOrderIterator(Node<T>* root);

    PreOrderIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const PreOrderIterator& other);
};

//implemnting PreOrderIterator function
/*
* constructor
*/
template <typename T, size_t K>
Tree<T, K>::PreOrderIterator::PreOrderIterator(Node<T>* root) : node(nullptr) {
    if (root) preOrder(root);
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    }
}

template <typename T, size_t K>
void Tree<T, K>::PreOrderIterator::preOrder(Node<T>* node) {
    if (node) {
        nodesStack.push(node);
        for (int i = node->children.size() - 1; i >= 0; --i) {
            preOrder(node->children[i]);
        }
    }
}

//implementing operators
template <typename T, size_t K>
typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::PreOrderIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) {
    return node != other.node;
}

//PostOrderIterator class
template <typename T, size_t K>
class Tree<T, K>::PostOrderIterator {
private:
    Node<T>* node;
    stack<Node<T>*> nodesStack;

    void postOrder(Node<T>* node);
public:
    PostOrderIterator(Node<T>* root);

    PostOrderIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const PostOrderIterator& other);
};

template <typename T, size_t K>
Tree<T, K>::PostOrderIterator::PostOrderIterator(Node<T>* root) : node(nullptr) {
    if (root) postOrder(root);
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    }
}

template <typename T, size_t K>
void Tree<T, K>::PostOrderIterator::postOrder(Node<T>* node) {
    if (node) {
        for (auto child : node->children) {
            postOrder(child);
        }
        nodesStack.push(node);
    }
}

template <typename T, size_t K>
typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::PostOrderIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) {
    return node != other.node;
}

//InOrderIterator class
template <typename T, size_t K>
class Tree<T, K>::InOrderIterator {
private:
    Node<T>* node;
    stack<Node<T>*> nodesStack;

    void inOrder(Node<T>* node);
public:
    InOrderIterator(Node<T>* root);

    InOrderIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const InOrderIterator& other);
};

template <typename T, size_t K>
Tree<T, K>::InOrderIterator::InOrderIterator(Node<T>* root) : node(nullptr) {
    if (root) inOrder(root);
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    }
}

template <typename T, size_t K>
void Tree<T, K>::InOrderIterator::inOrder(Node<T>* node) {
    if (node) {
        if (!node->children.empty()) inOrder(node->children[0]);
        nodesStack.push(node);
        for (size_t i = 1; i < node->children.size(); ++i) {
            inOrder(node->children[i]);
        }
    }
}

template <typename T, size_t K>
typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::InOrderIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) {
    return node != other.node;
}

//bfsIterator class
template <typename T, size_t K>
class Tree<T, K>::bfsIterator {
private:
    Node<T>* node;
    queue<Node<T>*> nodesQueue;

public:
    bfsIterator(Node<T>* root);

    bfsIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const bfsIterator& other);
};

template <typename T, size_t K>
Tree<T, K>::bfsIterator::bfsIterator(Node<T>* root) : node(nullptr) {
    if (root) nodesQueue.push(root);
    if (!nodesQueue.empty()) {
        node = nodesQueue.front();
        nodesQueue.pop();
    }
}

template <typename T, size_t K>
typename Tree<T, K>::bfsIterator& Tree<T, K>::bfsIterator::operator++() {
    if (!nodesQueue.empty()) {
        Node<T>* curr_node = nodesQueue.front();
        nodesQueue.pop();
        for (auto child : curr_node->children) {
            if (child) nodesQueue.push(child);
        }
        if (!nodesQueue.empty()) {
            node = nodesQueue.front();
            nodesQueue.pop();
        } else {
            node = nullptr;
        }
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::bfsIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::bfsIterator::operator!=(const bfsIterator& other) {
    return node != other.node;
}

//dfsIterator class
template <typename T, size_t K>
class Tree<T, K>::dfsIterator {
private:
    Node<T>* node;
    stack<Node<T>*> nodesStack;

public:
    dfsIterator(Node<T>* root);

    dfsIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const dfsIterator& other);
};

template <typename T, size_t K>
Tree<T, K>::dfsIterator::dfsIterator(Node<T>* root) : node(nullptr) {
    if (root) nodesStack.push(root);
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
    }
}

template <typename T, size_t K>
typename Tree<T, K>::dfsIterator& Tree<T, K>::dfsIterator::operator++() {
    if (!nodesStack.empty()) {
        node = nodesStack.top();
        nodesStack.pop();
        for (int i = node->children.size() - 1; i >= 0; --i) {
            nodesStack.push(node->children[i]);
        }
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::dfsIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::dfsIterator::operator!=(const dfsIterator& other) {
    return node != other.node;
}

#endif // TREE_HPP
