#include <iostream>
#include <random>
#include <functional>
#include "RBTree.h"
using std::cout;
using std::endl;
using structure::Node;
using structure::printNode;

int main() {
    int num;
    num = 4;
    structure::RBTree <int> tree1(num);
    tree1.insert(num);
    num = 6;
    tree1.insert(num);
    num = 2;
    tree1.insert(num);
    num = 1;
    tree1.insert(num);
    num = 7;
    tree1.insert(num);
    num = 3;
    tree1.insert(num);
    num = 5;
    tree1.insert(num);
    printNode(tree1.getRoot());
    /*tree1.getRoot().rotateLeft();
    printNode(tree1.getRoot());
    num = 4;
    tree1.remove(num);
    printNode(tree1.getRoot());
    num = 5;
    tree1.remove(num);
    printNode(tree1.getRoot());
    num = 6;
    tree1.remove(num);
    printNode(tree1.getRoot());
    Node<int>* node = tree1.minimum();
    while(node != nullptr){
        cout << node->getKey() << " ";
        node = node->successor();
    }
    cout << endl;*/
    return 0;
}