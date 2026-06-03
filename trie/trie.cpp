#include "trie.h"

#include <algorithm>

Trie::Trie() {
    root = CreateNode();
}

Trie::~Trie() {
    Clear();
}

Trie::TrieNode* Trie::CreateNode() const {
    TrieNode* node = new TrieNode();
    return node;
}

Trie::TrieNode::TrieNode() : isEndOfWord(false) {
    for (int i = 0; i < 26; ++i)
        children[i] = nullptr;
}

std::string Trie::Normalize(const std::string& s) const {
    std::string result;
    result.reserve(s.size());
    for (char c : s) {
        if (c >= 'A' && c <= 'Z')
            result.push_back(static_cast<char>(c - 'A' + 'a'));
        else if (c >= 'a' && c <= 'z')
            result.push_back(c);
    }
    return result;
}

bool Trie::IsLowercaseLetter(char c) const {
    return c >= 'a' && c <= 'z';
}

void Trie::Insert(const std::string& word) {
    std::string normalized = Normalize(word);
    TrieNode* current = root;
    for (char c : normalized) {
        if (!IsLowercaseLetter(c))
            continue;
        int index = c - 'a';
        if (current->children[index] == nullptr)
            current->children[index] = CreateNode();
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool Trie::Search(const std::string& word) const {
    std::string normalized = Normalize(word);
    TrieNode* current = root;
    for (char c : normalized) {
        if (!IsLowercaseLetter(c))
            continue;
        int index = c - 'a';
        if (current->children[index] == nullptr)
            return false;
        current = current->children[index];
    }
    return current->isEndOfWord;
}

Trie::TrieNode* Trie::FindNode(const std::string& prefix) const {
    std::string normalized = Normalize(prefix);
    TrieNode* current = root;
    for (char c : normalized) {
        if (!IsLowercaseLetter(c))
            continue;
        int index = c - 'a';
        if (current->children[index] == nullptr)
            return nullptr;
        current = current->children[index];
    }
    return current;
}

bool Trie::StartsWith(const std::string& prefix) const {
    return FindNode(prefix) != nullptr;
}

int Trie::CountWords(TrieNode* node) const {
    if (node == nullptr)
        return 0;
    int count = node->isEndOfWord ? 1 : 0;
    for (int i = 0; i < 26; ++i)
        count += CountWords(node->children[i]);
    return count;
}

int Trie::CountWordsWithPrefix(const std::string& prefix) const {
    TrieNode* node = FindNode(prefix);
    return node ? CountWords(node) : 0;
}

void Trie::CollectWords(TrieNode* node, std::string& current, std::vector<std::string>& words) const {
    if (node == nullptr)
        return;
    if (node->isEndOfWord)
        words.push_back(current);
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
            current.push_back('a' + i);
            CollectWords(node->children[i], current, words);
            current.pop_back();
        }
    }
}

std::vector<std::string> Trie::GetAllWords() const {
    std::vector<std::string> words;
    std::string current;
    CollectWords(root, current, words);
    return words;
}

Trie::TrieNode* Trie::RemoveRec(TrieNode* node, const std::string& word, int depth, bool& deleted) {
    if (node == nullptr)
        return nullptr;

    if (depth == static_cast<int>(word.size())) {
        if (node->isEndOfWord) {
            node->isEndOfWord = false;
            deleted = true;
        }
        bool hasChildren = false;
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                hasChildren = true;
                break;
            }
        }
        if (!hasChildren) {
            delete node;
            return nullptr;
        }
        return node;
    }

    char c = word[depth];
    if (!IsLowercaseLetter(c))
        return node;

    int index = c - 'a';
    node->children[index] = RemoveRec(node->children[index], word, depth + 1, deleted);

    if (node->isEndOfWord)
        return node;

    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr)
            return node;
    }

    delete node;
    return nullptr;
}

void Trie::Remove(const std::string& word) {
    bool deleted = false;
    std::string normalized = Normalize(word);
    root = RemoveRec(root, normalized, 0, deleted);
    if (root == nullptr)
        root = CreateNode();
}

void Trie::ClearRec(TrieNode* node) {
    if (node == nullptr)
        return;
    for (int i = 0; i < 26; ++i)
        ClearRec(node->children[i]);
    delete node;
}

void Trie::Clear() {
    ClearRec(root);
    root = CreateNode();
}