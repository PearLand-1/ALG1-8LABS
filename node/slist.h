#ifndef SLIST_H
#define SLIST_H

// Лабораторна 13: однозв'язний список
struct SNode {
    int data;
    SNode* next;

    explicit SNode(int value);
};

SNode* SListInsertHead(SNode* head, int value);
SNode* SListInsertBack(SNode* head, int value);
void SListDisplay(const SNode* head);
int SListCount(const SNode* head);
const SNode* SListSearch(const SNode* head, int value);
SNode* SListDeleteByValue(SNode* head, int value);
SNode* SListReverse(SNode* head);
void SListDeleteAll(SNode*& head);

#endif
