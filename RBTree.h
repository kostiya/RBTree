#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H

#include <iostream>
#include <random>
#include <functional>

using std::cout;
using std::endl;
namespace structure{
    enum Location{leftNode, rightNode};
    enum Color{black, red};

    template <class T>
    class Node{
        template <class R>friend class RBTree;
    protected:
        Node<T>* p;
        Node<T>* left;
        Node<T>* right;
        T key;
        Color color=red;

        static std::random_device rd;
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution;
        explicit  Node(T& key,
                       Node* p,
                       Node* left = nullptr,
                       Node* right = nullptr,
                       Color color=red);
    public:
        explicit  Node(T& key);
        ~Node();
        Node<T>* getParent() const;
        Node<T>* getLeft() const;
        Node<T>* getRight() const;
        const T& getKey() const;
        Color getColor() const{
            return color;
        }
        Node<T>* minimum();
        Node<T>* maximum();
        Node<T>* successor();
        Node<T>* predecessor();
        Node<T>* getRoot();
        //Node<T>* insert(T& key);
        //bool remove(T& key);
        //bool remove();
        Node<T>* find(T& key);
        //bool rotateLeft();
        //bool rotateRight();
    };


    template <class T>
    class RBTree{
    protected:
        Node<T>* root;
        void RBInsertFixup(Node<T>* z);
    public:
        explicit RBTree(T& key){
            root = new Node<T>(key);
            root->color = black;
        };
        RBTree(){
            root = nullptr;
        };
        Node<T>* getRoot(){
            return root;
        }
        ~RBTree(){
            if(root)
                delete root;
        }
        Node<T>* insert(T& key);
        Node<T>* transplant(Node<T>* u, Node<T>* v);
        bool remove(T& key);
        Node<T>* find(T& key){
            root->find(key);
        }
        bool rotateLeft(Node<T>* x);
        bool rotateRight(Node<T>* y);
    };


    void printNode(Node<int>* node, int depth=0);

    template <class T>
    Node<T>::Node(T& key,
                  Node* p,
                  Node* left,
                  Node* right,
                  Color color):key(key),
                               p(p),
                               left(left),
                               right(right),
                               color(color){};

    template <class T>
    Node<T>::Node(T& key):Node(key, nullptr){};

    template <class T>
    Node<T>::~Node() {
        delete right;
        delete left;

        if(p != nullptr){
            if(p->left==this)
                p->left= nullptr;
            else
                p->right= nullptr;
        }
    }
    template <class T>
    std::random_device Node<T>::rd;

    template <class T>
    std::default_random_engine Node<T>::generator(Node<T>::rd());

    template <class T>
    std::uniform_int_distribution<int> Node<T>::distribution(0,1);



    template <class T>
    Node<T>* Node<T>::getRoot(){
        Node* node = this;
        while(node->p != nullptr)
            node = node->p;
        return node;
    }
    template <class T>
    Node<T>* Node<T>::getParent() const{
        return this->p;
    }
    template <class T>
    Node<T>* Node<T>::getLeft() const{
        return this->left;
    }
    template <class T>
    Node<T>* Node<T>::getRight() const{
        return this->right;
    }
    template <class T>
    const T& Node<T>::getKey() const{
        return this->key;
    }
    template <class T>
    Node<T>* RBTree<T>::insert(T& key){
        Node<T>* current_node = this->getRoot();
        Node<T>* previous_node = nullptr;
        if(current_node == nullptr){
            root = new Node<T>(key, nullptr, nullptr, nullptr,black);
            return root;
        }
        Location side = rightNode;
        while (current_node != nullptr){
            if(key==current_node->key)
                return nullptr;
            else if(key < current_node->key){
                previous_node = current_node;
                current_node = current_node->left;
                side = leftNode;
            } else{
                previous_node = current_node;
                current_node = current_node->right;
                side = rightNode;
            }
        }
        if(side == rightNode){
            previous_node->right = new Node<T>(key,previous_node);
            RBInsertFixup(previous_node->right);
            return previous_node->right;
        } else{
            previous_node->left = new Node<T>(key,previous_node);
            RBInsertFixup(previous_node->left);
            return previous_node->left;
        }
    }

    template <class T>
    void RBTree<T>::RBInsertFixup(Node<T>* z){
        while (z->p->color == red) {
            if (z->p == z->p->p->left) {
                Node<T> *y = z->p->p->right;
                if (y && y->color == red) {
                    z->p->color = black;
                    y->color = black;
                    z->p->p->color = red;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        rotateLeft(z);
                    }
                    z->p->color = black;
                    z->p->p->color = red;
                    rotateRight(z->p->p);
                }
            } else {
                Node<T> *y = z->p->p->left;
                if (y && y->color == red) {
                    z->p->color = black;
                    y->color = black;
                    z->p->p->color = red;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rotateRight(z);
                    }
                    z->p->color = black;
                    z->p->p->color = red;
                    rotateLeft(z->p->p);
                }
            }
        }
        root->color = black;
    }

    template <class T>
    Node<T>* RBTree<T>::transplant(Node<T> *u, Node<T> *v) {
        if(u==root)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else u->p->right = v;

        v->p = u->p;
        u->p= nullptr;
        u->right = nullptr;
        u->left = nullptr;
    }

    template <class T>
    bool RBTree<T>::remove(T& key) {

        Node<T>* z = find(key);
        if(!z)
            return false;

    }


    template <class T>
    Node<T>* Node<T>::find(T& key){
        Node* current_node = this->getRoot();
        while (current_node != nullptr){
            if(key==current_node->key)
                return current_node;
            else if(key < current_node->key){
                current_node = current_node->left;
            } else{
                current_node = current_node->right;
            }
        }
        return nullptr;
    }
    template <class T>
    Node<T>* Node<T>::minimum(){
        Node* current_node = this;
        while(current_node->left != nullptr)
            current_node = current_node->left;
        return current_node;
    }
    template <class T>
    Node<T>* Node<T>::maximum(){
        Node* current_node = this;
        while(current_node->right != nullptr)
            current_node = current_node->right;
        return current_node;
    }

    template <class T>
    Node<T>* Node<T>::successor(){
        if(right != nullptr)
            return right->minimum();
        Node* current = this;
        Node* parent = this->p;
        while(parent != nullptr && current== parent->right){
            current = parent;
            parent = parent->p;
        }
        return parent;
    }
    template <class T>
    Node<T>* Node<T>::predecessor(){
        if(left != nullptr)
            return left->maximum();
        Node* current = this;
        Node* parent = p;
        while(parent != nullptr && current== parent->left){
            current = parent;
            parent = parent->p;
        }
        return parent;
    }

    template <class T>
    bool RBTree<T>::rotateLeft(Node<T>* x) {
        if(x->right == nullptr)
            return false;
        Node<T>* y = x->right;
        x->right = y->left;
        if(y->left != nullptr)
            y->left->p = x;
        y->p = x->p;
        if(x->p == nullptr){
            root = y;
        } else if (x == x->p->left){
            x->p->left = y;
        } else{
            x->p->right = y;
        }
        y->left = x;
        x->p = y;
    }

    template <class T>
    bool RBTree<T>::rotateRight(Node<T>* y) {
        if(y->left == nullptr)
            return false;
        Node<T>* x = y->left;
        y->left = x->right;
        if(x->right != nullptr)
            x->right->p = y;
        x->p = y->p;
        if(y->p == nullptr){
            x=root;
        } else if (y == y->p->left){
            y->p->left = x;
        } else{
            y->p->right = x;
        }
        x->right  = y;
        y->p = x;
    }


    void printNode(Node<int>* node, int depth){
        if(node == nullptr)
            return;
        printNode(node->getLeft() ,depth+1);
        for(int i = 0; i < depth*4;i++)
            cout << " ";
        cout << node->getKey() << (node->getColor() ? " Red":" Black") << endl;
        printNode(node->getRight(),depth+1);
        if(depth==0)
            cout << "--------------------" << endl;
    }

}



#endif //RBTREE_RBTREE_H
