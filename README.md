# Алгоритми та структури даних — Лабораторні роботи №1-26

## Опис проекту

Цей репозиторій містить реалізацію лабораторних робіт з алгоритмів на C++:
- Лабораторні роботи №1-8: різні алгоритми сортування масивів
- Лабораторні роботи №9-10: алгоритми пошуку елементів у масиві
- Лабораторні роботи №11-12: хеш-таблиця з ланцюговим вирішенням колізій
- Лабораторні роботи №13-14: однозв'язні, двозв'язні та кільцеві списки
- Лабораторні роботи №15-17: лінійні динамічні структури даних (стек, черги, пріоритетна черга, дек)
- Лабораторні роботи №18-19: бінарне дерево пошуку та AVL-дерево з автоматичним балансуванням
- Лабораторна робота №20: Trie (префіксне дерево)
- Лабораторні роботи №21-23: графи (матриця суміжності, DFS, BFS)
- Лабораторні роботи №24-26: розширені графи (топологія, MST Краскал/Прім)

Проєкт реалізовано з інтерактивним меню, кольоровою візуалізацією, тестами продуктивності (сортування та пошук), тестами коректності для хеш-таблиці та текстовою ASCII-візуалізацією дерев.

## Хто виконав

Виконав: **Чорноус Сергій (ІПЗ-22)**

## Нові можливості після додавання лабораторних 9-26

- Меню для вибору лабораторних робіт 1-8, 9-10, 11-12, 13-14, 21-23 та 24-26
- Пошук у масиві: лінійний пошук, двійковий пошук та бонусний стрибковий пошук
- Тестування алгоритмів пошуку на масивах різного розміру (за часом)
- Візуалізація процесу пошуку з виділенням перевірюваних елементів
- Хеш-таблиця: вставка, пошук, оновлення, видалення; перегляд колізій і статистики
- Списки: однозв'язні, двозв'язні та кільцеві структури з операціями вставки, видалення, пошуку та виводу
- Динамічні структури даних: стек, черги, пріоритетна черга, дек
- Бінарне дерево пошуку: вставка, пошук, видалення, обходи, мінімум/максимум, висота, кількість вузлів
- AVL-дерево: автоматичне балансування при вставці, видалення з балансуванням, обходи, висота, баланс кореня
- Trie (префіксне дерево): додавання слова, пошук слова, пошук за префіксом, підрахунок слів за префіксом, видалення
- ASCII-візуалізація дерев у текстовому вигляді для обох модулів
- Графи: матриця суміжності, DFS, BFS, топологічне сортування та MST (Краскал/Прім)
- **Автоматичні тести коректності** хеш-таблиці (`RunHashCorrectnessTests`) — перевірка правильності на фіксованих сценаріях із **покроковою візуалізацією** таблиці, статистики та колізій (як у лабораторних меню)

## Структура проекту

- `main.cpp` — центральне меню: сортування, пошук, хеш-таблиці, списки
- `MyLib.cpp`, `MyLib.h` — загальні утиліти: вивід кольорового тексту, введення масиву, `ReadInt` / `ReadPositiveInt`, тощо
- `sort/mainSort.cpp`, `sort/mainSort.h` — меню та керування лабораторними роботами 1-8
- `sort/sort.cpp`, `sort/sort.h` — реалізація алгоритмів сортування
- `sort/test.cpp`, `sort/test.h` — вимірювання часу виконання сортувань
- `search/mainSearch.cpp` — меню та керування лабораторними роботами 9-10
- `search/search.cpp`, `search/search.h` — реалізація алгоритмів пошуку
- `search/test.cpp`, `search/test.h` — вимірювання часу виконання пошуку
- `hash/mainHash.cpp`, `hash/mainHash.h` — меню лабораторних 11-12
- `hash/hash.cpp`, `hash/hash.h` — реалізація хеш-таблиці з ланцюжками
- `hash/test.cpp`, `hash/test.h` — **тести коректності** хеш-таблиці на заготовлених даних
- `node/mainNode.cpp`, `node/mainNode.h` — меню лабораторних 13-14
- `node/slist.cpp`, `node/slist.h` — однозв'язний список (лаб. 13)
- `node/dlist.cpp`, `node/dlist.h` — двозв'язний список (лаб. 14)
- `node/clist.cpp`, `node/clist.h` — кільцевий однозв'язний список (лаб. 14)
- `stack/mainStack.cpp`, `stack/mainStack.h` — меню лабораторних 15-17 (стек, черги, пріоритетна черга, дек)
- `tree/mainTree.cpp`, `tree/mainTree.h` — меню лабораторних 18-19
- `tree/tree.cpp`, `tree/tree.h` — реалізація бінарного дерева пошуку та AVL-дерева з ASCII-візуалізацією
- `trie/mainTrie.cpp`, `trie/mainTrie.h` — меню лабораторної роботи 20
- `trie/trie.cpp`, `trie/trie.h` — реалізація префіксного дерева Trie
- `graph/mainGraph.cpp`, `graph/mainGraph.h` — меню лабораторних 21-23
- `graph/graph.cpp`, `graph/graph.h` — матриця суміжності, довідка, DFS, BFS
- `graph_more/mainGraphMore.cpp`, `graph_more/mainGraphMore.h` — меню лабораторних 24-26 (топологія, MST)

## Опис основних функцій

### Головні функції
- `main()` — запускає головне меню для вибору між сортуванням, пошуком, хеш-таблицею, списками, деревами та графами
- `SortMenu()` — відображає меню лабораторних робіт 1-8 і обробляє вибір
- `SearchMenu()` — відображає меню лабораторних робіт 9-10 і обробляє вибір
- `HashMain()` — меню лабораторних 11-12 (інтерактивно та пункт з автотестами)
- `NodeMain()` — меню лабораторних 13-14 (списки)
- `StackMain()` — меню лабораторних 15-17 (стек, черги, пріоритетна черга, дек)
- `TreeMain()` — меню лабораторних 18-19 (дерева)
- `TrieMain()` — меню лабораторної роботи 20 (Trie)
- `GraphMain()` — меню лабораторних 21-23 (графи: введення, довідка, DFS, BFS)
- `GraphMoreMain()` — меню лабораторних 24-26 (топологічне сортування, MST Краскал/Прім)

### Сортування
- `RunAlgorithm(int type)` — викликає потрібний алгоритм сортування за номером
- `SelectionSort(...)` — реалізація сортування вибором
- `InsertionSort(...)` — реалізація сортування вставками
- `BubbleSort(...)` — бульбашкове сортування
- `MergeSort(...)` — сортування злиттям
- `QuickSort(...)` — швидке сортування
- `ShellSort(...)` — сортування Шелла
- `ShakerSort(...)` — шейкерне сортування
- `HeapSort(...)` — сортування з купою

### Пошук
- `RunSearch(short i)` — виконує обраний алгоритм пошуку
- `LinearSearch(...)` — лінійний пошук у масиві
- `BinarySearch(...)` — двійковий пошук у відсортованому масиві
- `JumpSearch(...)` — бонусний стрибковий пошук

### Тести та продуктивність
- `RunTest(int arraySize)` — тестує всі алгоритми сортування для заданого розміру масиву (час)
- `RunTest2(int arraySize)` — тестує алгоритми пошуку для заданого розміру масиву (час)
- `TestSortingAlgorithm(...)` — вимірює час виконання одного алгоритму сортування
- `TestSearchAlgorithm(...)` — вимірює час виконання одного алгоритму пошуку
- `RunHashCorrectnessTests()` — перевіряє **коректність** хеш-таблиці на **фіксованих** парах ключ–значення (вставка, оновлення, пошук, видалення, колізії); між кроками показуються `DisplayTable`, `PrintStatistics`, за потреби `DisplayCollisions`, затримка через `visualizationDelay`; час виконання не вимірюється

### Допоміжні утиліти
- `FromCustomFormatToString(string item)` — перетворює теги `<b>`, `<i>`, `<red>` тощо в ANSI-коди для кольорового тексту
- `Log(...)`, `LogSuccess(...)`, `LogError(...)` — виводять повідомлення з кольоровим оформленням
- `PrintArray(vector<int>& a, int idx1, int idx2)` — показує масив з підсвічуванням індексів
- `InputArray()` — вводить масив вручну з консолі
- `RandomArray()` — генерує випадковий масив з параметрами від користувача
- `ReadInt(...)`, `ReadPositiveInt(...)` — безпечне введення цілих чисел з повтором при помилці

## Компіляція та встановлення

### Windows

#### MSVC
1. Відкрийте `Developer Command Prompt for Visual Studio`
2. Перейдіть до папки проекту
3. Виконайте:
```bash
cl /EHsc main.cpp MyLib.cpp sort/mainSort.cpp sort/sort.cpp sort/test.cpp search/mainSearch.cpp search/search.cpp search/test.cpp hash/mainHash.cpp hash/hash.cpp hash/test.cpp node/mainNode.cpp node/slist.cpp node/dlist.cpp node/clist.cpp stack/mainStack.cpp tree/mainTree.cpp tree/tree.cpp trie/mainTrie.cpp trie/trie.cpp graph/mainGraph.cpp graph/graph.cpp graph_more/mainGraphMore.cpp /Fe:program.exe
```

#### MinGW/GCC
1. Встановіть MinGW або MSYS2
2. Переконайтеся, що `g++` доступний у PATH
3. Виконайте (рекомендована команда з **C++20** і статичним лінкуванням стандартної бібліотеки MinGW — зручно переносити `program.exe`):
```bash
g++ -std=c++20 -o program.exe main.cpp MyLib.cpp sort/mainSort.cpp sort/sort.cpp sort/test.cpp search/search.cpp search/mainSearch.cpp search/test.cpp hash/hash.cpp hash/mainHash.cpp hash/test.cpp node/mainNode.cpp node/slist.cpp node/dlist.cpp node/clist.cpp stack/mainStack.cpp tree/mainTree.cpp tree/tree.cpp trie/mainTrie.cpp trie/trie.cpp graph/mainGraph.cpp graph/graph.cpp graph_more/mainGraphMore.cpp graph_more/graph_high.cpp -static-libgcc -static-libstdc++ -static
```

### Linux

1. Встановіть компілятор:
   - Debian/Ubuntu: `sudo apt update && sudo apt install build-essential`
   - Fedora: `sudo dnf install gcc-c++`
   - Arch: `sudo pacman -S gcc`
2. Виконайте:
```bash
g++ -std=c++20 -o program.exe main.cpp MyLib.cpp sort/mainSort.cpp sort/sort.cpp sort/test.cpp search/search.cpp search/mainSearch.cpp search/test.cpp hash/hash.cpp hash/mainHash.cpp hash/test.cpp node/mainNode.cpp node/slist.cpp node/dlist.cpp node/clist.cpp stack/mainStack.cpp tree/mainTree.cpp tree/tree.cpp trie/mainTrie.cpp trie/trie.cpp graph/mainGraph.cpp graph/graph.cpp graph_more/mainGraphMore.cpp graph_more/graph_high.cpp -static-libgcc -static-libstdc++ -static
```

### macOS

1. Встановіть Xcode Command Line Tools:
```bash
xcode-select --install
```
2. Виконайте:
```bash
g++ -std=c++20 -o program main.cpp MyLib.cpp sort/mainSort.cpp sort/sort.cpp sort/test.cpp search/search.cpp search/mainSearch.cpp search/test.cpp hash/hash.cpp hash/mainHash.cpp hash/test.cpp node/mainNode.cpp node/slist.cpp node/dlist.cpp node/clist.cpp stack/mainStack.cpp tree/mainTree.cpp tree/tree.cpp trie/mainTrie.cpp trie/trie.cpp graph/mainGraph.cpp graph/graph.cpp graph_more/mainGraphMore.cpp graph_more/graph_high.cpp
```

### Додаткові інструкції
- Для запуску на Linux/macOS потрібно закоментувати або видалити виклики `SetConsoleOutputCP(CP_UTF8);` та `SetConsoleCP(CP_UTF8);` у `main.cpp`
- На Windows бажано використовувати консоль із підтримкою UTF-8 для коректного відображення українських символів

## Запуск програми

### Windows
```bash
program.exe
```

### Linux/macOS
```bash
./program
```

## Як користуватися

1. У головному меню виберіть:
   - `1` — меню лабораторних робіт 1-8 (сортування)
   - `2` — меню лабораторних робіт 9-10 (пошук)
   - `3` — меню лабораторних 11-12 (хеш-таблиці)
   - `4` — меню лабораторних 13-14 (списки)
   - `5` — меню лабораторних 21-23 (графи)
   - `6` — меню лабораторних 24-26 (розширені графи)
   - `7` — меню лабораторних 15-17 (стек, черги, пріоритетна черга, дек)
   - `8` — меню лабораторних 18-19 (дерева)
   - `9` — меню лабораторної роботи 20 (Trie)
   - `0` — вихід
2. Для сортування оберіть алгоритм 1-8 або `9` для тестування всіх алгоритмів (за часом)
3. Для пошуку оберіть `9` для лінійного, `10` для двійкового, `1` — бонусний стрибковий пошук; пункт `2` — тести за часом
4. Для хеш-таблиці: лабораторна 11 (операції), лабораторна 12 (колізії); пункт **`3`** у підменю хешів — автоматичні тести коректності
5. Для списків: **`13`** — однозв'язний список; **`14`** — двозв'язний і кільцевий (підменю)
6. Для графів **21-23**: введення матриці (клавіатура / файл / список ребер), довідка, DFS, BFS; пункт **`6`** у підменю — демо-граф з методички
7. Для розширених графів **24-26**: введення/довідка (пункти `1-4`), топосорт DFS/Кана (пункти `5-6`), MST Краскал/Прім (пункти `7-8`)
8. Для дерев: **`18`** — бінарне дерево пошуку, **`19`** — AVL-дерево з ASCII-візуалізацією
9. Введіть масив вручну або згенеруйте випадковий масив (для сортування/пошуку)
10. За потреби вмикайте візуалізацію та задайте затримку (сортування)

## Автор і мета

Виконавець: **Чорноус Сергій (ІПЗ-22)**

Мета проєкту: показати практичну роботу алгоритмів сортування, пошуку, хешування та роботи зі списками, візуалізувати кроки алгоритмів і перевіряти коректність структур даних.

