#pragma once

#include <cstdint>
#include <unordered_map>

// class GameObject;

template <typename Derived>
class Component {
 public:
  Component() = default;

  Component(const Component& c) = delete;
  Component& operator=(const Component& other) = delete;
  Component& operator=(Component&& other) = delete;

 private:
  inline static std::unordered_map<int32_t, Derived> entityToComponent;

  friend class GameObject;

  static Derived& addComponent(int32_t id) {
    // inserts the element in place with no copying
    return (entityToComponent
                .emplace(std::piecewise_construct, std::forward_as_tuple(id),
                         std::forward_as_tuple())
                .first)
        ->second;
  }

  static Derived& getComponent(int32_t id) { return entityToComponent.at(id); }

  static bool hasComponent(int32_t id) {
    return entityToComponent.count(id) > 0;
  }
};
