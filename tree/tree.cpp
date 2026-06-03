#include "tree.h"

#include <algorithm>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    Clear();
}

void BinarySearchTree::Insert(int value) {
    root = InsertRec(root, value);
}

bool BinarySearchTree::Search(int value) const {
    return SearchRec(root, value);
}

void BinarySearchTree::Remove(int value) {
    root = RemoveRec(root, value);
}

bool BinarySearchTree::Empty() const {
    return root == nullptr;
}

int BinarySearchTree::GetMin() const {
    BSTNode* node = FindMinNode(root);
    return node ? node->data : 0;
}

int BinarySearchTree::GetMax() const {
    BSTNode* current = root;
    while (current && current->right)
        current = current->right;
    return current ? current->data : 0;
}

int BinarySearchTree::Count() const {
    return CountRec(root);
}

BSTNode* BinarySearchTree::Root() const {
    return root;
}

int BinarySearchTree::Height() const {
    return HeightRec(root);
}

std::vector<int> BinarySearchTree::InOrder() const {
    std::vector<int> values;
    InOrderRec(root, values);
    return values;
}

std::vector<int> BinarySearchTree::PreOrder() const {
    std::vector<int> values;
    PreOrderRec(root, values);
    return values;
}

std::vector<int> BinarySearchTree::PostOrder() const {
    std::vector<int> values;
    PostOrderRec(root, values);
    return values;
}

void BinarySearchTree::Clear() {
    ClearRec(root);
    root = nullptr;
}

BSTNode* BinarySearchTree::InsertRec(BSTNode* node, int value) {
    if (node == nullptr)
        return new BSTNode(value);

    if (value < node->data)
        node->left = InsertRec(node->left, value);
    else if (value > node->data)
        node->right = InsertRec(node->right, value);

    return node;
}

bool BinarySearchTree::SearchRec(BSTNode* node, int value) const {
    if (node == nullptr)
        return false;
    if (value == node->data)
        return true;
    if (value < node->data)
        return SearchRec(node->left, value);
    return SearchRec(node->right, value);
}

BSTNode* BinarySearchTree::RemoveRec(BSTNode* node, int value) {
    if (node == nullptr)
        return node;

    if (value < node->data) {
        node->left = RemoveRec(node->left, value);
    } else if (value > node->data) {
        node->right = RemoveRec(node->right, value);
    } else {
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* temp = FindMinNode(node->right);
        node->data = temp->data;
        node->right = RemoveRec(node->right, temp->data);
    }
    return node;
}

BSTNode* BinarySearchTree::FindMinNode(BSTNode* node) const {
    BSTNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

int BinarySearchTree::CountRec(BSTNode* node) const {
    if (node == nullptr)
        return 0;
    return 1 + CountRec(node->left) + CountRec(node->right);
}

int BinarySearchTree::HeightRec(BSTNode* node) const {
    if (node == nullptr)
        return 0;
    int leftHeight = HeightRec(node->left);
    int rightHeight = HeightRec(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

void BinarySearchTree::InOrderRec(BSTNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    InOrderRec(node->left, values);
    values.push_back(node->data);
    InOrderRec(node->right, values);
}

void BinarySearchTree::PreOrderRec(BSTNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    values.push_back(node->data);
    PreOrderRec(node->left, values);
    PreOrderRec(node->right, values);
}

void BinarySearchTree::PostOrderRec(BSTNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    PostOrderRec(node->left, values);
    PostOrderRec(node->right, values);
    values.push_back(node->data);
}

void BinarySearchTree::ClearRec(BSTNode* node) {
    if (node == nullptr)
        return;
    ClearRec(node->left);
    ClearRec(node->right);
    delete node;
}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    Clear();
}

void AVLTree::Insert(int value) {
    root = InsertRec(root, value);
}

bool AVLTree::Search(int value) const {
    return SearchRec(root, value);
}

void AVLTree::Remove(int value) {
    root = RemoveRec(root, value);
}

bool AVLTree::Empty() const {
    return root == nullptr;
}

int AVLTree::Height() const {
    return GetHeight(root);
}

AVLNode* AVLTree::Root() const {
    return root;
}

int AVLTree::RootBalance() const {
    return GetBalance(root);
}

std::vector<int> AVLTree::InOrder() const {
    std::vector<int> values;
    InOrderRec(root, values);
    return values;
}

std::vector<int> AVLTree::PreOrder() const {
    std::vector<int> values;
    PreOrderRec(root, values);
    return values;
}

std::vector<int> AVLTree::PostOrder() const {
    std::vector<int> values;
    PostOrderRec(root, values);
    return values;
}

void AVLTree::Clear() {
    ClearRec(root);
    root = nullptr;
}

int AVLTree::GetHeight(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::GetBalance(AVLNode* node) const {
    if (!node)
        return 0;
    return GetHeight(node->left) - GetHeight(node->right);
}

AVLNode* AVLTree::RightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(GetHeight(y->left), GetHeight(y->right));
    x->height = 1 + std::max(GetHeight(x->left), GetHeight(x->right));

    return x;
}

AVLNode* AVLTree::LeftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(GetHeight(x->left), GetHeight(x->right));
    y->height = 1 + std::max(GetHeight(y->left), GetHeight(y->right));

    return y;
}

AVLNode* AVLTree::InsertRec(AVLNode* node, int value) {
    if (node == nullptr)
        return new AVLNode(value);

    if (value < node->data)
        node->left = InsertRec(node->left, value);
    else if (value > node->data)
        node->right = InsertRec(node->right, value);
    else
        return node;

    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && value < node->left->data)
        return RightRotate(node);

    if (balance < -1 && value > node->right->data)
        return LeftRotate(node);

    if (balance > 1 && value > node->left->data) {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}

AVLNode* AVLTree::MinValueNode(AVLNode* node) const {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

AVLNode* AVLTree::RemoveRec(AVLNode* node, int value) {
    if (!node)
        return node;

    if (value < node->data)
        node->left = RemoveRec(node->left, value);
    else if (value > node->data)
        node->right = RemoveRec(node->right, value);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node;
                return nullptr;
            }
            delete node;
            return temp;
        }

        AVLNode* temp = MinValueNode(node->right);
        node->data = temp->data;
        node->right = RemoveRec(node->right, temp->data);
    }

    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && GetBalance(node->left) >= 0)
        return RightRotate(node);

    if (balance > 1 && GetBalance(node->left) < 0) {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    if (balance < -1 && GetBalance(node->right) <= 0)
        return LeftRotate(node);

    if (balance < -1 && GetBalance(node->right) > 0) {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}

bool AVLTree::SearchRec(AVLNode* node, int value) const {
    if (node == nullptr)
        return false;
    if (value == node->data)
        return true;
    if (value < node->data)
        return SearchRec(node->left, value);
    return SearchRec(node->right, value);
}

void AVLTree::InOrderRec(AVLNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    InOrderRec(node->left, values);
    values.push_back(node->data);
    InOrderRec(node->right, values);
}

void AVLTree::PreOrderRec(AVLNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    values.push_back(node->data);
    PreOrderRec(node->left, values);
    PreOrderRec(node->right, values);
}

void AVLTree::PostOrderRec(AVLNode* node, std::vector<int>& values) const {
    if (node == nullptr)
        return;
    PostOrderRec(node->left, values);
    PostOrderRec(node->right, values);
    values.push_back(node->data);
}

void AVLTree::ClearRec(AVLNode* node) {
    if (node == nullptr)
        return;
    ClearRec(node->left);
    ClearRec(node->right);
    delete node;
}
