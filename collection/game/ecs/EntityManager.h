#pragma once

#include <stack>
#include <vector>

struct Entity {
  uint32_t entityId;
};

class EntityManager {
 public:
  EntityManager(int32_t capacity);

  /* adds an entity to the first available index,
     returns the index or -1 if no free indices */
  uint32_t addEntity();

  /* Returns true if entity id is alive, does not check bounds */
  bool isAlive(uint32_t id);

  /* kills the entity at index id, does not check bounds
    does nothing if entity already killed */
  void kill(uint32_t id);

 private:
  std::vector<bool> aliveEntities;
  std::stack<uint32_t> freeIds;
};

inline EntityManager::EntityManager(int32_t capacity)
    : aliveEntities(std::vector<bool>(capacity)) {
  for (int32_t i = capacity - 1; i >= 0; --i) {
    freeIds.push(i);
  }
}

inline uint32_t EntityManager::addEntity() {
  if (freeIds.empty()) {
    return -1;
  }

  uint32_t id = freeIds.top();
  freeIds.pop();
  aliveEntities[id] = true;
  return id;
}

inline void EntityManager::kill(uint32_t id) {
  if (aliveEntities[id]) {
    aliveEntities[id] = false;
    freeIds.push(id);
  }
}

inline bool EntityManager::isAlive(uint32_t id) {
  return aliveEntities[id];
}