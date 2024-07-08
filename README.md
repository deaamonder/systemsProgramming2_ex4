# Tree and Complex Number Library
@deaamonder
systems programming 2 , ariel university 

This C++ library provides implementations for a generic tree data structure (`Tree`) and a complex number class (`Complex`). It includes various traversal iterators for the tree structure and supports operations typical of a tree-like data structure, such as adding roots and sub-nodes, and traversing in different orders.

## Files

### `node.hpp`

Defines the `Node` class, which represents a node in the tree. Each node can store a value of type `T` and maintain children nodes in a vector.

### `tree.hpp`

Defines the `Tree` class template, which implements a generic tree structure using nodes from `node.hpp`. It includes methods for adding roots and sub-nodes, and various iterators (`PreOrderIterator`, `PostOrderIterator`, `InOrderIterator`, `bfsIterator`, `dfsIterator`) for different traversal orders.

### `complex.hpp`

Defines the `Complex` class, which represents a complex number with real and imaginary parts. It includes arithmetic operations such as addition, subtraction, multiplication, division, and comparison.

### `Demo.cpp`

Demonstrates the usage of the `Tree` and `Complex` classes. It includes a graphical demo using SFML to visualize a tree of complex numbers.

### `test.cpp`

Contains unit tests using the `doctest` framework to verify the functionalities of the `Node` and `Tree` classes, including iterators.

## Usage

To use this library, include the necessary header files (`node.hpp`, `tree.hpp`, `complex.hpp`) in your C++ project. Instantiate the `Tree` class with the desired data type (e.g., `Tree<int>` or `Tree<Complex>`), add nodes using `add_root` and `add_sub_node` methods, and iterate over the tree using the provided iterators.

Example usage for a tree of complex numbers:

```cpp
#include "tree.hpp"
#include "complex.hpp"

int main() {
    // Create a tree of complex numbers
    Node<Complex> root_node(Complex(1.1, 2.2));
    Tree<Complex> tree;
    tree.add_root(root_node);
    // Add sub-nodes...
    
    // Iterate over the tree
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        // Access node value: (*node)->get_value()
    }
    
    return 0;
}
