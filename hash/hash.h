#ifndef HASH_H
#define HASH_H

#include <vector>

// Структура для зберігання пари ключ-значення
struct hashTableEntry {
    int key;
    int value;
};

class hashMapTable {
private:
    int T_S;                                 // Розмір таблиці
    std::vector<hashTableEntry>* table;      // Масив векторів (ланцюжки)

    // Хеш-функція (обчислення індексу)
    int hashFunction(int key) const;

public:
    // Конструктор
    explicit hashMapTable(int size);

    // Деструктор
    ~hashMapTable();

    // Вставка або оновлення елемента
    void Insert(int key, int value);

    // Пошук значення за ключем
    int SearchKey(int key);

    // Видалення ключа
    void Remove(int key);

    // Показати стан таблиці
    void DisplayTable() const;
    // Показати перелік колізій у таблиці
    void DisplayCollisions() const;
    // Показати статистику (кількість елементів, колізії, заповнення)
    void PrintStatistics() const;
};

#endif 



