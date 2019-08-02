#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

class MergeSort {
 public:
  template <typename T>
  static std::vector<T> sort(std::vector<T>& vec) {
    return sortHelper(vec);
  }

 private:
  template <typename T>
  static std::vector<T> sortHelper(const std::vector<T>& vec) {
    int32_t n = vec.size();
    int32_t mid = n / 2;
    std::vector<T> out;
    if (n == 2) {
      out.push_back(std::min(vec[0], vec[1]));
      out.push_back(std::max(vec[0], vec[1]));
    } else if (n > 2) {
      std::vector<T> left =
          sortHelper(std::vector<T>(vec.begin(), vec.begin() + mid));
      std::vector<T> right =
          sortHelper(std::vector<T>(vec.begin() + mid, vec.end()));
      out = merge(left, right);
    } else {
      std::copy(vec.begin(), vec.end(), std::back_inserter(out));
    }
    return out;
  }
  template <typename T>
  static std::vector<T> merge(std::vector<T>& left, std::vector<T>& right) {
    std::vector<T> out;
    out.reserve(left.size() + right.size());

    int i = 0;
    int j = 0;

    while (out.size() < left.size() + right.size()) {
      if (i < left.size() && (j >= right.size() || left[i] < right[j])) {
        out.push_back(left[i]);
        i++;
      } else {
        out.push_back(right[j]);
        j++;
      }
    }
    return out;
  }
};
