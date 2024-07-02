#include <iostream>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

template<typename T>
Tree<T>::~Tree(){
    if(this->root != nullptr){
        delete root;
    }
    //delete each node , i do it this way because we have k children for each node
    for(int i=0; i<this.node.nodes.size(); i++){
        delete this.node.nodes[i];
    }
}

template<typename T>
void Tree<T>::add_root(Node<T> node){
    this->root = node;
}

template<typename T>
void Tree<T>::add_sub_node(Node<T> parent_node, Node<T> added_node){
    if((!parent_node == null) && (!added_node==null)){
        parent_node.nodes->push_back(added_node);
    }
}