#pragma once

#include <vector>

class QuickSort {
 public:
  template <typename T>
  static void sort(std::vector<T>& vec) {
    sortHelper(vec, 0, vec.size());
  }

 private:
  // sorts start (inclusive) end (exclusive)
  template <typename T>
  static void sortHelper(std::vector<T>& vec, int32_t start, int32_t end) {
    int32_t n = end - start;
    if (n > 2) {
      int32_t pivotIdx = end - 1;
      T pivotValue = vec[pivotIdx];
      // everything up to leftMarker (exclusive) is less than the pivotValue
      int32_t leftMarker = start;
      for (int32_t i = start; i < pivotIdx; i++) {
        if (vec[i] < pivotValue) {
          T temp = vec[leftMarker];
          vec[leftMarker] = vec[i];
          vec[i] = temp;

          leftMarker++;
        }
      }
      T temp = vec[leftMarker];
      vec[leftMarker] = vec[pivotIdx];
      vec[pivotIdx] = temp;

      sortHelper(vec, start, leftMarker);
      sortHelper(vec, leftMarker + 1, end);
    } else if (n == 2) {
      int32_t small = vec[start] < vec[start + 1] ? vec[start] : vec[start + 1];
      int32_t large = vec[start] < vec[start + 1] ? vec[start + 1] : vec[start];
      vec[start] = small;
      vec[start + 1] = large;
    }
  }
};
