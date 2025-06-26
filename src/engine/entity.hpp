#pragma once

#include "transform_component.hpp"

namespace ZameEngine
{
class Entity
{
  public:
    Entity(std::size_t id);
    ~Entity();

    std::size_t getId() const;

  private:
    std::size_t mId;
};

} // namespace ZameEngine
