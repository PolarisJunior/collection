#pragma once

#include <algorithm>
#include <vector>

/* Strategy at each point is to go to the next
   index that has the farthest reach, reach is defined
   as index + value */
inline static std::vector<int> arrayHop(std::vector<int> vec) {
  std::vector<int> path;
  if (vec.size() < 1) {
    return path;
  }

  std::vector<int> reaches;
  for (int i = 0; i < vec.size(); i++) {
    reaches.push_back(i + vec[i]);
  }

  int tentativeNextHop = 0;
  int tentativeNextReach = reaches[0];
  int curReach = reaches[0];

  int i = 0;
  while (i < vec.size()) {
    path.push_back(tentativeNextHop);
    for (; i <= curReach; i++) {
      if (i >= vec.size()) {
        break;
      }

      if (reaches[i] > tentativeNextReach) {
        tentativeNextReach = reaches[i];
        tentativeNextHop = i;
      }
    }

    if (tentativeNextReach == curReach) {
      return std::vector<int>();
    }

    curReach = tentativeNextReach;
  }
  path.push_back(tentativeNextHop);
  return path;
}