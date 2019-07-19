
#pragma once

#include <unordered_map>
#include <vector>
#include "../../math/Vector2.h"
#include "ComponentManager.h"
#include "EntityManager.h"

class PositionManager : public ComponentManager<Vector2<float>> {
 public:
  /* Gets the position of an entity */
  Vector2<float> getPosition(uint32_t eid);

  /* Sets the position of an entity */
  void setPosition(uint32_t eid, Vector2<float>& pos);

  void shiftHori(uint32_t eid, int32_t amount) { entityToComp.at(eid); }

  void shiftVert(uint32_t eid, int32_t amount) {}
};

inline Vector2<float> PositionManager::getPosition(uint32_t eid) {
  return dataArray[entityToComp.at(eid)];
  // return positions[entityToComp.at(eid)];
}

inline void PositionManager::setPosition(uint32_t eid, Vector2<float>& pos) {
  dataArray[entityToComp.at(eid)] = pos;
  // positions[entityToComp.at(eid)] = pos;
}
