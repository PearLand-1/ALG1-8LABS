#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class Trie {
public:
    Trie();
    ~Trie();

    void Insert(const std::string& word);
    bool Search(const std::string& word) const;
    bool StartsWith(const std::string& prefix) const;
    int CountWordsWithPrefix(const std::string& prefix) const;
    void Remove(const std::string& word);
    std::vector<std::string> GetAllWords() const;
    void Clear();

private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEndOfWord;
        TrieNode();
    };

    TrieNode* root;

    TrieNode* CreateNode() const;
    TrieNode* FindNode(const std::string& prefix) const;
    void CollectWords(TrieNode* node, std::string& current, std::vector<std::string>& words) const;
    int CountWords(TrieNode* node) const;
    TrieNode* RemoveRec(TrieNode* node, const std::string& word, int depth, bool& deleted);
    void ClearRec(TrieNode* node);
    std::string Normalize(const std::string& s) const;
    bool IsLowercaseLetter(char c) const;
};

#endif