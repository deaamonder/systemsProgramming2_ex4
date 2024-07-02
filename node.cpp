#include <iostream>
#include "node.hpp"

using namespace std;

template<typename T> 
T Node<T>::get_value(){
    return this->value;
}