#ifndef TREE_H
#define TREE_H

#include <vector>

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void Insert(int value);
    bool Search(int value) const;
    void Remove(int value);
    bool Empty() const;
    BSTNode* Root() const;
    int GetMin() const;
    int GetMax() const;
    int Count() const;
    int Height() const;

    std::vector<int> InOrder() const;
    std::vector<int> PreOrder() const;
    std::vector<int> PostOrder() const;

    void Clear();

private:
    BSTNode* root;

    BSTNode* InsertRec(BSTNode* node, int value);
    bool SearchRec(BSTNode* node, int value) const;
    BSTNode* RemoveRec(BSTNode* node, int value);
    BSTNode* FindMinNode(BSTNode* node) const;
    int CountRec(BSTNode* node) const;
    int HeightRec(BSTNode* node) const;
    void InOrderRec(BSTNode* node, std::vector<int>& values) const;
    void PreOrderRec(BSTNode* node, std::vector<int>& values) const;
    void PostOrderRec(BSTNode* node, std::vector<int>& values) const;
    void ClearRec(BSTNode* node);
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void Insert(int value);
    bool Search(int value) const;
    void Remove(int value);
    bool Empty() const;
    AVLNode* Root() const;
    int Height() const;
    int RootBalance() const;

    std::vector<int> InOrder() const;
    std::vector<int> PreOrder() const;
    std::vector<int> PostOrder() const;

    void Clear();

private:
    AVLNode* root;

    int GetHeight(AVLNode* node) const;
    int GetBalance(AVLNode* node) const;
    AVLNode* RightRotate(AVLNode* y);
    AVLNode* LeftRotate(AVLNode* x);
    AVLNode* InsertRec(AVLNode* node, int value);
    AVLNode* RemoveRec(AVLNode* node, int value);
    AVLNode* MinValueNode(AVLNode* node) const;
    bool SearchRec(AVLNode* node, int value) const;
    void InOrderRec(AVLNode* node, std::vector<int>& values) const;
    void PreOrderRec(AVLNode* node, std::vector<int>& values) const;
    void PostOrderRec(AVLNode* node, std::vector<int>& values) const;
    void ClearRec(AVLNode* node);
};

#endif