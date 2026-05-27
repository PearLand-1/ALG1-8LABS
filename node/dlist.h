#ifndef DLIST_H
#define DLIST_H

// Лабораторна 14: двозв'язний список
struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    explicit DNode(int value);
};

DNode* DListInsertBack(DNode* head, int value);
void DListDisplayForward(const DNode* head);
void DListDisplayReverse(const DNode* head);
DNode* DListDeleteFirst(DNode* head);
void DListDeleteAll(DNode*& head);

#endif
