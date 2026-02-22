//Trie Data Structure
#include <iostream>
using namespace std;

// Node structure for Trie
class TrieNode {
public:
    TrieNode* children[26];
    bool isLeaf;

    // Initialize Trie node
    TrieNode() {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isLeaf = false;
    }
};

// Trie data structure implementation
class Trie {
    TrieNode* root;

public:
    // Initialize Trie with root node
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(string key) {
        TrieNode* curr = root;
        for (char c : key) {
            int index = c - 'a';
            if (curr->children[index] == nullptr)
                curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isLeaf = true;
    }

    // Search for a complete word in the Trie
    bool search(string key) {
        TrieNode* curr = root;
        for (char c : key) {
            int index = c - 'a';
            if (curr->children[index] == nullptr)
                return false;
            curr = curr->children[index];
        }
        return curr->isLeaf;
    }

    // Check if a prefix exists in the Trie
    bool isPrefix(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (curr->children[index] == nullptr)
                return false;
            curr = curr->children[index];
        }
        return true;
    }
};

int main() {
    Trie trie;
    string arr[] = {"test", "elephant", "cat", "mouse"};

    for (string s : arr)
        trie.insert(s);

    string searchKeys[] = {"test", "ghee", "cat"};
    for (string s : searchKeys)
        cout << (trie.search(s) ? "true " : "false ");

    cout << endl;

    string prefixKeys[] = {"tes", "mo", "ele", "de"};
    for (string s : prefixKeys)
        cout << (trie.isPrefix(s) ? "true " : "false ");
    cout << endl;
    return 0;
}