#ifndef CLIST_H
#define CLIST_H

// Лабораторна 14: кільцевий однозв'язний список
struct CNode {
    int data;
    CNode* next;

    explicit CNode(int value);
};

CNode* CListInsertBack(CNode* head, int value);
void CListDisplayCircular(const CNode* head);
void CListDeleteAll(CNode*& head);

#endif
