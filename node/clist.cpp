/* =======================================================

    Алгоритми і структура данних
    Лабораторна робота №14 (кільцевий список)
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "clist.h"
#include "../MyLib.h"

#include <iostream>

using namespace std;

CNode::CNode(int value) : data(value), next(nullptr) {}

CNode* CListInsertBack(CNode* head, int value)
{
    CNode* newNode = new CNode(value);
    if (head == nullptr)
    {
        newNode->next = newNode;
        return newNode;
    }

    CNode* current = head;
    while (current->next != head)
        current = current->next;

    current->next = newNode;
    newNode->next = head;
    return head;
}

void CListDisplayCircular(const CNode* head)
{
    if (head == nullptr)
    {
        Log(FromCustomFormatToString("<magenta>(порожній список)</magenta>"));
        return;
    }

    const CNode* current = head;
    int i = 0;
    cout << "\n";
    do
    {
        cout << colors[i % 9] << current->data << resetText;
        current = current->next;
        ++i;
        if (current != head)
            cout << " -> ";
    } while (current != head);
    cout << " -> " << cyan << "(голова)" << resetColor << "\n";
}

void CListDeleteAll(CNode*& head)
{
    if (head == nullptr)
        return;

    if (head->next == head)
    {
        delete head;
        head = nullptr;
        return;
    }

    CNode* current = head->next;
    while (current != head)
    {
        CNode* next = current->next;
        delete current;
        current = next;
    }
    delete head;
    head = nullptr;
}
