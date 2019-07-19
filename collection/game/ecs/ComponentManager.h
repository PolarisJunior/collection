#pragma once

#include <unordered_map>
#include <vector>

template <typename T>
class ComponentManager {
 protected:
 public:
  std::vector<T> dataArray;
  std::unordered_map<uint32_t, uint32_t> entityToComp;

  void registerEntity(uint32_t eid, const T& val) {
    if (!isRegistered(eid)) {
      // not yet registered
      dataArray.push_back(val);
      entityToComp[eid] = dataArray.size() - 1;
    }
  }

  bool isRegistered(uint32_t eid) { return entityToComp.count(eid) > 0; }

  // Gets data associated with eid, assumes it exists
  T& get(uint32_t eid) { return dataArray[entityToComp[eid]]; }
};