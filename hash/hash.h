#ifndef HASH_H
#define HASH_H

#include <cstddef>
#include <vector>

// Структура для зберігання пари ключ-значення
struct hashTableEntry {
    int key;
    int value;
};

class hashMapTable {
private:
    std::size_t T_S;                                 // Розмір таблиці
    std::vector<std::vector<hashTableEntry>> table;  // Масив векторів (ланцюжки)

    // Хеш-функція (обчислення індексу)
    std::size_t hashFunction(int key) const;

public:
    // Конструктор
    explicit hashMapTable(int size);
    std::size_t GetSize() const;

    // Вставка або оновлення елемента
    void Insert(int key, int value);

    // Пошук значення за ключем
    bool TryGetValue(int key, int& value) const;
    bool ContainsKey(int key) const;
    int SearchKey(int key);

    // Видалення ключа
    bool Remove(int key);

    // Показати стан таблиці
    void DisplayTable() const;
    // Показати перелік колізій у таблиці
    void DisplayCollisions() const;
    // Показати статистику (кількість елементів, колізії, заповнення)
    void PrintStatistics() const;
};

#endif 



