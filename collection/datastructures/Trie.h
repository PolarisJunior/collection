
#pragma once

#include <optional>
#include <string>
#include <unordered_map>

template <typename T>
class Trie {
 public:
  ~Trie() {
    for (auto it = children.begin(); it != children.end(); it++) {
      delete it->second;
    }
  }

  void insert(const std::string& key, T value) {
    // loop does not contain the null terminator
    Trie* node = this;

    for (char c : key) {
      if (node->children.count(c)) {
        // does contain c
        node = node->children[c];
      } else {
        // does not contain c
        node->children[c] = new Trie;
        node = node->children[c];
      }
    }

    node->value = value;
  }

  std::optional<T> get(const std::string& key) {
    Trie* node = this;

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
    Trie* node = this;
    for (char c : key) {
      if (node->children.count(c)) {
        node = node->children[c];
      } else {
        return false;
      }
    }
    return true;
  }

 private:
  std::unordered_map<char, Trie*> children;
  T value;

  uint32_t size = 0;
};
