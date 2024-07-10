#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <functional>

using namespace std;

template <typename T, size_t K = 2>
class Tree {
private:
    Node<T>* root; //poitner to the root of the tree

    void deleteTree(Node<T>* node); // function to delete the tree recursivley 
public:
    Tree() : root(nullptr) {}
    ~Tree() { deleteTree(root); }

    /*
     * function to add (set) the root of tree. 
     */
    void add_root(const Node<T>& node);
    /*
     * function to add a sub node to some node in the tree. 
     */
    void add_sub_node(const Node<T>& parent, const Node<T>& node);
    /*
    * root getter 
    */
    Node<T>* get_root(){return root;}

    //defining iterators
    class PreOrderIterator;
    class PostOrderIterator;
    class InOrderIterator;
    class bfsIterator;
    class dfsIterator;
    class MinHeapIterator;

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
    MinHeapIterator myHeap() { return MinHeapIterator(root); }

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
    stack<Node<T>*> nodesStack; //impleminting the pre order iterator using stack data structure
    /*
    * private function to add nodes in the pre order way (root-left-right).
    */
    void preOrder(Node<T>* node);
public:
    PreOrderIterator(Node<T>* root);
    //operators
    PreOrderIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const PreOrderIterator& other);
};

//implemnting PreOrderIterator function
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
    stack<Node<T>*> nodesStack;//as the pre order iterator also here i used stack
    /*
    * private function to add nodes in the post order way (left-right-root).
    */
    void postOrder(Node<T>* node);
public:
    PostOrderIterator(Node<T>* root);
    //operators
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
    stack<Node<T>*> nodesStack;//as the pre/post order i used stack here
    /*
    * private function to add nodes in the in order way (left-root-right).
    */
    void inOrder(Node<T>* node);
public:
    InOrderIterator(Node<T>* root);
    //operators
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
    queue<Node<T>*> nodesQueue;//in the bfs iterator I used the queue data structure 

public:
    bfsIterator(Node<T>* root);
    //operators
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
    stack<Node<T>*> nodesStack;//in the dfs I used the stack data structure

public:
    dfsIterator(Node<T>* root);
    //operators
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

// MinHeapIterator class
template <typename T, size_t K>
class Tree<T, K>::MinHeapIterator {
private:
    Node<T>* node;
    //using preority queue 
    priority_queue<Node<T>*, vector<Node<T>*>, function<bool(Node<T>*, Node<T>*)>> minHeap;

public:
    MinHeapIterator(Node<T>* root);
    //operators
    MinHeapIterator& operator++();
    Node<T>* operator*();
    bool operator!=(const MinHeapIterator& other);
};

/**
 * in the constructor of the min heap iterator i used a lambda function(anonymous function)
 * which is basicly compare between the "left-hand" side node and the "right-hand"
 * side node .
 */
template <typename T, size_t K>
Tree<T, K>::MinHeapIterator::MinHeapIterator(Node<T>* root) : node(nullptr), minHeap([](Node<T>* lhs, Node<T>* rhs) {
    return lhs->value > rhs->value;
}) {
    if (root) minHeap.push(root);
    if (!minHeap.empty()) {
        node = minHeap.top();
        minHeap.pop();
    }
}

template <typename T, size_t K>
typename Tree<T, K>::MinHeapIterator& Tree<T, K>::MinHeapIterator::operator++() {
    if (!minHeap.empty()) {
        for (auto child : node->children) {
            if (child) minHeap.push(child);
        }
        if (!minHeap.empty()) {
            node = minHeap.top();
            minHeap.pop();
        } else {
            node = nullptr;
        }
    } else {
        node = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::MinHeapIterator::operator*() {
    return node;
}

template <typename T, size_t K>
bool Tree<T, K>::MinHeapIterator::operator!=(const MinHeapIterator& other) {
    return node != other.node;
}

#endif // TREE_HPP
