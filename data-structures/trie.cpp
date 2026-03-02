#include <iostream>
#include <string>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isLeaf;
    TrieNode() {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isLeaf = false;
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

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

    // Returns the full word if prefix matches, else ""
    string findWord(string prefix) {
        TrieNode* curr = root;
        string result = prefix;

        for (char c : prefix) {
            int index = c - 'a';
            if (curr->children[index] == nullptr)
                return "";
            curr = curr->children[index];
        }

        // If exact word, return it
        if (curr->isLeaf) return result;

        // Try to complete the prefix to a word
        while (!curr->isLeaf) {
            bool found = false;
            for (int i = 0; i < 26; i++) {
                if (curr->children[i] != nullptr) {
                    result += (char)('a' + i);
                    curr = curr->children[i];
                    found = true;
                    break;
                }
            }
            if (!found) return "";
        }

        return result;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " word1 word2 ..." << endl;
        return 1;
    }

    Trie trie;
    for (int i = 1; i < argc; i++)
        trie.insert(string(argv[i]));

    string query;
    while (true) {
        cout << "Search: ";
        if (!getline(cin, query)) break;

        string result = trie.findWord(query);
        if (result != "")
            cout << "Found: " << result << endl;
        else
            cout << "No match found" << endl;
    }

    return 0;
}
