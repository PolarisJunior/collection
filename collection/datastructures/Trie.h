
#pragma once

#include <optional>
#include <string>
#include <unordered_map>

template <typename T>
class Trie {
 private:
  struct TrieNode {
    ~TrieNode() {
      for (auto it = children.begin(); it != children.end(); it++) {
        delete it->second;
      }
    }

    std::unordered_map<char, TrieNode*> children;
    // wrap this in an optional?
    T value;
  };

 public:
  ~Trie() {}

  void insert(const std::string& key, T value) {
    TrieNode* node = &root;
    for (char c : key) {
      if (node->children.count(c)) {
        // does contain c
        node = node->children[c];
      } else {
        // does not contain c
        node->children[c] = new TrieNode;
        node = node->children[c];
      }
    }

    node->value = value;
  }

  std::optional<T> get(const std::string& key) {
    TrieNode* node = &root;

    for (char c : key) {
      if (node->children.count(c)) {
        node = node->children[c];
      } else {
        return std::nullopt;
      }
    }

    return std::optional<T>(node->value);
  }

  void remove(const std::string& key) {}

  bool hasKey(const std::string& key) {
    TrieNode* node = &root;
    for (char c : key) {
      if (node->children.count(c)) {
        node = node->children[c];
      } else {
        return false;
      }
    }
    return true;
  }

  uint32_t getSize() { return size; }

 private:
  TrieNode root;
  uint32_t size = 0;
};
