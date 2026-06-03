/* =======================================================

    Лабораторні роботи №15-17
    Лінійні динамічні структури даних
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "mainStack.h"
#include "../MyLib.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

struct PriorityNode {
    int data;
    int priority;
    PriorityNode* next;
    PriorityNode(int val, int pr) : data(val), priority(pr), next(nullptr) {}
};

struct DequeNode {
    int data;
    DequeNode* next;
    DequeNode* prev;
    DequeNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DynamicStack {
private:
    Node* topNode;
public:
    DynamicStack() : topNode(nullptr) {}
    ~DynamicStack() { clear(); }

    bool isEmpty() const { return topNode == nullptr; }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) return numeric_limits<int>::min();
        Node* temp = topNode;
        int value = temp->data;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    int peek() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return topNode->data;
    }

    void clear() {
        while (!isEmpty())
            pop();
    }

    bool findElement(int val) const {
        Node* curr = topNode;
        while (curr) {
            if (curr->data == val)
                return true;
            curr = curr->next;
        }
        return false;
    }

    int sum() const {
        int total = 0;
        Node* curr = topNode;
        while (curr) {
            total += curr->data;
            curr = curr->next;
        }
        return total;
    }

    double average() const {
        if (isEmpty()) return 0.0;
        int total = 0;
        int count = 0;
        Node* curr = topNode;
        while (curr) {
            total += curr->data;
            count++;
            curr = curr->next;
        }
        return static_cast<double>(total) / count;
    }

    void display() const {
        if (isEmpty()) {
            cout << "<yellow>Стек порожній.</yellow>\n";
            return;
        }
        cout << "Стек (верх -> дно): ";
        Node* curr = topNode;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) {
            LogError("Не вдалося відкрити файл для запису.");
            return;
        }
        Node* curr = topNode;
        while (curr) {
            out << curr->data << "\n";
            curr = curr->next;
        }
        out.close();
        LogSuccess("Стек збережено у файл.");
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            LogError("Не вдалося відкрити файл для зчитування.");
            return;
        }
        vector<int> values;
        int value;
        while (in >> value) {
            values.push_back(value);
        }
        in.close();
        clear();
        for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i)
            push(values[i]);
        LogSuccess("Стек завантажено з файлу.");
    }
};

class ListQueue {
private:
    Node* front;
    Node* rear;
public:
    ListQueue() : front(nullptr), rear(nullptr) {}
    ~ListQueue() { clear(); }

    bool isEmpty() const { return front == nullptr; }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) return numeric_limits<int>::min();
        Node* temp = front;
        int value = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return value;
    }

    int peek() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return front->data;
    }

    int minimum() const {
        if (isEmpty()) return numeric_limits<int>::max();
        int minVal = numeric_limits<int>::max();
        Node* curr = front;
        while (curr) {
            minVal = min(minVal, curr->data);
            curr = curr->next;
        }
        return minVal;
    }

    int maximum() const {
        if (isEmpty()) return numeric_limits<int>::min();
        int maxVal = numeric_limits<int>::min();
        Node* curr = front;
        while (curr) {
            maxVal = max(maxVal, curr->data);
            curr = curr->next;
        }
        return maxVal;
    }

    void clear() {
        while (!isEmpty())
            dequeue();
    }

    void display() const {
        if (isEmpty()) {
            cout << "<yellow>Черга порожня.</yellow>\n";
            return;
        }
        cout << "Черга (front -> rear): ";
        Node* curr = front;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

class CircularQueue {
private:
    vector<int> data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;
public:
    explicit CircularQueue(int cap) : data(cap), capacity(cap), frontIndex(0), rearIndex(0), count(0) {}

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }

    void enqueue(int val) {
        if (isFull()) {
            LogError("Кільцева черга заповнена.");
            return;
        }
        data[rearIndex] = val;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    int dequeue() {
        if (isEmpty()) return numeric_limits<int>::min();
        int value = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return value;
    }

    int peek() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return data[frontIndex];
    }

    int minimum() const {
        if (isEmpty()) return numeric_limits<int>::max();
        int minVal = numeric_limits<int>::max();
        int idx = frontIndex;
        for (int i = 0; i < count; ++i) {
            minVal = min(minVal, data[idx]);
            idx = (idx + 1) % capacity;
        }
        return minVal;
    }

    int maximum() const {
        if (isEmpty()) return numeric_limits<int>::min();
        int maxVal = numeric_limits<int>::min();
        int idx = frontIndex;
        for (int i = 0; i < count; ++i) {
            maxVal = max(maxVal, data[idx]);
            idx = (idx + 1) % capacity;
        }
        return maxVal;
    }

    void display() const {
        if (isEmpty()) {
            cout << "<yellow>Кільцева черга порожня.</yellow>\n";
            return;
        }
        cout << "Кільцева черга: ";
        int idx = frontIndex;
        for (int i = 0; i < count; ++i) {
            cout << data[idx];
            if (i < count - 1) cout << " -> ";
            idx = (idx + 1) % capacity;
        }
        cout << "\n";
    }
};

class PriorityQueue {
private:
    PriorityNode* head;
public:
    PriorityQueue() : head(nullptr) {}
    ~PriorityQueue() { clear(); }

    bool isEmpty() const { return head == nullptr; }

    void enqueue(int val, int pr) {
        PriorityNode* newNode = new PriorityNode(val, pr);
        if (isEmpty() || head->priority < pr) {
            newNode->next = head;
            head = newNode;
            return;
        }
        PriorityNode* curr = head;
        while (curr->next != nullptr && curr->next->priority >= pr) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    int dequeue() {
        if (isEmpty()) return numeric_limits<int>::min();
        PriorityNode* temp = head;
        int value = head->data;
        head = head->next;
        delete temp;
        return value;
    }

    int peekHighest() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return head->data;
    }

    void display() const {
        if (isEmpty()) {
            cout << "<yellow>Пріоритетна черга порожня.</yellow>\n";
            return;
        }
        cout << "Пріоритетна черга (від найвищого пріоритету): ";
        PriorityNode* curr = head;
        while (curr) {
            cout << "(" << curr->data << ", pr=" << curr->priority << ")";
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }

    void clear() {
        while (!isEmpty()) {
            PriorityNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Deque {
private:
    DequeNode* front;
    DequeNode* rear;
public:
    Deque() : front(nullptr), rear(nullptr) {}
    ~Deque() { clear(); }

    bool isEmpty() const { return front == nullptr; }

    void pushFront(int val) {
        DequeNode* newNode = new DequeNode(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void pushBack(int val) {
        DequeNode* newNode = new DequeNode(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    int popFront() {
        if (isEmpty()) return numeric_limits<int>::min();
        DequeNode* temp = front;
        int value = front->data;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return value;
    }

    int popBack() {
        if (isEmpty()) return numeric_limits<int>::min();
        DequeNode* temp = rear;
        int value = rear->data;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        return value;
    }

    int peekFront() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return front->data;
    }

    int peekBack() const {
        if (isEmpty()) return numeric_limits<int>::min();
        return rear->data;
    }

    void clear() {
        while (!isEmpty())
            popFront();
    }

    void display() const {
        if (isEmpty()) {
            cout << "<yellow>Дек порожній.</yellow>\n";
            return;
        }
        cout << "Дек (front -> back): ";
        DequeNode* curr = front;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " <-> ";
            curr = curr->next;
        }
        cout << "\n";
    }
};

static void ShowHeader(const string& title, const string& subtitle) {
    ClearScreen();
    cout << FromCustomFormatToString(
        "<magenta><i><u>" + title + "</u></i></magenta>\n"
        "<b>Виконав:</b> <i>Чорноус Сергій ІПЗ-22</i>\n"
        "<cyan>" + subtitle + "</cyan>\n");
}

static void RunStackMenu() {
    DynamicStack stack;
    bool run = true;
    while (run) {
        ShowHeader("Лабораторні роботи 15-17: Стек", "Динамічний стек на базі списку");
        cout << FromCustomFormatToString(R"(
<green>Меню стеку:</green>
  1 - Додати елемент
  2 - Видалити елемент
  3 - Показати верхній елемент
  4 - Показати стек
  5 - Знайти елемент
  6 - Порахувати суму
  7 - Обчислити середнє значення
  8 - Зберегти стек у файл
  9 - Завантажити стек з файлу
  0 - Повернутись назад

<green>Оберіть опцію: </green>)");
        int choice = ReadIntInRange("", 0, 9);
        switch (choice) {
            case 1: {
                int val = ReadInt("Введіть значення: ");
                stack.push(val);
                LogSuccess("Елемент додано.");
                WaitForEnter();
                break;
            }
            case 2: {
                int value = stack.pop();
                if (value == numeric_limits<int>::min())
                    LogError("Стек порожній.");
                else
                    LogSuccess("Вилучено елемент: " + to_string(value));
                WaitForEnter();
                break;
            }
            case 3: {
                int value = stack.peek();
                if (value == numeric_limits<int>::min())
                    LogError("Стек порожній.");
                else
                    cout << "Верхній елемент: " << value << "\n";
                WaitForEnter();
                break;
            }
            case 4:
                stack.display();
                WaitForEnter();
                break;
            case 5: {
                int val = ReadInt("Значення для пошуку: ");
                if (stack.findElement(val))
                    LogSuccess("Елемент знайдено у стеку.");
                else
                    LogError("Елемент не знайдено.");
                WaitForEnter();
                break;
            }
            case 6:
                cout << "Сума елементів: " << stack.sum() << "\n";
                WaitForEnter();
                break;
            case 7:
                cout << fixed << setprecision(2);
                cout << "Середнє значення: " << stack.average() << "\n";
                WaitForEnter();
                break;
            case 8: {
                cout << "Введіть ім'я файлу: ";
                string filename;
                cin >> filename;
                stack.saveToFile(filename);
                WaitForEnter();
                break;
            }
            case 9: {
                cout << "Введіть ім'я файлу: ";
                string filename;
                cin >> filename;
                stack.loadFromFile(filename);
                WaitForEnter();
                break;
            }
            case 0:
                run = false;
                break;
            default:
                LogError("Невірний вибір.");
                WaitForEnter();
                break;
        }
    }
}

static void RunQueueMenu() {
    ListQueue listQueue;
    CircularQueue circularQueue(10);
    bool run = true;
    while (run) {
        ShowHeader("Лабораторні роботи 15-17: Черги", "Класична черга на списку та кільцева черга");
        cout << FromCustomFormatToString(R"(
<green>Меню черг:</green>
  1 - Класична черга (список)
  2 - Кільцева черга (масив)
  0 - Повернутись назад

<green>Оберіть опцію: </green>)");
        int choice = ReadIntInRange("", 0, 2);
        switch (choice) {
            case 1: {
                bool queueRun = true;
                while (queueRun) {
                    ShowHeader("Класична черга", "FIFO на базі динамічного списку");
                    cout << FromCustomFormatToString(R"(
<green>Класична черга:</green>
  1 - Додати елемент
  2 - Видалити елемент
  3 - Показати чергу
  4 - Показати мінімум
  5 - Показати максимум
  0 - Назад

<green>Оберіть опцію: </green>)");
                    int sub = ReadIntInRange("", 0, 5);
                    switch (sub) {
                        case 1: {
                            int val = ReadInt("Введіть значення: ");
                            listQueue.enqueue(val);
                            LogSuccess("Елемент додано.");
                            WaitForEnter();
                            break;
                        }
                        case 2: {
                            int value = listQueue.dequeue();
                            if (value == numeric_limits<int>::min())
                                LogError("Черга порожня.");
                            else
                                LogSuccess("Вилучено елемент: " + to_string(value));
                            WaitForEnter();
                            break;
                        }
                        case 3:
                            listQueue.display();
                            WaitForEnter();
                            break;
                        case 4:
                            if (listQueue.isEmpty()) {
                                LogError("Черга порожня.");
                            } else {
                                cout << "Мінімум: " << listQueue.minimum() << "\n";
                            }
                            WaitForEnter();
                            break;
                        case 5:
                            if (listQueue.isEmpty()) {
                                LogError("Черга порожня.");
                            } else {
                                cout << "Максимум: " << listQueue.maximum() << "\n";
                            }
                            WaitForEnter();
                            break;
                        case 0:
                            queueRun = false;
                            break;
                        default:
                            LogError("Невірний вибір.");
                            WaitForEnter();
                            break;
                    }
                }
                break;
            }
            case 2: {
                bool queueRun = true;
                while (queueRun) {
                    ShowHeader("Кільцева черга", "FIFO на базі масиву");
                    cout << FromCustomFormatToString(R"(
<green>Кільцева черга:</green>
  1 - Додати елемент
  2 - Видалити елемент
  3 - Показати чергу
  4 - Показати мінімум
  5 - Показати максимум
  0 - Назад

<green>Оберіть опцію: </green>)");
                    int sub = ReadIntInRange("", 0, 5);
                    switch (sub) {
                        case 1: {
                            int val = ReadInt("Введіть значення: ");
                            circularQueue.enqueue(val);
                            WaitForEnter();
                            break;
                        }
                        case 2: {
                            int value = circularQueue.dequeue();
                            if (value == numeric_limits<int>::min())
                                LogError("Чергa порожня.");
                            else
                                LogSuccess("Вилучено елемент: " + to_string(value));
                            WaitForEnter();
                            break;
                        }
                        case 3:
                            circularQueue.display();
                            WaitForEnter();
                            break;
                        case 4:
                            if (circularQueue.isEmpty()) {
                                LogError("Чергa порожня.");
                            } else {
                                cout << "Мінімум: " << circularQueue.minimum() << "\n";
                            }
                            WaitForEnter();
                            break;
                        case 5:
                            if (circularQueue.isEmpty()) {
                                LogError("Чергa порожня.");
                            } else {
                                cout << "Максимум: " << circularQueue.maximum() << "\n";
                            }
                            WaitForEnter();
                            break;
                        case 0:
                            queueRun = false;
                            break;
                        default:
                            LogError("Невірний вибір.");
                            WaitForEnter();
                            break;
                    }
                }
                break;
            }
            case 0:
                run = false;
                break;
            default:
                LogError("Невірний вибір.");
                WaitForEnter();
                break;
        }
    }
}

static void RunPriorityQueueMenu() {
    PriorityQueue pq;
    bool run = true;
    while (run) {
        ShowHeader("Лабораторні роботи 15-17: Пріоритетна черга", "Max-Priority Queue на базі списку");
        cout << FromCustomFormatToString(R"(
<green>Меню пріоритетної черги:</green>
  1 - Додати елемент з пріоритетом
  2 - Видалити елемент з найвищим пріоритетом
  3 - Показати вершину черги
  4 - Показати чергу
  0 - Повернутись назад

<green>Оберіть опцію: </green>)");
        int choice = ReadIntInRange("", 0, 4);
        switch (choice) {
            case 1: {
                int val = ReadInt("Введіть значення: ");
                int pr = ReadInt("Введіть пріоритет: ");
                pq.enqueue(val, pr);
                LogSuccess("Елемент додано у пріоритетну чергу.");
                WaitForEnter();
                break;
            }
            case 2: {
                int value = pq.dequeue();
                if (value == numeric_limits<int>::min())
                    LogError("Пріоритетна черга порожня.");
                else
                    LogSuccess("Вилучено елемент: " + to_string(value));
                WaitForEnter();
                break;
            }
            case 3: {
                int value = pq.peekHighest();
                if (value == numeric_limits<int>::min())
                    LogError("Пріоритетна черга порожня.");
                else
                    cout << "Вершина черги: " << value << "\n";
                WaitForEnter();
                break;
            }
            case 4:
                pq.display();
                WaitForEnter();
                break;
            case 0:
                run = false;
                break;
            default:
                LogError("Невірний вибір.");
                WaitForEnter();
                break;
        }
    }
}

static void RunDequeMenu() {
    Deque dq;
    bool run = true;
    while (run) {
        ShowHeader("Лабораторні роботи 15-17: Дек", "Двобічна черга на базі двозв'язного списку");
        cout << FromCustomFormatToString(R"(
<green>Меню дека:</green>
  1 - Додати елемент спереду
  2 - Додати елемент ззаду
  3 - Видалити елемент спереду
  4 - Видалити елемент ззаду
  5 - Показати передній елемент
  6 - Показати задній елемент
  7 - Показати дек
  0 - Повернутись назад

<green>Оберіть опцію: </green>)");
        int choice = ReadIntInRange("", 0, 7);
        switch (choice) {
            case 1: {
                int val = ReadInt("Введіть значення: ");
                dq.pushFront(val);
                LogSuccess("Елемент додано спереду.");
                WaitForEnter();
                break;
            }
            case 2: {
                int val = ReadInt("Введіть значення: ");
                dq.pushBack(val);
                LogSuccess("Елемент додано ззаду.");
                WaitForEnter();
                break;
            }
            case 3: {
                int value = dq.popFront();
                if (value == numeric_limits<int>::min())
                    LogError("Дек порожній.");
                else
                    LogSuccess("Вилучено елемент спереду: " + to_string(value));
                WaitForEnter();
                break;
            }
            case 4: {
                int value = dq.popBack();
                if (value == numeric_limits<int>::min())
                    LogError("Дек порожній.");
                else
                    LogSuccess("Вилучено елемент ззаду: " + to_string(value));
                WaitForEnter();
                break;
            }
            case 5: {
                int value = dq.peekFront();
                if (value == numeric_limits<int>::min())
                    LogError("Дек порожній.");
                else
                    cout << "Передній елемент: " << value << "\n";
                WaitForEnter();
                break;
            }
            case 6: {
                int value = dq.peekBack();
                if (value == numeric_limits<int>::min())
                    LogError("Дек порожній.");
                else
                    cout << "Задній елемент: " << value << "\n";
                WaitForEnter();
                break;
            }
            case 7:
                dq.display();
                WaitForEnter();
                break;
            case 0:
                run = false;
                break;
            default:
                LogError("Невірний вибір.");
                WaitForEnter();
                break;
        }
    }
}

void StackMain() {
    bool run = true;
    while (run) {
        ShowHeader("Лабораторні роботи 15-17", "Лінійні динамічні структури даних");
        cout << FromCustomFormatToString(R"(
<green>Меню лабораторних робіт 15-17:</green>
  1 - Стек (динамічний список)
  2 - Черги (класична та кільцева)
  3 - Пріоритетна черга
  4 - Дек
  0 - Повернутись назад

<green>Оберіть опцію: </green>)");
        int choice = ReadIntInRange("", 0, 4);
        switch (choice) {
            case 1: RunStackMenu(); break;
            case 2: RunQueueMenu(); break;
            case 3: RunPriorityQueueMenu(); break;
            case 4: RunDequeMenu(); break;
            case 0: run = false; break;
            default:
                LogError("Невірний вибір.");
                WaitForEnter();
                break;
        }
    }
}
